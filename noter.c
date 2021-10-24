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
#include <time.h>
#include <sys/stat.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#define BODY 4096
#define TITLE 255
#define TIME 64
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
            mkdir(path, 0700); 
        #endif
    }
}

void createNote(char title[TITLE], char content[BODY]){
    checkDirectory();

    struct Note note;
    title[strlen(title) - 1] = '\0';

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char currentTime[TIME];
    assert(strftime(currentTime, sizeof(currentTime), "%c", tm));

    strcpy(note.title, title);
    strcpy(note.body, content);
    strcpy(note.timestamp, currentTime);

    strcat(title, ".dat");
    strcat(PATH, title);

    FILE *outfile;
    outfile = fopen(PATH, "wb");
    if(outfile == NULL){
	    printf("\n[-] Unable to open the file\n");
        return;
    }
    fwrite(&note, sizeof(struct Note), 1, outfile);
    if(fwrite == 0){
	    printf("\n[-] Unable to write to the file\n");
        return;
    }
    fclose(outfile);
    printf("\n[+] Note created successfully\n");

    return;
}

void readNote(char title[TITLE]){
    checkDirectory();
    title[strlen(title) - 1] = '\0';

    strcat(title, ".dat");
    strcat(PATH, title);

    FILE *infile;
    struct Note note;
    infile = fopen(PATH, "rb");
    if(infile == NULL){
        printf("\n[-] Unable to open the file\n");
        return;
    }
    fread(&note, sizeof(struct Note), 1, infile);
    if(fread == 0){
	    printf("\n[-] Unable to read from the file\n");
        return;
    }

    printf("\nCONTENT\n");
    printf("-------\n");
    printf("%s\n\n", note.body);
    printf("TIMESTAMP\n");
    printf("---------\n");
    printf("%s\n\n", note.timestamp);
    fclose(infile);

    return;
}

void updateNote(char title[TITLE], char newContent[BODY]){
    checkDirectory();

    char updatePath[255];
    title[strlen(title) - 1] = '\0';

    strcat(title, ".dat");
    strcat(PATH, title);
    strcpy(updatePath, PATH);

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char currentTime[TIME];
    assert(strftime(currentTime, sizeof(currentTime), "%c", tm));

    struct Note note;
    struct Note newNote;

    FILE *infile;
    infile = fopen(PATH, "rb");
    if(infile == NULL){
        printf("\n[-] Unable to open the file\n");
        return;
    }
    fread(&note, sizeof(struct Note), 1, infile);
    if(fread == 0){
	    printf("\n[-] Unable to read from the file\n");
        return;
    }
    strcpy(newNote.title, note.title);
    strcpy(newNote.body , newContent);
    strcpy(newNote.timestamp, currentTime);
    fclose(infile);

    FILE *outfile;
    outfile = fopen(updatePath, "wb");
    if(outfile == NULL){
	    printf("\n[-] Unable to open the file\n");
        return;
    }
    fwrite(&newNote, sizeof(struct Note), 1, outfile);
    if(fwrite == 0){
	    printf("\n[-] Unable to write to the file\n");
        return;
    }
    fclose(outfile);
    printf("\n[+] Note updated successfully\n");

    return;
}

void deleteNote(char title[TITLE]){
    checkDirectory();
    title[strlen(title) - 1] = '\0';

    strcat(title, ".dat");
    strcat(PATH, title);

    if(remove(PATH) == 0){
        printf("\n[+] Note deleted successfully\n");
        return;
    }else{
        printf("\n[-] nable to delete note\n");
        return;
    }
}
