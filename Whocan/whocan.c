/*
    Beau Morton
    PA2 Whocan
    20170220

*/
#define _GNU_SOURCE // for asprintf(), if needed
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#define USERBUFFER 32

void directoryCheck(char *fileName, char *dirValue);
int fileCompare(char *X, char *Y);
void optionCD(char *userPath);

char *options[7] = {"cd", "delete", "execute", "ls", "read", "search", "write"};

typedef struct List {
    int hasPermissions; 
    char userName[USERBUFFER];
    int groupFound;
    int gid;
    int uid;
    int ngroups;
    gid_t *groups;
    struct List *nextList;
} List;

List Root;

void initializeList(List *node){
    node->hasPermissions = 1;
    node->gid = 0;
    node->uid = 0;
    node->nextList = 0;
    node->ngroups = 0;
    node->groupFound = 0;
    node->groups = NULL;
}

void deleteList(List *head){
    List *temp, *next;
    temp = head->nextList;

    while(temp != NULL){
        next = temp->nextList;
        free(temp->groups);
        free(temp);
        temp = next;
    }
}

void printList(List *user, int zeroList){

    if(zeroList != 1){
        int notEverybody = 0;
        int someone = 0;

        List *temp;
        temp = user->nextList;

        while(temp != NULL)
        {
            if(temp->hasPermissions == 0){
                notEverybody = 1;
            }
            if(temp->hasPermissions == 1){
                someone = 1;
            }

            temp = temp->nextList;
        }

        if(notEverybody == 0){
            printf("(everyone)\n");
        }
        else{
            temp = user->nextList;

            while(temp != NULL){

                if(zeroList == 2){
                    if(temp->uid == 0 && someone == 1){
                        temp->hasPermissions = 1;
                    }                    
                }
                else if(zeroList != 2 && temp->uid == 0){
                    temp->hasPermissions = 1;
                } 

                if(temp->hasPermissions == 1){
                    printf("%s\n", temp->userName);
                }
                temp = temp->nextList;
            }
        }
    }
}

void sortList(List *head, List *current){
    List *temp;
    temp = head;
    int tuid, tgid, tempngroups;
    char tname[32];
    gid_t *groupArray;

    while(temp != NULL){
        if(strcmp(temp->userName, current->userName) > 0){
            strcpy(tname, temp->userName);
            tuid = temp->uid;
            tgid = temp->gid;
            tempngroups = temp->ngroups;
            groupArray = temp->groups;
            strcpy(temp->userName, current->userName);
            temp->uid = current->uid;
            temp->gid = current->gid;
            temp->ngroups = current->ngroups;
            temp->groups = current->groups;
            strcpy(current->userName, tname);
            current->uid = tuid;
            current->gid = tgid;
            current->ngroups = tempngroups;
            current->groups = groupArray;
        }
        temp = temp->nextList;
    }


}

void getGroupInfo(List *node) {

    if (node->userName != NULL) {

        node->ngroups = 0;
        node->groups = NULL;

        // Get group list. This returns the exact size and mallocs it back.
        if (getgrouplist(node->userName, node->gid, NULL, &node->ngroups) < 0) {
            node->groups = (gid_t *) malloc(node->ngroups * sizeof (gid_t));
            getgrouplist(node->userName, node->gid, node->groups, &node->ngroups);
         }
    }

    
}

void addList(List *item, int uid, int gid, char *user, int iteration){

    List *newnode = malloc(sizeof(List));
    char *buf;
    asprintf(&buf, "%s", user);
    List *temp;
    temp = item;

    initializeList(newnode);
   
    if(iteration == 0){
        strncpy(newnode->userName, buf, 32);
        newnode->gid = gid;
        newnode->uid = uid;
        newnode->groupFound = 0;
        newnode->nextList = NULL;
        item->nextList = newnode;
        getGroupInfo(newnode);
    }
    else if(iteration >= 1){

        while(temp->nextList != NULL)
        {
            temp = temp->nextList;
        }

        strncpy(newnode->userName, buf, 32);
        newnode->gid = gid;
        newnode->uid = uid;
        newnode->groupFound = 0;
        newnode->nextList = NULL;
        temp->nextList = newnode;
        getGroupInfo(newnode);

        sortList(item, temp->nextList);

    }
    free(buf);
}

