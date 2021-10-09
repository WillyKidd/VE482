<script>
   $(document).ready(function() {
     $head = $('#header');
     $head.prepend('<img src=\"cat.jpg\" style=\"float: right;width: 150px;z-index: 289;\"/>')
   });
</script>
<div><img src="cat.jpg" width="180px" align="right"></div>

# VE482 Homework 1 
# <span style="font-family:Myriad Pro; font-size:0.6em;"> Weili Shi 519370910011  Oct 3, 2021</span>
## Ex 1. Stack and heap

Stack and heap are two methods of memory allocation. Stack allocation allocates the memory automatically and deallocates the memory when the variables go out of scope. The access speed of stack is faster compared to heap. However, a stack has a smaller size compared to heap. When stack space runs out, stack overflow happens. A heap has a larger size and is usually used for dynamic memory allocation. Therefore, the allocation and deallocation are manual and we should prevent memory leaks.

## Ex 2. BIOS and Kernels

1. BIOS if the first to be launched when the computer is powered on. It performs a series of tests such as power on self test (POST) which tests the hardwares of the computer, and the master boot record (MBR) which searches for installed operating systems. If the tests are successful, the operation system is loaded. If the tests fail, an error message will appear.

2. Hybrid kernel combines features of monolithic and micro kernel. It tries to achieve the advantages of both monolithic and micro kernels.

   Exo kernel reduces hardware abstraction such that users can access the hardware more directly.

## Ex 3. Course Application

1. Instructions a), c), d) should only be allowed in kernel mode. 

   Reason: kernel mode allows access to all the hardware. Disabling all interrupts, setting the time-of-day clock and changing the memory map should not be allowed in user mode since the user cannot always be trusted for those kind of low-level operations (the user may break the operating system). However, reading the time-of-day clock is very safe since it only reads and does not write or execute,  therefore it can be allowed in user mode.

2. 20 ms, 25 ms, 30 ms, or 35 ms depending the scheduling.
   - When all programs are assigned to one cpu, it takes 35 ms.
   - When P0, P1 assigned to one cpu and P2 to the other, it takes 20 ms.
   - When P0, P2 assigned to one cpu and P1 to the other, it takes 25 ms.
   - When P1, P2 assigned to one cpu and P0 to the other, it takes 30 ms.

## Ex 4. RAM

- To support a 25 lines by 80 rows character monochrome text screen:
  - RAM needed: 25\*80/1024 = 1.953125 KB
  - Price: $9.765625
- To support a 1024*768 px 24-bit color bitmap:
  - RAM needed: 1024\*768\*24/8/1024 = 2304 KB
  - Price: $11,520
- Price now (2021): less than $10 / GB

## Ex 5. Command Lines on a Unix System

```shell
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

```

