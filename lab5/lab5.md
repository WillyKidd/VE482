<script>
   $(document).ready(function() {
     $head = $('#header');
     $head.prepend('<img src=\"cat.jpg\" style=\"float: right;width: 150px;z-index: 289;\"/>')
   });
</script>
<div><img src="cat.jpg" width="180px" align="right"></div>

# VE482 Lab5
# <span style="font-size:0.6em;"> Weili Shi 519370910011  Oct 28, 2021</span>

## 1. Layer programming

**The program can be divided into three layers, what are they?**

- list data structure
- sorting logic
- user interface

**Split the program into files according to the defined layers.**

- list data structure: `list.h`, `list.c`
- sorting logic: `sort.c`, `sort.h`
- user interface: `ui.c`, `ui.h`
- main for command line user interface: `main_cmd.c`
- main for menu user interface: `main_menu.c`

See the folder `./ex1` for details :)

## 2. Libraries

- **What are the four stages performed when compiling a file?**
  - **preprocessing**: removes comments, expands macros, expands included files
  - **compiling**: generates assembly code
  - **assembly**: converts the assembly code into binary code or machine code (also known as object code)
  - **linking**: merges all object codes from multiple modules into a single one
- **Static and dynamic libraries**
  - **static libraries**: statically linked, because a copy of the libraries is physically part of the executable. At compile time, static libraries stay locked into a program.
  - **dynamic libraries**: dynamically linked, because it contains filenames that enable the loader to find the program's library references at runtime, the dynamic libraries exist as separate files outside of the executable.

### Static library

- **Create 2 static libraries, 1 for each of the 2 lowest layers in the previous program.**

  ```shell
  gcc -c list.c -o list.o
  ar -crs liblist.a list.o
  gcc -c sort.c -o sort.o
  ar -crs libsort.a sort.o
  ```

- **Compile the command line version using the static libraries**

  ```shell
  gcc -L. -o ui_menu main_menu.c ui.c -lsort -llist
  ./ui_menu
  ```

### Dynamic library

```shell
gcc list.c main_menu.c sort.c ui.c -c -fpic
gcc *.o -shared -o libmenu.so
gcc -L. -o ui_menu main_menu.c ui.c -lmenu
# using environment variable LD_LIBRARY_PATH
# to tell compiler where to find the shared library
export LD_LIBRARY_PATH=./
./ui_menu
```

- **What is the difference between a library and the API?**
  - An API (application programming interface) is the way that an application communicates with some software components, typically a library.
  - A library is a collection of functionality. A library may not be executable, but can be a part of other executable.
  - See `./ex2` for the implementation