int userCheck(char *argument){

    int result;

    struct stat fileStat;

    if(stat(argument,&fileStat) < 0)    
                return 1;

    if((fileStat.st_mode & S_IRUSR) && !(fileStat.st_mode & S_IWUSR) && !(fileStat.st_mode & S_IXUSR)){
        result = 100;
        return result;
    }
    else if((fileStat.st_mode & S_IRUSR) && (fileStat.st_mode & S_IWUSR) && !(fileStat.st_mode & S_IXUSR)){
        result = 110;
        return result;
    }
    else if((fileStat.st_mode & S_IRUSR) && !(fileStat.st_mode & S_IWUSR) && (fileStat.st_mode & S_IXUSR)){
        result = 101;
        return result;
    }
    else if((fileStat.st_mode & S_IRUSR) && (fileStat.st_mode & S_IWUSR) && (fileStat.st_mode & S_IXUSR)){
        result = 111;
        return result;
    }
    else if(!(fileStat.st_mode & S_IRUSR) && (fileStat.st_mode & S_IWUSR) && (fileStat.st_mode & S_IXUSR)){
        result = 11;
        return result;
    }
    else if(!(fileStat.st_mode & S_IRUSR) && (fileStat.st_mode & S_IWUSR) && !(fileStat.st_mode & S_IXUSR)){
        result = 10;
        return result;
    }
    else if(!(fileStat.st_mode & S_IRUSR) && !(fileStat.st_mode & S_IWUSR) && (fileStat.st_mode & S_IXUSR)){
        result = 1;
        return result;
    }
    else{ 
        //Need this if there aren't any permissions set
        result = 0;
        return result;
    }


}

int otherCheck(char *argument){

    int result;

    struct stat fileStat;

    if(stat(argument,&fileStat) < 0)    
                return 1;

    if((fileStat.st_mode & S_IROTH) && !(fileStat.st_mode & S_IWOTH) && !(fileStat.st_mode & S_IXOTH)){
        result = 100;
        return result;
    }
    else if((fileStat.st_mode & S_IROTH) && (fileStat.st_mode & S_IWOTH) && !(fileStat.st_mode & S_IXOTH)){
        result = 110;
        return result;
    }
    else if((fileStat.st_mode & S_IROTH) && !(fileStat.st_mode & S_IWOTH) && (fileStat.st_mode & S_IXOTH)){
        result = 101;
        return result;
    }
    else if((fileStat.st_mode & S_IROTH) && (fileStat.st_mode & S_IWOTH) && (fileStat.st_mode & S_IXOTH)){
        result = 111;
        return result;
    }
    else if(!(fileStat.st_mode & S_IROTH) && (fileStat.st_mode & S_IWOTH) && (fileStat.st_mode & S_IXOTH)){
        result = 11;
        return result;
    }
    else if(!(fileStat.st_mode & S_IROTH) && (fileStat.st_mode & S_IWOTH) && !(fileStat.st_mode & S_IXOTH)){
        result = 10;
        return result;
    }
    else if(!(fileStat.st_mode & S_IROTH) && !(fileStat.st_mode & S_IWOTH) && (fileStat.st_mode & S_IXOTH)){
        result = 1;
        return result;
    }
    else{ 
        //Need this if there aren't any permissions set
        result = 0;
        return result;
    }
}

int groupCheck(char *argument){

    int result;

    struct stat fileStat;

    if(stat(argument,&fileStat) < 0)    
                return 1;

    if((fileStat.st_mode & S_IRGRP) && !(fileStat.st_mode & S_IWGRP) && !(fileStat.st_mode & S_IXGRP)){
        result = 100;
        return result;
    }
    else if((fileStat.st_mode & S_IRGRP) && (fileStat.st_mode & S_IWGRP) && !(fileStat.st_mode & S_IXGRP)){
        result = 110;
        return result;
    }
    else if((fileStat.st_mode & S_IRGRP) && !(fileStat.st_mode & S_IWGRP) && (fileStat.st_mode & S_IXGRP)){
        result = 101;
        return result;
    }
    else if((fileStat.st_mode & S_IRGRP) && (fileStat.st_mode & S_IWGRP) && (fileStat.st_mode & S_IXGRP)){
        result = 111;
        return result;
    }
    else if(!(fileStat.st_mode & S_IRGRP) && (fileStat.st_mode & S_IWGRP) && (fileStat.st_mode & S_IXGRP)){
        result = 11;
        return result;
    }
    else if(!(fileStat.st_mode & S_IRGRP) && (fileStat.st_mode & S_IWGRP) && !(fileStat.st_mode & S_IXGRP)){
        result = 10;
        return result;
    }
    else if(!(fileStat.st_mode & S_IRGRP) && !(fileStat.st_mode & S_IWGRP) && (fileStat.st_mode & S_IXGRP)){
        result = 1;
        return result;
    }
    else{ 
        //Need this if there aren't any permissions set
        result = 0;
        return result;
    }

}

