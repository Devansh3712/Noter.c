/*
 * =================================================
 *
 *       Filename   user.h
 *       Authors    Devansh Singh <nbtg14124@mail.jiit.ac.in>
 *                  Chirag Tyagi <nbtg14814@mail.jiit.ac.in>
 *
 * =================================================
 */

#include <stdio.h>
#include <stdbool.h>

#define LIMIT 100

bool createUser(char username[LIMIT], char password[LIMIT]);
bool authUser(char username[LIMIT], char password[LIMIT]);
bool updateUserPassword(char username[LIMIT], char newPassword[LIMIT]);
bool deleteUser(char username[LIMIT]);
