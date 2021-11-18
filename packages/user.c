/*
 * ====================================================================
 *
 *      Filename        main.c
 *      Authors         Devansh Singh <nbtg14124@mail.jiit.ac.in>
 *                      Chirag Tyagi <nbtg14814@mail.jiit.ac.in>
 *      Description     Library for CRUD (Create, Read, Update, Delete)
 *                      functions of users
 *
 * ====================================================================
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
#define PATH "./notes/"

/*
 * @struct User
 * @brief This structure is for storing the login details of a user
 * @var User::username
 * Member 'username' stores the username of a user
 * @var User::password
 * Member 'password' stores the password of a user
 */
struct User{
    char username[LIMIT];
    char password[LIMIT];
};

/*
 * Check if the `notes` directory exists, if it doesn't
 * create the directory
 */
void checkNotesDirectory(){
    struct stat st = {0};

    if (stat(PATH, &st) == -1){ // path doesn't exist
        #if defined(_WIN32)
        CreateDirectory(PATH, NULL);
        #else 
        mkdir(PATH, 0700); 
        #endif
    }
}

/*
 * Check if the directory dedicated to user exists, if
 * it doesn't create the directory
 * 
 * @param username  Username of user
 */
void createUserDirectory(char username[]){
    checkNotesDirectory();

    char path[300];
    sprintf(path, "./notes/%s", username); // path for the user directory
    struct stat st = {0};

    if (stat(path, &st) == -1){ // path doesn't exist
        #if defined(_WIN32)
        CreateDirectory(path, NULL);
        #else 
        mkdir(path, 0700);
        #endif
    }
}

/*
 * Create a user
 *
 * @param username  Username of the user
 * @param password  Password of the user
 * @return bool     True if user is created else false
 */
bool createUser(char username[], char password[]){
    createUserDirectory(username);
    struct User user;
    char path[300];
    sprintf(path, "./notes/%s/user.dat", username); // path of file to store user data

    strcpy(user.username, username);
    strcpy(user.password, password);

    FILE *outfile;
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

/*
 * Check if the user exists and authorize user password
 *
 * @param username  Username of the user
 * @param password  Password of the user
 * @return bool     True if the user password is correct else false
 */
bool authUser(char username[], char password[]){
    char path[300];
    sprintf(path, "./notes/%s/user.dat", username);

    struct stat st = {0};
    struct User user;

    if (stat(path, &st) == -1){ // user doesn't exist
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

/*
 * Update password of a user
 *
 * @param username  Username of the user
 * @param password  Passwoed of the user
 * @return bool     True if the password is updated else false
 */
bool updateUserPassword(char username[], char newPassword[]){
    char path[300];
    sprintf(path, "./notes/%s/user.dat", username);

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
    outfile = fopen(path, "wb");
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

/*
 * Delete a user and their data
 *
 * @param username  Username of the user
 * @return bool     True if user is deleted else false
 */
bool deleteUser(char username[]){
    #ifdef _WIN32
    char command[100];
    sprintf(command, "rmdir \"./notes/%s\" /S /Q", username); // delete user's directory
    system(command);
    return true;
    #else 
    char command[100];
    sprintf(command, "rm -rf ./notes/%s", username);
    system(command);
    return true;
    #endif
}