void setRoot(int choice){
    List *temp;
    temp = &Root;
    temp = temp->nextList;

    while(temp != NULL){
        if(temp->uid == 0){
            temp->hasPermissions = 1;
        }
        else
            temp->hasPermissions = 0;

        temp = temp->nextList;
    }
}

//Permissions check on parent directory when wanting to delete
void permissionsCheckParentDelete(char *argument){

    List *temp;
    temp = &Root;
    temp = temp->nextList;
    struct stat fileStat;
    int result = 0;

    stat(argument, &fileStat);

    while(temp != NULL){

        if(temp->hasPermissions == 1){
            if(fileStat.st_uid == temp->uid){

                result = userCheck(argument);

                if(result == 111 || result == 11){
                    temp->hasPermissions = 1;
                }
                else
                    temp->hasPermissions = 0;                        
            }
            else if((fileStat.st_uid != temp->uid)){

                for(int i = 0; i < temp->ngroups; i++){

                    if((fileStat.st_gid == temp->groups[i])){

                    result = groupCheck(argument);

                        if(result == 111 || result == 11){
                            temp->hasPermissions = 1;
                            
                        }
                        else{
                            temp->hasPermissions = 0;
                        }
                        temp->groupFound = 1;
                        
                    }
                }                
            }
            if((temp->groupFound != 1) && (fileStat.st_uid != temp->uid)){

                result = otherCheck(argument);

                if(result == 111 || result == 11){
                    temp->hasPermissions = 1;
                }
                else
                    temp->hasPermissions = 0;
            }
    }


    temp = temp->nextList;
    }

    
}

//Permissions check when trying to read or ls on fsobj
void permissionsCheckReadandLs(char *argument){

    List *temp;
    temp = &Root;
    temp = temp->nextList;
    struct stat fileStat;
    int result;

    stat(argument, &fileStat);

    while(temp != NULL){

        if(temp->hasPermissions == 1){
            if(fileStat.st_uid == temp->uid){

                result = userCheck(argument);

                if(result == 111 || result == 110 || result == 101 || result == 100){
                    temp->hasPermissions = 1;
                }
                else
                    temp->hasPermissions = 0;                        
            }
            else if((fileStat.st_uid != temp->uid)){

                for(int i = 0; i < temp->ngroups; i++){

                    if((fileStat.st_gid == temp->groups[i])){
                        result = groupCheck(argument);

                        if(result == 111 || result == 110 || result == 101 || result == 100){
                            temp->hasPermissions = 1;
                        }
                        else
                            temp->hasPermissions = 0; 

                        temp->groupFound = 1;
                    }
                }
                    
            }
            if((temp->groupFound != 1) && (fileStat.st_uid != temp->uid)){

                result = otherCheck(argument);

                if(result == 111 || result == 110 || result == 101 || result == 100){
                    temp->hasPermissions = 1;
                }
                else
                    temp->hasPermissions = 0;
            }  
        }


    temp = temp->nextList;
    }

    
}

//Permissions check when trying to read or ls a directory fsobj specifically
void permissionsCheckReadandLsDirectory(char *argument){

    List *temp;
    temp = &Root;
    temp = temp->nextList;
    struct stat fileStat;
    int result;

    stat(argument, &fileStat);

    while(temp != NULL){

        if(temp->hasPermissions == 1){
            if(fileStat.st_uid == temp->uid){

            result = userCheck(argument);

            if(result == 111 || result == 101){
                temp->hasPermissions = 1;
            }
            else
                temp->hasPermissions = 0;                        
            }
            else if((fileStat.st_uid != temp->uid)){

                for(int i = 0; i < temp->ngroups; i++){

                    if((fileStat.st_gid == temp->groups[i])){

                        result = groupCheck(argument);

                        if(result == 111 || result == 101){
                            temp->hasPermissions = 1;
                        }
                        else
                            temp->hasPermissions = 0;

                        temp->groupFound = 1;    
                    }
                                  
                }
            }
            if((temp->groupFound != 1) && (fileStat.st_uid != temp->uid)){

                result = otherCheck(argument);

                if(result == 111 || result == 101){
                    temp->hasPermissions = 1;
                }
                else
                    temp->hasPermissions = 0;
            }
        }
 
        temp = temp->nextList;
    }

    
}

