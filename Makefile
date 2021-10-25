CC = gcc

all: noter
test: test_noter test_user

noter: main.c packages/noter.c packages/user.c
	gcc -o noter main.c packages/noter.c packages/user.c

test_noter: tests/test_noter.c packages/noter.c
	gcc -o test_noter tests/test_noter.c packages/noter.c

test_user: tests/test_user.c packages/user.c
	gcc -o test_user tests/test_user.c packages/user.c