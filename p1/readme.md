# VE482 - Mumsh

Everything looks like a mess, since I just got out of bed.

A home-made shell named `mumsh` 

## To Build `mumsh`

Source files include: 

io.h, io.c, parse.h, parse.c, exec.h, exec.c, mumsh.h, mumsh.c

```shell
make all
```

## Change Your Default Shell as `mumsh`

```shell
# it is highly unrecommended to change your default shell to mumsh
mv mumsh /bin/
chsh -s /bin/mumsh
# perform this operation at your own risk :)
```

## Supported Features

1. commands and commands with arguments
2. I/O redirection, including `<` `>` `>>`  and pipes `|`
3. ctrl-c and ctrl-d
4. bash-style quotes
5. very basic error handling
6. wait for incomplete input
7. ask processes to run in background
8. check background processes through command `jobs`

## Potential Issues

1. mumsh may fail when dealing with quotes
2. mumsh may report incorrect error message when input has problems
3. ctrl-c may crash mumsh
4. potential memory leaks
5. mumsh may mess up the stdin and stdout file descriptors
6. mumsh may produce undefined behavior



Author:

Weili Shi

Oct 13, 2021