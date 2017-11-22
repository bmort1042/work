/*
 * Beau Morton
 * CptS360
 * PA4, Tattle
 * 20170417
 *
 *
 *
 *
*/

#define _GNU_SOURCE
#define _XOPEN_SOURCE 	
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utmp.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <pwd.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "syscall_check.h"
#include "get_sockaddr.h"
#include "client_server.h"

#define BUFFSIZE 20

typedef struct List{
    char ut_user[UT_NAMESIZE];
    char ut_line[UT_LINESIZE];
    char ut_host[UT_HOSTSIZE];

    int logoff_set;

    pid_t ut_pid;
    int invalid;
    int userSelected;
    time_t logonEpoch;
    time_t logoffEpoch;
    char logon[BUFFSIZE];
    char logoff[BUFFSIZE];

    struct List *next;
    struct List *previous;

} List;

List Root;

void initializeList(List *node){
    node->logoff_set = 0;
    node->ut_pid = 0;
    node->userSelected = 0;
    node->invalid = 0;
    node->logonEpoch = 0;
    node->logoffEpoch = 0;
    node->next = NULL;
    node->previous = NULL;

}


void printList(int userCheckReturn, time_t timeParams){
    List *tmp;
    tmp = &Root;
    time_t logon, logoff;
    tmp = tmp->next;

    printf("\n\n%-20s|%-20s|%-20s|%-20s|%-20s\n", "login", "tty", "log on", "log off", "from host");
     printf("_____________________________________________________________________________________________\n");

     tmp = tmp->next;
    //If users are specified and time is not
    if(userCheckReturn == 1 && timeParams == 0){
        while(tmp != NULL){
            if(tmp->userSelected){

                if(tmp->logoffEpoch == 0){
                    strcpy(tmp->logoff, "(stil logged on)");
                }

                printf("%-20s|%-20s|%-20s|%-20s|%-20s\n", tmp->ut_user, tmp->ut_line, tmp->logon, tmp->logoff, tmp->ut_host);               
            }
            tmp = tmp->next;
        }
    }//Else, if users and time are both specified 
    else if(userCheckReturn == 1 && timeParams != 0){

        while(tmp != NULL){

            logon = tmp->logonEpoch;
            logoff = tmp->logoffEpoch;
            if(tmp->userSelected == 1 && ((timeParams >= logon && timeParams < logoff) || (timeParams >= logon && strcmp(tmp->logoff, "(still logged on)") == 0))){
                if(tmp->logoff_set == 0){
                    strcpy(tmp->logoff, "(still logged on)");
                }
                printf("%-20s|%-20s|%-20s|%-20s|%-20s\n", tmp->ut_user, tmp->ut_line, tmp->logon, tmp->logoff, tmp->ut_host);
            }
            tmp = tmp->next;
        }
    }//Else if only time is specified and not users
    else if(userCheckReturn != 1 && timeParams != 0){

        while(tmp != NULL){

            logon = tmp->logonEpoch;
            logoff = tmp->logoffEpoch;

                if(tmp->logoff_set == 0){
                    strcpy(tmp->logoff, "(still logged on)");
                }

                if((logon <= timeParams  && logoff > timeParams) || (timeParams >= logon && strcmp(tmp->logoff, "(still logged on)") == 0)){
                     printf("%-20s|%-20s|%-20s|%-20s|%-20s\n", tmp->ut_user, tmp->ut_line, tmp->logon, tmp->logoff, tmp->ut_host);

                }

            tmp = tmp->next;
        }
    }//Else, print it all - default option
    else if(userCheckReturn != 1 && timeParams == 0){ 

        while(tmp != NULL){

            if(tmp->logoff_set == 0){
                strcpy(tmp->logoff, "(still logged on)");
            }
            printf("%-20s|%-20s|%-20s|%-20s|%-20s\n", tmp->ut_user, tmp->ut_line, tmp->logon, tmp->logoff, tmp->ut_host);

            tmp = tmp->next;
        }
    }
    printf("\n\n");
    
}

//Help option
void usage(void)
{
    printf("*usage: ./rtattle [-u login[, login]*] [-d date (mm/dd/yy)] [-t time (HH:MM)] [-p port] hosts[, *hosts]*\n");
}



//Check to make sure the date is in the right format, if not exit.
int userDateCheck(char *loginDate){

    struct tm date = {0};


    if(strlen(loginDate) == 8){
        if(strptime(loginDate, "%D", &date) == NULL){
            fprintf(stderr, "Invalid date format, needs to mm/dd/yy!\n");
            usage();
            exit(EXIT_FAILURE);
        }else{
            return 1;
        }
    }else{
        fprintf(stderr, "Invalid date format, needs to mm/dd/yy!\n");
        usage();
        exit(EXIT_FAILURE);
    }


    
}

