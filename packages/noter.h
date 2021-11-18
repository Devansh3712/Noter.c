/*
 * ====================================================================
 *
 *      Filename        noter.h
 *      Authors         Devansh Singh <nbtg14124@mail.jiit.ac.in>
 *                      Chirag Tyagi <nbtg14814@mail.jiit.ac.in>
 *      Description     Header file for functions of `noter.c` library
 *
 * ====================================================================
 */

#include <stdio.h>
#include <stdbool.h>

#define ART "\n888b    888          888                              \n"\
"8888b   888          888                              \n"\
"88888b  888          888                              \n"\
"888Y88b 888  .d88b.  888888 .d88b.  888d888   .d8888b \n"\
"888 Y88b888 d88\"\"88b 888   d8P  Y8b 888P\"    d88P\"    \n"\
"888  Y88888 888  888 888   88888888 888      888      \n"\
"888   Y8888 Y88..88P Y88b. Y8b.     888  d8b Y88b.    \n"\
"888    Y888  \"Y88P\"   \"Y888 \"Y8888  888  Y8P  \"Y8888P \n\n"

#define MENU_OPTIONS "OPTIONS\n"\
"-------\n\n"\
"1. Create a note\n"\
"2. Read a note\n"\
"3. Update a note\n"\
"4. Delete a note\n"\
"5. Change password\n"\
"6. Delete account\n"\
"7. Help\n"\
"8. Quit\n\n"

#define USER_OPTIONS "1. Login\n"\
"2. Register\n"\
"3. Exit\n\n"

bool createNote(char username[], char title[], char content[]);
bool readNote(char username[], char title[]);
bool updateNote(char username[], char title[], char newContent[]);
bool deleteNote(char username[], char title[]);
