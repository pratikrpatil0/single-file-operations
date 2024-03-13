//-------------------------------|
// Edited By:- Pratik and Ishaan |
// Date:- 13/2/24                |
//-------------------------------|
 

#include <stdio.h> /* using for the input/output function */
#include <errno.h> /* using to return the error codes. errno,  */
#include <string.h> /* manipulation of strings */
#include <fcntl.h> /* manipulation of the file descriptor. O_EXCL , O_CREAT, open() */
#include <unistd.h> /* for some system calls and the important functions. write() */
#include <sys/stat.h> /* display file or file system status. S_IRWXU ,  */
#include <stdlib.h> /* for atoi function, atoi converts string to integer */

int createFileDir(char *path , char *flag){
    int fileDescriptor;

    if(strcmp("-f" , flag) == 0){

        fileDescriptor = open(path , O_CREAT | O_EXCL, S_IRWXU);
        if(fileDescriptor == -1){
            return errno;
        }

        close(fileDescriptor);
        fileDescriptor = errno;
    }
    else if(strcmp("-d" , flag) == 0){
        fileDescriptor = mkdir(path, S_IRWXU);
        fileDescriptor = errno;
    }

    return fileDescriptor;
}

int appendText(char *path , char *text){

    int fileDescriptor = open(path , O_WRONLY | O_APPEND);
    if(fileDescriptor == -1){
        return errno;
    }
    int size = 0;
    int index = 0;

    char buffer[1];
    int status = 0;

    while(text[index] != '\0' && size <= 50){
        buffer[0] = text[index];
        status = write(fileDescriptor , buffer , 1);
        if(status == -1){
            return errno;
        }
        size = size + status;
        index++;

    }

    close(fileDescriptor);
        return errno;   

}


int fdRename(char *oldPath, char *newPath) {
    int newName = rename(oldPath, newPath);
    if(newName == -1){
        return errno;
    }

    return newName;
}

int appendOdd(char *path, char *num){
    int n = atoi(num);   // atoi converts string to integer , stdlib
    if(n < 50 || n > 200){
        return -1;
    }
    if(n%2 != 1){
        n = n + 1;
    }

    int size = 0;
    int fileDescriptor = open(path, O_WRONLY | O_APPEND);
    if(fileDescriptor == -1){
        return errno;
    }

    int status = 0;

    while(size <= 50){
        if(n > 200){
            break;
        }
        char buffer[5];
        sprintf(buffer , "%d" , n); // sprintf - it converts number to string 
        status = write(fileDescriptor , buffer , strlen(buffer));
        if(status == -1){
            return errno;
        }
        size = size + status;
        n = n + 2;
    }

    close(fileDescriptor);

    return errno;
}

int outputToCmd(char *path){
    int fileDescriptor = open(path , O_RDONLY);
    if(fileDescriptor == -1){
        return errno;
    }

    char buffer[50];
    int readStatus = read(fileDescriptor, buffer , 50);
    if(readStatus == -1){
        return errno;
    }

    int writeStatus = write(1, buffer , 50);  /* 1 is for standard output */
    if(writeStatus == -1){
        return errno;
    }

    close(fileDescriptor);
    return errno;
}


int checkDir(char *path){
    struct stat directory;

    int status = stat(path, &directory);
    if(status == -1){
        return errno;
    }

    return S_ISDIR(directory.st_mode);
}


int deleteFileDir(char *path){
    int status;
    if(checkDir(path)){
        status = rmdir(path);
        if(status == -1){
             return errno;
        }
    }
    else{
        status = unlink(path); /* delete file */
        if(status == -1){
            return errno;
        }
    }
       
    return 0;
}



int main(int argc , char *argv[]){

    char path[100] = "";
    char newPath[100] = "";
    char option[10] = "";    /* state the functionality or command*/
    char flag[10] = "";
    char text[50] = "";
    char num[20] = "";

    if(argc < 3 || argc > 5){
        return -1;
    }


    for(int i = 0 ; i < argc; i++){
        if(argv[i][0] == '-' && i+1 < argc){
            if(strlen(argv[i]) != 2){
                return -1;
            }
        char c = argv[i][1];
            if(c == 'c' || c == 'a' || c == 'x' || c == 'p' || c == 'r'){
                if(strlen(option)){
                    return -1;
                }
                if(c != 'c'){
                    strcat(path,argv[i+1]);
                }
                strcat(option, argv[i]);
                if (c == 'r'){
                    if(i + 2 < argc){
                        strcat(newPath, argv[i+2]);
                    }
                    else{
                        return -1;
                    }
                }
            }else if(c == 't' || c == 'n'){
                if(strlen(flag) == 0){
                    if(c == 't'){
                        strcat(text , argv[i+1]);
                    }
                    else{
                        strcat(num, argv[i+1]);
                    }
                    strcat(flag, argv[i]);
                }
                else{
                    return -1;
                }
            }
            else if(c == 'f' || c == 'd'){
                if(strcmp(option , "-c") == 0 && strlen(flag) == 0){
                    strcat(flag , argv[i]);
                    strcat(path , argv[i+1]);
                }
                else{
                    return -1;
                }
            }
            else{
                return -1;
            }
        }
        else if(argv[i][0] == '-' && i+1 == argc){
            return -1;
        }
    }

    if(strlen(option) == 0 && strlen(flag)){
        return -1;
    }

    if(strlen(option)){
        if(option[1] == 'c'){
            if(strlen(flag)){
                return createFileDir(path, flag);
            }
            else{
                return -1;
            }

        }
        else if(option[1] == 'a'){
            if(flag){
                if(checkDir(path)){
                    return -1;
                }
                if(strcmp(flag , "-t") == 0){
                    return appendText(path, text);
                }
                else{
                    return appendOdd(path, num);
                }
            }
            else{
                return -1;
            }
        }
        else if(option[1] == 'r'){
            if(access(newPath, F_OK) != -1){
                return -1;
            }
            return fdRename(path, newPath);
        }
        else if(option[1] == 'x'){
            return deleteFileDir(path);
        }
        else if(option[1] == 'p'){
            if (checkDir(path)){
                return -1;
            }
            return outputToCmd(path);
        }
        else{
            return -1;
        }
    }


    return 0;
}