//Check to make sure the time is in the right format, if not exit.
int userTimeCheck(char *loginTime){

    struct tm time = {0};

    if(strlen(loginTime) == 5){

        if(strptime(loginTime, "%R", &time) == NULL){
        fprintf(stderr, "Invalid time format, needs to HH:MM (24 hour)!\n");
        usage();
        exit(EXIT_FAILURE);  
        }else{
            return 1;
        }
    }else{
        fprintf(stderr, "Invalid time format, needs to HH:MM (24 hour)!\n");
        usage();
        exit(EXIT_FAILURE);  
    }
    

    
}

//free the list
void freeLinkedList(void){
    List *tmp, *nextList;
    tmp = &Root;
    tmp = tmp->next;

    while(tmp != NULL){
        nextList = tmp->next;
        free(tmp);
        tmp = nextList;
    }
}

void remoteShell(char *users, char *hosts, int port)
{
    /*
     * ASSIGNMENT
     *
     * Implement the following pseudocode:
     *
     * declare a char buffer of RESPONSE_SIZE `response`
     * let `socketFd` be a datagram socket for the Internet address
     *  family (hint: socket(2))
     * fill in a "struct sockaddr_in" `inetSocketAddress` associating
     *  socket with `host` and `port` (hint: getInetSocketAddress())
     * send `command` out on `socketFd` with a "return address" of
     *  `inetSocketAddress` (hint: sendto(2), which expects a pointer
     *  to a "struct sockaddr *", so you'll have to cast it)
     * set `responseLength` to the result of reading `response` from
     *  `socketFd` (hint: recvfrom(2))
     * write `response` on standard output (hint: fwrite(3))
     */

    //char response[RESPONSE_SIZE];

    if(users == NULL){
        //printf("Adding null terminator\n");
        users = (char *)calloc(6, sizeof(char));
        users = "noone\0";
    }

    //printf("Here is the user in rtattle: %s\n", users);

    char buffer[40];
    strcpy(buffer, hosts);

    //printf("Here is the buffer: %s\n", buffer);
    char *p;
    int multihost = 0;

    int start = 0;

    //printf("Here are the users being passed: %s\n", users);
    p = strtok(hosts, ",");

    if(p == NULL){
        p = buffer;
    }

    //printf("Here is the host: %s\n", p);
    
     
    while(p != NULL){

        //printf("Here is the host: %s\n", hosts);

        //printf("Here are the users being passed: %s\n", users);
        //List *response = malloc(sizeof(List));
        List *tmp, *root;

        tmp = &Root;
        root = &Root;


        int socketFd;

        socketFd = socket(AF_INET, SOCK_DGRAM, 0);

        struct timeval tv;
        tv.tv_sec = 2;  /* 2 Secs Timeout */
        tv.tv_usec = 0;  // Not init'ing this can cause strange errors
        setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(struct timeval));

        if(socketFd < 0)
            printf("Error opening socket!\n");

        struct sockaddr_in inetSockAddress;
        getInetSocketAddress(p, SOCK_DGRAM, port, &inetSockAddress); //pass in the host

        sendto(socketFd, users, strlen(users) + 1, 0, (struct sockaddr *) &inetSockAddress, sizeof(struct sockaddr));



        struct sockaddr_in inetSocketAddress;

        memset (&inetSocketAddress, 0, sizeof(inetSocketAddress));

        inetSocketAddress.sin_family = AF_INET;
        inetSocketAddress.sin_addr.s_addr = INADDR_ANY;
        inetSocketAddress.sin_port = port;

        //socklen_t socketAdressLen = sizeof(inetSocketAddress);


        socklen_t fromlen = sizeof(inetSocketAddress);

        //ssize_t responseLength = recvfrom(socketFd, response, sizeof(struct List) - 1, 0, (struct sockaddr*)&inetSocketAddress, &fromlen);



        while(1){

            List *response = malloc(sizeof(List));
            
            if(recvfrom(socketFd, response, sizeof(struct List) - 1, 0, (struct sockaddr*)&inetSocketAddress, &fromlen) <= 0){
                free(response);
                break;
            }

            List *newnode = malloc(sizeof(List));

            if(start == 0){

                memcpy(newnode, response, sizeof(List));
                newnode->next = NULL;
                newnode->previous = root;
                root->next = newnode;
                start++;
                free(response);

            }else{

                if(multihost != 0){
                    memcpy(newnode, response, sizeof(List));
                    List *temp1;

                    tmp = root;

                    while(tmp->next != NULL){

                        if(tmp->logonEpoch > newnode->logonEpoch){
                            temp1 = tmp->previous;
                            tmp->previous = newnode;
                            newnode->next = tmp;
                            newnode->previous = temp1;
                            temp1->next = newnode;
                            free(response);

                        }else{
                            newnode->next = NULL;
                            newnode->previous = tmp;
                            tmp->next = newnode;
                            free(response);
                        }
                    }

                }else{
                    //printf("Here is the response length: %d\n", responseLength);
                    memcpy(newnode, response, sizeof(List));

                    tmp = root;

                    while(tmp->next != NULL){
                    tmp = tmp->next;
                    }

                    newnode->next = NULL;
                    newnode->previous = tmp;
                    tmp->next = newnode;
                    free(response);
                }
                
            }

            


        }

            multihost++;

            close(socketFd);

            p = strtok(NULL, ",");

            //printf("Here is p: %s\n", p);
    }

    //free(users);
    return;

}

