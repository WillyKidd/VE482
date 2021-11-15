# Race Condition in Bash

## Description

The script reads from a txt file. If the txt file doesn't exist or is empty, we create one by

`echo 1 > race.txt`.

Then the script reads the last line from it, and append to the file 1 + the number of the last line.

If two scripts are running simultaneously, reading and writing from the same file, race condition is very likely to occur.

## Usage

```shell
chmod +x *.sh
./ex3_driver.sh
```

The runs one script in the foreground and another in the background simultaneously.

## Explanation

- `ex3.sh` is the original script, that may result in race condition.
  - resulted output file: duplicated numbers
- `ex3_flock.sh` resolves the race condition by `flock`
- `ex3_mkdir.sh` resolves the race condition by `mkdir`
  - `mkdir` is atomic
  - the script makes a directory on entering the critical region
  - removes a directory on leaving the critical region
  - the script may only enter the critical region given the folder does not exist
