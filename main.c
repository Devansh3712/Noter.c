/*
 * =================================================
 *
 *      Filename        main.c
 *      Authors         Devansh Singh <nbtg14124@mail.jiit.ac.innoter>
 *                      Chirag Tyagi <nbtg14814@mail.jiit.ac.innoter>
 *      Description     Main Noter.c program file
 *
 * =================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "packages/noter.h"
#include "packages/user.h"

#define BODY 4096
#define TITLE 255
#define LIMIT 100

int main(){
    char username[LIMIT], password[LIMIT];
    int option;
    bool flag = false, res;
    printf("%s", ART);
    printf("%s", USER_OPTIONS);
    printf("noter> Enter option: ");
    scanf("%d", &option);
    switch(option){
        case 1:
            printf("\nnoter> Enter username: ");
            scanf("%s", &username);
            printf("noter> Enter password: ");
            scanf("%s", &password);
            res = authUser(username, password);
            if(res == true){
                flag = true;
                printf("\n[+] User '%s' logged in\n\n", username);
            }else{
                flag = false;
                printf("\n[-] Unable to log in user '%s'\n\n", username);
            }
            break;

        case 2:
            printf("\nnoter> Enter username: ");
            scanf("%s", &username);
            printf("noter> Enter password: ");
            scanf("%s", &password);
            res = createUser(username, password);
            if(res == true){
                flag = true;
                printf("\n[+] User '%s' created\n\n", username);
            }else{
                flag = false;
                printf("\n[-] Unable to create user '%s'\n\n", username);
            }
            break;
        
        case 3:
            printf("\n[*] Terminating program\n\n");
            exit(0);

        default:
            printf("\n[-] Choose a correct option\n");
            break;
    }

    if(flag == true){
        printf("%s", MENU_OPTIONS);
        while(true){
            char title[TITLE], content[BODY], newPassword[LIMIT], opt;

            printf("\nnoter> Enter option: ");
            scanf("%d", &option);
            getchar();

            switch(option){
                case 1:
                    printf("\nnoter> Enter title of note: ");
                    fgets(title, sizeof(title), stdin);
                    printf("noter> Enter content of note: ");
                    fgets(content, sizeof(content), stdin);
                    title[strlen(title) - 1] = '\0';
                    res = createNote(username, title, content);
                    if(res == true){
                        printf("\n[+] Note created successfully\n");
                    }else{
                        printf("\n[-] Unable to create note\n");
                    }
                    break;
                
                case 2:
                    printf("\nnoter> Enter title of note: ");
                    fgets(title, sizeof(title), stdin);
                    title[strlen(title) - 1] = '\0';
                    res = readNote(username, title);
                    if(res == false){
                        printf("\n[-] Unable to read note\n");
                    }
                    break;

                case 3:
                    printf("\nnoter> Enter title of note: ");
                    fgets(title, sizeof(title), stdin);
                    printf("noter> Enter new content of note: ");
                    fgets(content, sizeof(content), stdin);
                    title[strlen(title) - 1] = '\0';
                    res = updateNote(username, title, content);
                    if(res == true){
                        printf("\n[+] Note updated successfully\n");
                    }else{
                        printf("\n[-] Unable to update note\n");
                    }
                    break;
                
                case 4:
                    printf("\nnoter> Enter title of note: ");
                    fgets(title, sizeof(title), stdin);
                    title[strlen(title) - 1] = '\0';
                    res = deleteNote(username, title);
                    if(res == true){
                        printf("\n[+] Note deleted successfully\n");
                    }else{
                        printf("\n[-] Unable to delete note\n");
                    }
                    break;

                case 5:
                    printf("\nnoter> Enter new password: ");
                    scanf("%s", &newPassword);
                    res = updateUserPassword(username, newPassword);
                    if(res == true){
                        printf("\n[+] Password updated successfully\n");
                    }else{
                        printf("\n[-] Unable to update password\n");
                    }
                    break;
                
                case 6:
                    printf("\n[*] All your data will be deleted, do you want to continue? (y/n): ");
                    scanf("%c", &opt);
                    if(opt == 'y' || opt == 'Y'){
                        res = deleteUser(username);
                        if(res == true){
                            printf("\n[+] User deleted succesfully, program terminating\n\n");
                            exit(0);
                        }else{
                            printf("\n[-] Unable to delete account\n");
                        }
                    }else if(opt == 'n' || opt == 'N'){
                        printf("\n[*] Account deletion aborted\n");
                    }else{
                        printf("\n[-] Choose a correct option\n");
                    }
                    break;
                
                case 7:
                    printf("\n%s", MENU_OPTIONS);
                    break;

                case 8:
                    printf("\n[*] Terminating program\n\n");
                    exit(0);
                
                default:
                    printf("\n[-] Choose a correct option\n");
                    break;
            }
        }
    }

    return 0;
}
