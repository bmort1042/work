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

#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>

#include "daemonize_me.h"
#include "syscall_check.h"
#include "client_server.h"

#define BUFFSIZE 20
#define MIN_USER_PORT 1024
#define HOST_NAME_MAX 256

static int runAsDaemon = 0;

int userChecks(char *userNames);


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


void addInitialList(struct utmp *log, int *first){

    List *tmp, *root;
    time_t getTime = 0;
    char buffer[BUFFSIZE];
    char buffer2[BUFFSIZE];


    root = &Root;
    tmp = root;


    //If it's a user process, add it to the list
    if(log->ut_type == USER_PROCESS){

        List *newnode = malloc(sizeof(List));
        // Initialize list attributes
        initializeList(newnode);

        getTime = log->ut_time;

        if((*first) == 0){
            strcpy(newnode->ut_user, log->ut_user);
            stpcpy(newnode->ut_line, log->ut_line);
            stpcpy(newnode->ut_host, log->ut_host);
            newnode->ut_pid = log->ut_pid;
            newnode->logonEpoch = log->ut_time;
            strftime(buffer, sizeof(buffer),"%D %H:%M", localtime(&getTime));
            strcpy(newnode->logon, buffer);
            newnode->next = NULL;
            newnode->previous = root;
            root->next = newnode;
        }
        else{

            tmp = root;

            while(tmp->next != NULL){
                if((strcmp(log->ut_line, tmp->ut_line) == 0) && tmp->logoff_set == 0){

                    strftime(buffer2, sizeof(buffer2),"%D %H:%M", localtime(&getTime));
                    strcpy(tmp->logoff, buffer2);
                    tmp->logoffEpoch = log->ut_time;
     
                    tmp->logoff_set = 1;
                    free(newnode);
                    return;
                }
                tmp = tmp->next;
            }

            strcpy(newnode->ut_user, log->ut_user);
            stpcpy(newnode->ut_line, log->ut_line);
            stpcpy(newnode->ut_host, log->ut_host);
            newnode->ut_pid = log->ut_pid;
            newnode->logonEpoch = log->ut_time;
            strftime(buffer, sizeof(buffer),"%D %H:%M", localtime(&getTime));
            strcpy(newnode->logon, buffer);

            newnode->next = NULL;
            newnode->previous = tmp;
            tmp->next = newnode;

        }
        (*first)++;

    } //Else, if it is a dead process, find the correct user
    else if(log->ut_type == DEAD_PROCESS){

        getTime = log->ut_time;

        tmp = root;
        while(tmp != NULL){

        	if(tmp->logoff_set == 0){
        		if((strcmp(log->ut_line, tmp->ut_line) == 0)){

                //Do the work upfront and convert time_t to string and store value
                //still need time_t value for user time constraints
                strftime(buffer2, sizeof(buffer2),"%D %H:%M", localtime(&getTime));
                strcpy(tmp->logoff, buffer2);
                tmp->logoffEpoch = log->ut_time;
 
                tmp->logoff_set = 1;
                break;
            	}
        	}


            tmp = tmp->next;
        }
        //free(newnode);
    } // Else if it is a boot time, set logoff for those who haven't been set
    else if(log->ut_type == BOOT_TIME){

        getTime = log->ut_time;

        tmp = root;

        while(tmp != NULL){

            if(tmp->logoff_set == 0){

                strftime(buffer2, sizeof(buffer2),"%D %H:%M", localtime(&getTime));
                strcpy(tmp->logoff, buffer2);
                tmp->logoffEpoch = log->ut_time;

                tmp->logoff_set = 1;
            }

            tmp = tmp->next;
        }
        //free(newnode);
    }
    else{
        //free(newnode);
    }


}

static void executeCommand(char *command, int socketFd,
                    struct sockaddr *socketAddress, socklen_t socketAddressLen)
