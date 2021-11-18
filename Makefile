CC = gcc
DEPS = packages/noter.c packages/user.c

all: noter
test: test_noter test_user

noter: main.c $(DEPS)
	$(CC) -o noter main.c $(DEPS)

test_noter: tests/test_noter.c $(DEPS)
	$(CC) -o test_noter tests/test_noter.c $(DEPS)

test_user: tests/test_user.c packages/user.c
	$(CC) -o test_user tests/test_user.c packages/user.c