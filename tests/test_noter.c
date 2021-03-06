/*
 * ====================================================================
 *
 *      Filename        test_noter.c
 *      Authors         Devansh Singh <nbtg14124@mail.jiit.ac.in>
 *                      Chirag Tyagi <nbtg14814@mail.jiit.ac.in>
 *      Description     Unittest `packages/noter.h` header file
 *
 * ====================================================================
 */

#include <stdio.h>
#include <time.h>
#include "../packages/noter.h"
#include "../packages/user.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/*
 * Test the functions declared in `noter.h` header file
 */
void test(){
    clock_t begin = clock();
    int fail = 0, result[4];
    createUser("test", "test@123"); // create a test user
    result[0] = createNote("test", "testNote", "testContent");
    result[1] = readNote("test", "testNote");
    printf("\e[1;1H\e[2J"); // clear the terminal
    result[2] = updateNote("test", "testNote", "newTestContent");
    result[3] = deleteNote("test", "testNote");
    deleteUser("test");
    for(int test = 0; test < 4; test++){
        if(result[test]){
            printf(".");
            #ifdef _WIN32
            Sleep(100); // sleep for 1 second
            #else
            sleep(1);
            #endif
        }else{
            printf("E");
            fail++;
        }
    }
    printf("\n----------------------------------------------------------------------\n");
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // execution time for the test
    printf("Ran %d tests in %.2lfs\n\n", 4, time_spent);
    if(fail == 0){
        printf("OK\n");
    }
    else{
        printf("FAILED (errors=%d)\n", fail);
    }
}

int main(){
    test();
    return 0;
}
