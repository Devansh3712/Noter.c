/*
 * =================================================
 *
 *      Filename        main.c
 *      Authors         Devansh Singh <nbtg14124@mail.jiit.ac.in>
 *                      Chirag Tyagi <nbtg14814@mail.jiit.ac.in>
 *      Description     Library for CRUD (Create, Read, Update, Delete)
 *                      functions of users
 *
 * =================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#define LIMIT 100

struct User{
    char username[LIMIT];
    char password[LIMIT];
};

void checkNotesDirectory(){
    char path[] = "./notes/";
    struct stat st = {0};

    if (stat(path, &st) == -1){
        #if defined(_WIN32)
        CreateDirectory(path, NULL);
        #else 
        mkdir(path, 0700); 
        #endif
    }
}

void createUserDirectory(char username[LIMIT]){
    checkNotesDirectory();

    char path[] = "./notes/";
    strcat(path, username);
    struct stat st = {0};

    if (stat(path, &st) == -1){
        #if defined(_WIN32)
        CreateDirectory(path, NULL);
        #else 
        mkdir(path, 0700);
        #endif
    }
}

bool createUser(char username[LIMIT], char password[LIMIT]){
    createUserDirectory(username);
    struct User user;
    char path[] = "./notes/";

    strcpy(user.username, username);
    strcpy(user.password, password);

    FILE *outfile;
    strcat(path, username);
    strcat(path, "/user.dat");
    outfile = fopen(path, "wb");
    if(outfile == NULL){
        return false;
    }
    fwrite(&user, sizeof(struct User), 1, outfile);
    if(fwrite == 0){
        return false;
    }
    fclose(outfile);

    return true;
}

bool authUser(char username[LIMIT], char password[LIMIT]){
    char path[] = "./notes/";
    strcat(path, username);
    strcat(path, "/user.dat");

    struct stat st = {0};
    struct User user;

    if (stat(path, &st) == -1){
        return false;
    }

    FILE *infile;
    infile = fopen(path, "rb");
    if(infile == NULL){
        return false;
    }
    fread(&user, sizeof(struct User), 1, infile);
    if(fread == 0){
        return false;
    }
    int value = strcmp(user.password, password);
    if(value != 0){
        return false;
    }
    fclose(infile);

    return true;
}

bool updateUserPassword(char username[LIMIT], char newPassword[LIMIT]){
    char path[] = "./notes/", updatePath[255];
    strcat(path, username);
    strcat(path, "/user.dat");
    strcpy(updatePath, path);

    struct User user;
    struct User updatedUser;

    FILE *infile;
    infile = fopen(path, "rb");
    if(infile == NULL){
        return false;
    }
    fread(&user, sizeof(struct User), 1, infile);
    if(fread == 0){
        return false;
    }
    strcpy(updatedUser.username, user.username);
    strcpy(updatedUser.password, newPassword);
    fclose(infile);

    FILE *outfile;
    outfile = fopen(updatePath, "wb");
    if(outfile == NULL){
        return false;
    }
    fwrite(&updatedUser, sizeof(struct User), 1, outfile);
    if(fwrite == 0){
        return false;
    }
    fclose(outfile);

    return true;
}

bool deleteUser(char username[LIMIT]){
    #ifdef _WIN32
    char command[100];
    sprintf(command, "rmdir \"./notes/%s\" /S /Q", username);
    system(command);
    return true;
    #else 
    char command[100];
    sprintf(command, "rm -rf ./notes/%s", username);
    system(command);
    return true;
    #endif
}
