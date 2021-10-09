# 1. Create a new user
user add -m willykid
# 2. List all currently running processes
ps -A
# 3. Display the characteristics of the CPU and the available memory
lscpu # or 
cat /proc/cpuinfo

lsmem # or
cat /proc/meminfo
# 4. Redirect some random output into two different files
head /dev/urandom | tee file1 > file2
# 5. Concatenate the two previous files
cat file1 file2 > file3
# 6. Read the content of file3 as hexadecimal values
hexdump file3
# 7. Use a single command to find all the files in /usr/src with the word semaphore in their name and containing the word ddekit_sem_down
grep -Rl "ddekit_sem_down" | grep "semaphore"
