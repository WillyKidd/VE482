 # VE482 Lab 6 Ex 2

## Zathura txt-plugin

Install Zathura using your package manager.

To build the plugin:

```shell
meson build
cd build
ninja
ninja install

```

A file `libtxt.so` will be placed in `/usr/lib/zathura`

Now Zathura can display txt files. Test using

```shell
zathura $(your_txt_file_name)
```

## Potential issues

- Somehow Zathura cannot display change line character `\n`.

  - I replaced the `\n` with `\0` and instead moved to the next line through

    `cairo_move_to(cairo, 20, 30+i*15); ` 

    where `i` is the line number

- Potential memory leaks

- Unused variables