//Permissions check when trying to write to a fsobj directory
void permissionsCheckWriteDirectory(char *argument){

    List *temp;
    temp = &Root;
    temp = temp->nextList;
    struct stat fileStat;
    int result;

    stat(argument, &fileStat);

    while(temp != NULL){

        if(temp->hasPermissions == 1){
            if(fileStat.st_uid == temp->uid){

            result = userCheck(argument);

            if(result == 111 || result == 11){
                temp->hasPermissions = 1;
            }
            else
                temp->hasPermissions = 0;                        
            }
            else if((fileStat.st_uid != temp->uid)){

                for(int i = 0; i < temp->ngroups; i++){

                    if((fileStat.st_gid == temp->groups[i])){
                
                        result = groupCheck(argument);

                        if(result == 111 || result == 11){
                            temp->hasPermissions = 1;
                        }
                        else
                            temp->hasPermissions = 0;

                        temp->groupFound = 1;
                    }
                }
            }
            if((temp->groupFound != 1) && (fileStat.st_uid != temp->uid)){

                result = otherCheck(argument);

                if(result == 111 || result == 11){
                    temp->hasPermissions = 1;
                }
                else
                    temp->hasPermissions = 0;
            }
        }

        temp = temp->nextList;
    }

    
}


//Permissions check when trying to write to something that isn't a fsobj dir
void permissionsCheckWrite(char *argument){

    List *temp;
    temp = &Root;
    temp = temp->nextList;
    struct stat fileStat;
    int result;

    stat(argument, &fileStat);

    while(temp != NULL){

        if(temp->hasPermissions == 1){
            if(fileStat.st_uid == temp->uid){

            result = userCheck(argument);

            if(result == 111 || result == 110 || result == 11 || result == 10){
                temp->hasPermissions = 1;
            }
            else
                temp->hasPermissions = 0;                        
            }
            else if((fileStat.st_uid != temp->uid)){

                for(int i = 0; i < temp->ngroups; i++){

                    if((fileStat.st_gid == temp->groups[i])){
                
                        result = groupCheck(argument);

                        if(result == 111 || result == 110 || result == 11 || result == 10){
                            temp->hasPermissions = 1;
                        }
                        else
                            temp->hasPermissions = 0;

                        temp->groupFound = 1;
                    }
                }
            }
            if((temp->groupFound != 1) && (fileStat.st_uid != temp->uid)){

                result = otherCheck(argument);

                if(result == 111 || result == 110 || result == 11 || result == 10){
                    temp->hasPermissions = 1;
                }
                else
                    temp->hasPermissions = 0;
            }
        
        }
        temp = temp->nextList;
    }   
}

//Permissions check when trying to cd a directory
void permissionsCheck(char *argument){

    List *temp;
    temp = &Root;
    temp = temp->nextList;
    struct stat fileStat;
    int result = 0;

    stat(argument, &fileStat);

    while(temp != NULL){

        if(temp->hasPermissions == 1){
            if(fileStat.st_uid == temp->uid){

            result = userCheck(argument);

            if(result == 111 || result == 101 || result == 11 || result == 1){
                temp->hasPermissions = 1;
            }
            else
                temp->hasPermissions = 0;                        
            }
            else if((fileStat.st_uid != temp->uid)){

                for(int i = 0; i < temp->ngroups; i++){

                    if((fileStat.st_gid == temp->groups[i])){
                
                        result = groupCheck(argument);

                        if(result == 111 || result == 101 || result == 11 || result == 1){
                            temp->hasPermissions = 1;
                        }
                        else
                            temp->hasPermissions = 0;

                        temp->groupFound = 1;
                    }
                }
            }
            if((temp->groupFound != 1) && (fileStat.st_uid != temp->uid)){

                result = otherCheck(argument);

                if(result == 111 || result == 101 || result == 11 || result == 1){
                    temp->hasPermissions = 1;
                }
                else
                    temp->hasPermissions = 0;
            }
        }

    temp = temp->nextList;
    }

    
}

