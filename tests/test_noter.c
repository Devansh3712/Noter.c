#include <stdio.h>
#include <time.h>
#include "../packages/noter.h"
#include "../packages/user.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void test(){
    clock_t begin = clock();
    int fail = 0, result[4];
    createUser("test", "test@123");
    result[0] = createNote("test", "testNote", "testContent");
    result[1] = readNote("test", "testNote");
    printf("\e[1;1H\e[2J");
    result[2] = updateNote("test", "testNote", "newTestContent");
    result[3] = deleteNote("test", "testNote");
    deleteUser("test");
    for(int test = 0; test < 4; test++){
        if(result[test]){
            printf(".");
            #ifdef _WIN32
            Sleep(100);
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
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
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