int userChecks(char *userNames){

    List *tmp;

    char *p;

    p = strtok(userNames, ",");
    if(p == NULL){
        return 0;
    }

    while(p != NULL){

        tmp = &Root;

        while(tmp != NULL){

            if(strcmp(p, tmp->ut_user) == 0){

                tmp->userSelected = 1;
            }
            tmp = tmp->next;
        }

        p = strtok(NULL, ",");
    }

    return 1;
}


int main(int argc, char *argv[]){



    int ch, userCheckReturn, userDateCheckReturn, userTimeCheckReturn;
    char defaultTimeorDate[80];
    char *userNamesAll, *loginDate, *loginTime, *passingTimeandDate;
    char hostNames[1024] = {0};
    userCheckReturn = 0;
    userDateCheckReturn = 0;
    userTimeCheckReturn = 0;
    userNamesAll = NULL;
    passingTimeandDate = NULL;
    loginDate = NULL;
    loginTime = NULL;
    //userName = NULL;
    int index = 0;
    int arguments = 0;
    int port = -1;


    for(int i = 0; i < argc; i++){
        //printf("argv[%d]: %s \n", i, argv[i]);
        arguments++;
        //printf("Here are the arguments: %d\n", arguments);
    }

    while((ch = getopt(argc, argv, "u:d:t:p:")) != -1){
        switch(ch){
            case 'u':

                userNamesAll = (char*)malloc((strlen(optarg) + 1) * sizeof(char));
                strcpy(userNamesAll, optarg);
                index++;
                break;

            case 'd':

                loginDate = (char*)malloc((strlen(optarg) + 1) * sizeof(char));
                strcpy(loginDate, optarg);
                userDateCheckReturn = userDateCheck(loginDate);
                index++;     
                break;

            case 't':
                
                loginTime = (char*)malloc((strlen(optarg) + 1) * sizeof(char));
                strcpy(loginTime, optarg);
                userTimeCheckReturn = userTimeCheck(loginTime); //testing, make sure to pass this to validation function
                index++;
                break;

            case 'p':
                index++;
                break;

            default:
                fprintf(stderr, "unknown option \"-%c\" -- exiting\n", ch);
                usage();
                exit(EXIT_FAILURE);

        }
        index++;
        
    }

    //printf("Here is the index: %d\n", index);

    if(arguments == index){
        fprintf(stderr, "Need to pass a host!\n");
        usage();
        exit(EXIT_FAILURE);
    }else{

        for(int i = index + 1; i < arguments; i++){
            strcat(hostNames, argv[i]);
            //printf("Hostname: %s\n", hostNames);
        }


    }

    port = DEFAULT_PORT;
    
    char *allHosts = hostNames;

    //printf("Here are the users being passed: %s\n", userNamesAll);

    remoteShell(userNamesAll, allHosts, port);

    userCheckReturn = userChecks(userNamesAll);

    struct tm *info;
    struct tm epochtest = {0}; //if you don't do this, you're going to get bitched at by valgrind
    time_t rawtime, testtime;
    info = NULL;
    rawtime = 0;
    testtime = 0;



    //If both -t and -d options are used, get the time_t
    if(userDateCheckReturn == 1 && userTimeCheckReturn == 1){

        asprintf(&passingTimeandDate, "%s %s", loginDate, loginTime);

        strptime(passingTimeandDate, "%D %H:%M", &epochtest);
        testtime = mktime(&epochtest);

        free(loginTime);
        free(loginDate);


    }//If only -d is used, get current time. Concatenate the two togther,
     //then convert to time_t
    else if(userDateCheckReturn == 1 && userTimeCheckReturn != 1){

        time(&rawtime);
        info = localtime(&rawtime);
        strftime(defaultTimeorDate, 80, "%H:%M", info);

        asprintf(&passingTimeandDate, "%s %s", loginDate, defaultTimeorDate);

        epochtest.tm_isdst = 1; //daylights saving

        strptime(passingTimeandDate, "%D %H:%M", &epochtest);
        testtime = mktime(&epochtest);

        free(loginDate);

    }//If only -t is used, get current date. Concatenate the two togther,
     //then convert to time_t
    else if(userDateCheckReturn != 1 && userTimeCheckReturn == 1){

        time(&rawtime);
        info = localtime(&rawtime);
        strftime(defaultTimeorDate, 80, "%D", info);

        asprintf(&passingTimeandDate, "%s %s", defaultTimeorDate, loginTime);

        epochtest.tm_isdst = 1; //daylights saving

        strptime(passingTimeandDate, "%D %H:%M", &epochtest);
        testtime = mktime(&epochtest);

        free(loginTime);
    }

    List *tmp;
    tmp = &Root;

    if(tmp->next != NULL){
        printList(userCheckReturn, testtime);

        freeLinkedList();
    }

    //fclose(fp);
    free(passingTimeandDate);
    free(userNamesAll);
    return(0);
	
}
