# VE482 Lab 6 Ex 3

## Complex Sort

Sorts txt or csv files with a plugin architecture.

## build

```
make
```

Note:

- make sure that the `./plugins` folder exists. GNU make automatically places the compiled `.so` files in this directory.
- two test cases are included: `rand_int.txt` and `sample.csv`
- sort results are directed to `stdout` file descriptor

## file structure

- `src-main`: the main program
- `src-plugin-csv`: csv plugin
- `src-plugin-txt`: txt plugin
- `Makefile`: GNU make

## sample tests

```shell
# format: ./l6 $(input_file) $(sorting_order)
# input file must be .txt or .csv
# sorting order eithe inc, dec or rand
./l6 rand_int.txt inc
./l6 sample.csv inc
```

