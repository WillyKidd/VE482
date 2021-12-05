# Thrashing using C

## Description

This is a short C program that leads to thrashing. This is done by mallocing in a while loop that never exits. To compile and run,

```shell
gcc thrashing.c -o thrashing
./thrashing
```

 In Linux, if we simply ask for memory, it will just reserve the memory without allocating them. The memory is allocated when we try to access it, therefore we do a "memset" after the "malloc".
