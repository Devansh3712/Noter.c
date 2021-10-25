/*
 * =================================================
 *
 *       Filename   noter.c
 *       Authors    Devansh Singh <nbtg14124@mail.jiit.ac.in>
 *                  Chirag Tyagi <nbtg14814@mail.jiit.ac.in>
 *
 * =================================================
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#define BODY 4096
#define TITLE 255
#define TIME 64
#define USER 100
#define PATH "./notes/"

struct Note{
    char title[TITLE];
    char body[BODY];
    char timestamp[TIME];
};

void checkDirectory(){
    struct stat st = {0};

    if (stat(PATH, &st) == -1){
        #if defined(_WIN32)
        CreateDirectory(PATH, NULL);
        #else 
        mkdir(PATH, 0700); 
        #endif
    }
}

bool createNote(char username[USER], char title[TITLE], char content[BODY]){
    checkDirectory();
    struct Note note;
    char path[300];
    sprintf(path, "./notes/%s/%s.dat", username, title);

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char currentTime[TIME];
    assert(strftime(currentTime, sizeof(currentTime), "%c", tm));

    strcpy(note.title, title);
    strcpy(note.body, content);
    strcpy(note.timestamp, currentTime);

    FILE *outfile;
    outfile = fopen(path, "wb");
    if(outfile == NULL){
        return false;
    }
    fwrite(&note, sizeof(struct Note), 1, outfile);
    if(fwrite == 0){
        return false;
    }
    fclose(outfile);

    return true;
}

bool readNote(char username[USER], char title[TITLE]){
    checkDirectory();
    struct Note note;
    char path[300];
    sprintf(path, "./notes/%s/%s.dat", username, title);

    FILE *infile;
    infile = fopen(path, "rb");
    if(infile == NULL){
        return false;
    }
    fread(&note, sizeof(struct Note), 1, infile);
    if(fread == 0){
        return false;
    }

    printf("\nCONTENT\n");
    printf("-------\n");
    printf("%s\n\n", note.body);
    printf("TIMESTAMP\n");
    printf("---------\n");
    printf("%s\n\n", note.timestamp);
    fclose(infile);

    return true;
}

bool updateNote(char username[USER], char title[TITLE], char newContent[BODY]){
    checkDirectory();
    char path[300];
    struct Note note, newNote;
    sprintf(path, "./notes/%s/%s.dat", username, title);

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char currentTime[TIME];
    assert(strftime(currentTime, sizeof(currentTime), "%c", tm));

    FILE *infile;
    infile = fopen(path, "rb");
    if(infile == NULL){
        return false;
    }
    fread(&note, sizeof(struct Note), 1, infile);
    if(fread == 0){
        return false;
    }
    strcpy(newNote.title, note.title);
    strcpy(newNote.body , newContent);
    strcpy(newNote.timestamp, currentTime);
    fclose(infile);

    FILE *outfile;
    outfile = fopen(path, "wb");
    if(outfile == NULL){
        return false;
    }
    fwrite(&newNote, sizeof(struct Note), 1, outfile);
    if(fwrite == 0){
        return false;
    }
    fclose(outfile);

    return true;
}

bool deleteNote(char username[USER], char title[TITLE]){
    checkDirectory();
    char path[300];
    sprintf(path, "./notes/%s/%s.dat", username, title);

    if(remove(path) == 0){
        return true;
    }else{
        return false;
    }
}
