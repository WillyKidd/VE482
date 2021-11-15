# Semaphores

To compile and run

```shell
clang -lpthread -o ex4 cthread.c
./ex4
```

## Description

`cthread.c` creates two threads which increment a common global variable. When run it generates a random and inaccurate output. In order to solve this problem we used semaphores.