//Permissions check when the sticky bit is set on the parent directory of fsobj trying to delete
void permissionsCheckParentDeleteSticky(char *argument){
    List *temp;
    temp = &Root;
    temp = temp->nextList;
    struct stat fileStat;
    char buf[PATH_MAX]; 

    char *getPath = realpath(argument, buf);

    stat(getPath, &fileStat);

    while(temp != NULL){
        if(fileStat.st_uid == temp->uid || temp->uid == 0){
            temp->hasPermissions = 1;
        }
        else
            temp->hasPermissions = 0;

        temp = temp->nextList;
    }
}

//Checking the parent of delete
int getParent(char *path){

    char *lastSlash = NULL;
    int result = 0;

    if((lastSlash = strrchr(path, '/'))){
        *lastSlash = '\0';
    }
       
    if(path[0] == '\0'){
        result = 1;
    }
    return result;
}

//Start to apppend path as it is chopped up in cut up
void createPaths(char *path, int loop, char *newPath){

    char slash[2];
    slash[0] = '/';
    slash[1] = '\0';

    if(loop == 0){
        //Send this to check user check
        permissionsCheck(slash);
    }
        
    strcat(newPath, slash);
    strcat(newPath, path);

    permissionsCheck(newPath);

}

//Need to add realpath here in case user uses . / ~
void cutUpDatShit(char *path){

    char newPath[PATH_MAX];
    newPath[0] = '\0';

    char *token = strtok(path, "/");

    int loop = 0;

    while(token != NULL){
        createPaths(token, loop, newPath);
        token = strtok(NULL, "/");
        loop++;
    }
}

//Check if the user insert root
int rootCheck(char *userPath){

    char slash[2];
    slash[0] = '/';
    slash[1] = '\0';

    int result;

    if(strcmp(slash, userPath) == 0){
        result = 1;
        return result;
    }
    else
        result = 0;
    return result;
}

//User chose cd
void optionCD(char *userPath){

    int root;

    root = rootCheck(userPath);

    if(root == 1){
        return; //All users should be able to cd into the root directory, so return   
    }
    
    char buf[PATH_MAX];

    char *getPath = NULL;

    getPath = realpath(userPath, buf); //This is going to get the full path, and resolve any paths that are symlinks

    cutUpDatShit(getPath);
    
}
//User chose delete option
void optionDelete(char *userPath){

    struct stat fileStat;
    char *returnPath;
    int parentResult;

    int root = 0;

    root = rootCheck(userPath);

    if(root == 1){
        //need to set only root with capability here
        setRoot(100);
        return;  
    }

    char buf[PATH_MAX];

    returnPath = realpath(userPath, buf);

    parentResult = getParent(returnPath);
    
    if(parentResult == 1){
        char slash[2];
        slash[0] = '/';
        slash[1] = '\0';
        returnPath = slash;
    }
    
    stat(returnPath, &fileStat);

    //if sticky is set send to handle the sticky
    if(fileStat.st_mode & S_ISVTX){
        optionCD(returnPath); //check to see if user can get to directory

        permissionsCheckParentDeleteSticky(userPath);
    }
    else{
        optionCD(returnPath); //check to see if user can get to directory

        permissionsCheckParentDelete(returnPath); //Now, specifically check the parent permissions needed
    }

}

//User chose ls
void optionLS(char *userPath){

    int root, parentResult;

    struct stat fileStat;

    root = rootCheck(userPath);

    if(root == 1){
        return; //All users should be able to ls the root directory, so return   
    }
    
    char bufPath[PATH_MAX], bufParent[PATH_MAX];

    char *getPath, *getParentPath;
    
    getPath = realpath(userPath, bufPath); //This is going to get the full path, and resolve any paths that are symlinks

    getParentPath = realpath(userPath, bufParent);

    parentResult = getParent(getParentPath);
    
    if(parentResult == 1){
        char slash[2];
        slash[0] = '/';
        slash[1] = '\0';
        getParentPath = slash;
    }
    
    stat(getPath, &fileStat);

    optionCD(getParentPath); //check --x permissions

    if(S_ISDIR(fileStat.st_mode)){
        permissionsCheckReadandLsDirectory(getPath);
    }
    else
        permissionsCheckReadandLs(getPath);    
}

