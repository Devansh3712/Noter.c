/*
 * =================================================
 *
 *       Filename   main.c
 *       Authors    Devansh Singh <nbtg14124@mail.jiit.ac.in>
 *                  Chirag Tyagi <nbtg14814@mail.jiit.ac.in>
 *
 * =================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "noter.h"
#include "user.h"

#define BODY 4096
#define TITLE 255

int main(){
    bool flag = true;
    printf("%s", ART);
    printf("%s", MENU);

    while(flag == true){
        int option;
        char title[TITLE], content[BODY];

        printf("\n> Enter option: ");
        scanf("%d", &option);
        getchar();

        switch(option){
            case 1:
                printf("\n> Enter title of note: ");
                fgets(title, sizeof(title), stdin);
                printf("> Enter content of note: ");
                fgets(content, sizeof(content), stdin);
                createNote(title, content);
                break;
            
            case 2:
                printf("\n> Enter title of note: ");
                fgets(title, sizeof(title), stdin);
                readNote(title);
                break;

            case 3:
                printf("\n> Enter title of note: ");
                fgets(title, sizeof(title), stdin);
                printf("> Enter new content of note: ");
                fgets(content, sizeof(content), stdin);
                updateNote(title, content);
                break;
            
            case 4:
                printf("\n> Enter title of note: ");
                fgets(title, sizeof(title), stdin);
                deleteNote(title);
                break;

            case 5:
                printf("\n[*] Terminating program\n");
                exit(0);
            
            default:
                printf("\n[-] Choose a correct option\n");
                break;
        }
    }

    return 0;
}