/* runs `command` and sends the results back to the client via `socketFd` */
{

	struct utmp log;

    int userReturn = 100;
    /*
     * ASSIGNMENT
     *
     * Implement the following pseudocode:
     *
     * declare a char buffer of RESPONSE_SIZE `response`
     * create a pipe to execute command (hint: popen(3))
     * if that succeeds,
     *     fill `response` with the output of the command (hint: fread(3))
     *     close the pipe (hint: pclose(3))
     * otherwise,
     *     fill `response` with an error message (hint: snprintf(3))
     *     let `responseLength` be its length
     * send `response` to `socketFd` with a "return address" of
     *  `socketAddress` (hint: sendto(2))
     */

    //printf("In tattled\n");

    //printf("Here is command passed: %s\n", command);

    /*char *buf = (char *)calloc(40, sizeof(char));

    strcpy(buf, "noone");*/

    if(strcmp(command, "noone") != 0){
        userReturn = userChecks(command);
    }

    //free(buf);
    

    if(userReturn == 0){

        printf("User doesn't exist\n");

        char* response = calloc(RESPONSE_SIZE + 1, sizeof(char));
        snprintf(response, RESPONSE_SIZE, "User doesn't exist!!\n");
        sendto(socketFd, response, RESPONSE_SIZE, 0, (struct sockaddr*)socketAddress, sizeof(struct sockaddr));
        free(response);

        exit(EXIT_FAILURE);
    }


    struct List *tmp;
    tmp = &Root;

	FILE *fp;

	fp = fopen(WTMP_FILENAME, "r");

    if(fp == NULL) {
       fprintf(stderr, "Failed to open /var/log/wtmp file.\n");
       exit(EXIT_FAILURE);
    }



    char* response = calloc(RESPONSE_SIZE + 1, sizeof(char));
    //char response[RESPONSE_SIZE];

    initializeList(&Root);

    int start = 0;

    while(fread(&log, sizeof(log), 1, fp) != 0){
        addInitialList(&log, &start);
    }

    while(tmp != NULL){

        //printf("Here is the user: %s\n", tmp->ut_user);
        tmp=tmp->next;
    }

    fclose(fp);;

    //FILE *file = popen(command, "r");


    if(fp != NULL){
        tmp = &Root;


        //printf("Before while: \n");

    	while(tmp != NULL){

    		//printf("Here is the size of the node: %d\n", sizeof(tmp));

                
            sendto(socketFd, tmp, sizeof(struct List), 0, (struct sockaddr*)socketAddress, sizeof(struct sockaddr));

    		
    		tmp = tmp->next;
    	}
	}
    else{
    	//snprintf(response, RESPONSE_SIZE, "fin");
    }
    //shutdown(socketFd, SHUT_RDWR);
    //printf("Sending response here!\n");
    
    free(response);
    //exit(EXIT_SUCCESS);
    //sendto(socketFd, response, RESPONSE_SIZE, 0, (struct sockaddr*)socketAddress, sizeof(struct sockaddr));

    
}

//Check to make sure the user actually exists based on input. If not, exit.
int userChecks(char *userNames){

    //List *tmp;

    struct passwd *pwd;

    char *p;

    p = strtok(userNames, ",");
    if(p == NULL){
        return 0;
    }

    //printf("Here is the user: %s\n", p);

    while(p != NULL){
        //tmp = &Root;
        pwd = getpwnam(p);
        if(pwd == NULL){
            fprintf(stderr, "User does not exist!\n");
            return 0;
            exit(EXIT_FAILURE);
        }
        p = strtok(NULL, ",");
    }

    return 1;

}



static int initServer(int port)
{
    /*
     * ASSIGNMENT
     *
     * Implement the following pseudocode:
     *
     * declare a "struct sockaddr_in" `inetSocketAddress`
     * declare a "struct sockaddr" pointer and cast the address of 
     *  `inetSocketAd dress` to it
     * set `inetSockAddress`'s "sin_family" attribute to `AF_INET`
     * set `inetSockAddress`'s "sin_addr.s_addr" attribute to
     *  `INADDR_ANY`
     * set `inetSockAddress`'s port attribute (you'll have to find the
     *  exact name) to `port`
     * let `socketFd` be a datagram socket with family
     *  `socketAddress->sa_family` (hint: socket(2))
     * bind the socket to `socketAddress` (hint: bind(2), and be sure
     *  to use `sizeof(struct sockaddr_in)` as the length of
     *  `socketAddress`
     * if the bind fails,
     *     close `socketFd` (hint: close(2))
     *     return a -1
     * otherwise
     *     return `socketFd`
     */

    struct sockaddr_in inetSockAddress;
    memset(&inetSockAddress, 0, sizeof(inetSockAddress));

    inetSockAddress.sin_family = AF_INET;
    inetSockAddress.sin_addr.s_addr = INADDR_ANY;
    inetSockAddress.sin_port = port;

    int socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(bind(socketfd, (struct sockaddr*) &inetSockAddress, sizeof(struct sockaddr_in)) < 0){
        close(socketfd);
        return -1;
    }else{
        return socketfd;
    }
}