//User chose ls for file or device
void optionLSFileorDevice(char *userPath){

    int parentResult;
  
    char bufPath[PATH_MAX];

    char *getParentPath;

    getParentPath = realpath(userPath, bufPath);

    parentResult = getParent(getParentPath);
    
    if(parentResult == 1){
        char slash[2];
        slash[0] = '/';
        slash[1] = '\0';
        getParentPath = slash;
    }

    optionCD(getParentPath); //check --x permissions
    
}

//User chose write
void optionWrite(char *userPath){

    int root, parentResult;

    struct stat fileStat;

    root = rootCheck(userPath);

    if(root == 1){
        //Only root should be able to write to root directory
        setRoot(100);
        return;
    }

    char bufPath[PATH_MAX], bufParent[PATH_MAX];

    char *getPath, *getParentPath;
    
    getPath = realpath(userPath, bufPath); //This is going to get the full path, and resolve any paths that are symlinks

    getParentPath = realpath(userPath, bufParent);

    stat(getPath, &fileStat);

    parentResult = getParent(getParentPath);
    
    if(parentResult == 1){
        char slash[2];
        slash[0] = '/';
        slash[1] = '\0';
        getParentPath = slash;
    }

    optionCD(getParentPath); //check for --x all the way down

    if(S_ISDIR(fileStat.st_mode)){
        permissionsCheckWriteDirectory(getPath);
    }
    else
        permissionsCheckWrite(getPath);
}

/* issue a usage error message */
void usage(void)
{
    fprintf(stderr,
            "usage: ./whocan [{args}] [{fsobj}]*\n");
    fprintf(stderr, "%s\n",
            " {args} are:");
    fprintf(stderr, "%s",
        "  cd                               change directory\n"
        "  delete                           delete fsobj\n"
        "  execute                          execute fsobj\n"
        "  ls                               list fsobj\n"
        "  read                             read fsobj\n"
        "  search                           search fsobj\n"
        "  write                            write fsobj\n\n"
        );
}

//We will do an initial check of the fsobj in question, if it doesn't meet the end
//requirements kick out
int initialCheckList(char *original, char *command){

    struct stat fileStat;

    char buf[PATH_MAX];

    char *path;

    path = realpath(original, buf);

    stat(path, &fileStat);

    int choices = 10;
    int nonsense = 0;

    for(int i = 0; i < 7; i++){
    
        if(strcmp(command, options[i]) == 0){
            choices = i;
        }
    }

    if(choices == 0){
        if(S_ISDIR(fileStat.st_mode)){       
            optionCD(original);
        }
        else{
            nonsense = 1;
        }    
    }
    else if(choices == 1){                  
        optionDelete(original);
    }
    else if(choices == 2){                
        if(S_ISDIR(fileStat.st_mode)){
            nonsense = 1;
        }
        else{
            optionCD(original);
            nonsense = 2; //return 2 because not even root can execute a file if there aren't any bit execute bits set
        }
    }
    else if(choices == 3){              
    	if(S_ISDIR(fileStat.st_mode)){
            optionLS(original);
        }else
            optionLSFileorDevice(original);
        
    }
    else if(choices == 4){                
        optionLS(original);
    }
    else if(choices == 5){               
        if(S_ISDIR(fileStat.st_mode)){
            optionCD(original);
        }
        else{
            nonsense = 1;
        }
    }
    else if(choices == 6){              
        optionWrite(original); 
    }
    else if(choices == 10){
        usage();
        nonsense = -1;
    }

    return nonsense;
}

int main(int argc, char *argv[])
{
    struct passwd *pwd; //this will be used to get uid and gid
    struct stat fileStat;
    int whatToPrint, loop;

    if(argc != 3){
        usage();
        return -1;
    }

    if(stat(argv[2],&fileStat) < 0){
        // use this when error is implemented
        fprintf(stderr, "Errno: %d\n", errno);
        perror("Error");    
        return (-1);
    } 

    initializeList(&Root); 

    loop = 0;

    //this will print out all the users on the system uid and gid
    while((pwd = getpwent()) != 0){
        //printf("%-8s %d %d\n", pwd->pw_name, pwd->pw_uid, pwd->pw_gid);
        addList(&Root, pwd->pw_uid, pwd->pw_gid, pwd->pw_name, loop);
        loop++;
    }
    endpwent();

    whatToPrint = initialCheckList(argv[2], argv[1]);

    if(whatToPrint != -1){
        printList(&Root, whatToPrint);
    }
              
    deleteList(&Root);

    return 0;
}
