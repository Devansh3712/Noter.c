/*
 * ====================================================================
 *
 *      Filename        noter.h
 *      Authors         Devansh Singh <nbtg14124@mail.jiit.ac.in>
 *                      Chirag Tyagi <nbtg14814@mail.jiit.ac.in>
 *      Description     Header file for functions of `user.c` library
 *
 * ====================================================================
 */

#include <stdio.h>
#include <stdbool.h>

bool createUser(char username[], char password[]);
bool authUser(char username[], char password[]);
bool updateUserPassword(char username[], char newPassword[]);
bool deleteUser(char username[]);
