/*
 * ====================================================================
 *
 *      Filename        noter.c
 *      Authors         Devansh Singh <nbtg14124@mail.jiit.ac.in>
 *                      Chirag Tyagi <nbtg14814@mail.jiit.ac.in>
 *      Description     Library for CRUD (Create, Read, Update, Delete)
 *                      functions of notes of a user
 *
 * ====================================================================
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

/*
 * @struct Note
 * @brief This structure is for storing the notes of a user
 * @var Note::title
 * Member 'title' stores the title of the note
 * @var Note::body
 * Member 'body' stores the content of the note
 * @var Note::timestamp
 * Member 'timestamp' stores the timestamp of the creation of a note
 */
struct Note{
    char title[TITLE];
    char body[BODY];
    char timestamp[TIME];
};

/*
 * Check if the `notes` directory exists, if it doesn't
 * create the directory
 */
void checkDirectory(){
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
 * Create a note for a user
 *
 * @param username  User whose note is to be created.
 * @param title     Title of the note.
 * @param content   Content of the note.
 * @return bool     True if note is created else false.
 */
bool createNote(char username[], char title[], char content[]){
    checkDirectory();
    struct Note note;
    char path[300];
    sprintf(path, "./notes/%s/%s.dat", username, title); // path of note

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char currentTime[TIME];
    assert(strftime(currentTime, sizeof(currentTime), "%c", tm)); // current timestamp

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

/*
 * Read a note of a user
 *
 * @param username  User whose note is to be created.
 * @param title     Title of the note.
 * @return bool     True if note is read else false.
 */
bool readNote(char username[], char title[]){
    checkDirectory();
    struct Note note;
    char path[300];
    sprintf(path, "./notes/%s/%s.dat", username, title);

    FILE *infile;
    infile = fopen(path, "rb");
    if(infile == NULL){
        return false;
    }
    fread(&note, sizeof(struct Note), 1, infile); // read and store note details in struct
    if(fread == 0){
        return false;
    }

    printf("\nCONTENT\n");
    printf("-------\n");
    printf("%s\n\n", note.body); // print content of note
    printf("TIMESTAMP\n");
    printf("---------\n");
    printf("%s\n\n", note.timestamp); // print timestamp of note
    fclose(infile);

    return true;
}

/*
 * Update a note of a user
 *
 * @param username      User whose note is to be created.
 * @param title         Title of the note.
 * @param newContent    New content of the note.
 * @return bool         True if note is updated else false.
 */
bool updateNote(char username[], char title[], char newContent[]){
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

/*
 * Delete a note of a user
 *
 * @param username  User whose note is to be created.
 * @param title     Title of the note.
 * @return bool     True if note is deleted else false.
 */
bool deleteNote(char username[], char title[]){
    checkDirectory();
    char path[300];
    sprintf(path, "./notes/%s/%s.dat", username, title);

    if(remove(path) == 0){
        return true;
    }else{
        return false;
    }
}
