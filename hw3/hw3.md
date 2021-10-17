<script>
   $(document).ready(function() {
     $head = $('#header');
     $head.prepend('<img src=\"cat.jpg\" style=\"float: right;width: 150px;z-index: 289;\"/>')
   });
</script>
<div><img src="cat.jpg" width="180px" align="right"></div>

# VE482 Homework 3
# <span style="font-family:Myriad Pro; font-size:0.6em;"> Weili Shi | 519370910011 | Oct 20, 2021</span>

## Ex 1. General questions

1. **Why would a thread voluntarily release the CPU?**

   Kernels use clock interrupt to ask processes to release the CPU, as processes are greedy. However, threads are working together and programmers decide how threads should sometimes give up CPU to allow other threads to run.

2. **What is the biggest advantage/disadvantage of user space threads?**

   Advantage: easy to switch threads: no traps or context switches are needed.
   
   Disadvantage: if one thread gets blocked, all threads in the same process get blocked.

3. **If a multi-threaded process forks, a problem occurs if the child gets copies of all the parent’s threads. Suppose that one of the original threads was waiting for keyboard input. Now two threads are waiting for keyboard input, one in each process. Does this problem ever occur in single-threaded processes?**

   No, since a blocked single-threaded process cannot fork.

4. **Many UNIX system calls have no Win32 API equivalents. For each such call, what are the consequences when porting a program from a UNIX system to a Windows system?**

   The incompatible system calls might be replaced with a combination of Win32 API system calls or other codes, otherwise the program won't work properly.

   

## Ex 2. C programming

   