static void logError(char *funcName)
/* note error in `funcName` on the system log (daemon) or stderr (non-daemon) */
{
    if (runAsDaemon)
        syslog(LOG_ERR, "%s error: %s", funcName, strerror(errno));
    else
        fprintf(stderr, "%s error: %s\n", funcName, strerror(errno));
}

void serve(char *hostname, int port)
{
    /*
     * ASSIGNMENT
     *
     * Implement the following pseudocode:
     *
     * start a server on `port` (hint: initServer())
     * if there's an error,
     *     log the error
     *     return
     * loop:
     *     let `commandLength` be the result of reading a
     *      `COMMAND_SIZE` char buffer `command` from `socketFd`,
     *      noting the requestor's `socketAddress` (and its length
     *      `socketAddressLen`, which must be initialised to the size
     *      of the socketAddress) (hint: recvfrom())
     *     make `command` nul-terminated
     *     execute `command` on `socketFd` with a reply to
     *      `socketAddress` (hint: executeCommand())
     */

    int socketFd = initServer(port);

    if(socketFd < 0){
        logError("Unable to initiate the server");
        return;
    }

    while(1){
        char *command = malloc(COMMAND_SIZE);
        //char command[COMMAND_SIZE + 1];

        struct sockaddr_in socketAddress;
        //struct sockaddr from;
        socklen_t socketAddressLen = sizeof(socketAddress);

        memset(&socketAddress, 0, sizeof(socketAddress));

        recvfrom(socketFd, command, COMMAND_SIZE, 0, (struct sockaddr*)&socketAddress, &socketAddressLen);

        char *command2 = malloc(strlen(command) + 1);
        strcpy(command2, command);
        command2[strlen(command)] = '\0';

        //command[COMMAND_SIZE + 1] = '\0';

        executeCommand(command2, socketFd, (struct sockaddr*) &socketAddress, socketAddressLen);

        free(command);
        free(command2);
    }
}


//Help option
void usage(void)
{
    printf("*usage: ./tattle [-u login[, login]*] [-d date (mm/dd/yy)] [-t time (HH:MM)]*\n");
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


static char *getDefaultHostName(void)
{
    char *hostName = NULL;
    int hostNameLen = HOST_NAME_MAX;

    /*
     * Allocate a buffer to hold the host name. If sysconf() provides
     * a maximum host name length, get it. Otherwise, use
     * HOST_NAME_MAX.
     */
#ifdef _SC_HOST_NAME_MAX
    hostNameLen = sysconf(_SC_HOST_NAME_MAX);
    if (hostNameLen < 0)                  /* best guess */
        hostNameLen = HOST_NAME_MAX;
#endif
    /* Allocate a buffer to hold the host name. */
    hostName = malloc((hostNameLen+1) * sizeof(char)); // allow for nul-term
    SYSCALL_CHECK(gethostname(hostName, hostNameLen));
    return hostName;
}




int main(int argc, char *argv[]){

	int ch;
	int port = -1;

	char *hostname = getDefaultHostName();



    while((ch = getopt(argc, argv, "hdp:")) != -1){
        switch(ch){
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
            case 'd':
	            runAsDaemon = 1;
	            break;

            case 'p':
	            //port = atoi(optarg);
	            break;

            default:
	            fprintf(stderr, "unknown option \"-%c\" -- exiting\n", ch);
	            exit(EXIT_FAILURE);

        }
        
    }


    port = DEFAULT_PORT;
    

    if (port < MIN_USER_PORT) {
        fprintf(stderr, "port must be at least %d -- exiting\n", MIN_USER_PORT);
        exit(EXIT_FAILURE);
    }


    //create the daemon on the host that is running
   	if (runAsDaemon){
   		printf("Running as Daemon!\n");
        daemonizeMe(argv[0]);
   	}

   	serve(hostname, port);

   	free(hostname);

    exit(EXIT_FAILURE);
	
}
