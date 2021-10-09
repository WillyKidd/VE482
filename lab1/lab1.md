# VE482 Lab 1 <span style="font-family:Myriad Pro; font-size:0.6em;">                     Weili Shi 519370910011</span>

## 1. Hardware overview

- In the computer:

  <center>
      <img style="height:200px" src="src\mother.jpg" alt="motherboard">
      <br> Figure 1. The motherboard <br>
      <img style="height:200px" src="src\power.jpg" alt="motherboard">
      <br> Figure 2. The PC power supply <br>
      <img style="height:200px" src="src\hard.jpg" alt="motherboard">
      <br> Figure 3. The PC hard disk drive <br>
      <img style="height:200px" src="src\pci.jpg" alt="motherboard">
      <br> Figure 4. The PCI card <br>
      <img style="height:200px" src="src\optical.jpg" alt="motherboard">
      <br> Figure 5. The optical disk drive <br>

- On the motherboard

  <center>
      <img style="height:200px" src="src\ram.jpg" alt="motherboard">
      <br> Figure 6. The RAM <br>
      <img style="height:200px" src="src\bridge.jpg" alt="motherboard">
      <br> Figure 7. The south bridge (North bridge integrated in cpu) <br>
      <img style="height:200px" src="src\satasoket.jpg" alt="motherboard">
      <br> Figure 8. The SATA socket <br>
      <img style="height:200px" src="src\battery.jpg" alt="motherboard">
      <br> Figure 9. The battery <br>
      <img style="height:200px" src="src\pcislot.jpg" alt="motherboard">
      <br> Figure 10. The PCI slot <br>
      <img style="height:200px" src="src\cpu.jpg" alt="motherboard">
      <br> Figure 11. The CPU <br>
      <img style="height:200px" src="src\bios.jpg" alt="motherboard">
      <br> Figure 12. The BIOS (a chip on the motherboard) <br>
  </center>

- Where is the CPU hidden, and why?

  - The CPU is hidden under a fan and a structure shown in Figure 10. In this way, the CPU can be cooled quickly and the connection for the CPU is good.

-  What are the north and south bridges?

  - The north bridge controls the communication of the CPU with other parts of the computer. South bridge is connected with CPU through the north bridge, which controls the IO functions.

- How are north and south bridges connected?

  - They are connected through an internal bus.

- What is a BIOS?

  - BIOS, "basic input/output system", is used to perform hardware initialization during the booting process and provide runtime service for operating systems and programs.

- Take out the CPU, rotate it and try to plug it back in a different position, is that working?

  - No. It can break the CPU if you use lots of strength.

- Explain what overclocking is?

  - Overclocking is increasing the clock rate so as to increase the operating speed of a given component.

-  What are pins on a PCI/PCI-e card and what are they used for?

  - The pins on the PCI card are on the bottom of the PCI card. They can be used to provide power for the PCI card, connect the PCI with the motherboard, connect to the ground and so on.

- Before PCI-e became a common standard many graphics cards were using Accelerated Graphics Port (AGP), explain why.

  - AGP is based on PCI. AGP provides a dedicated pathway between the slots and the processor rather than sharing the PCI bus. Higher clock speeds can be achieved using AGP.

## 2. Git

## 3. Command line interface

### TASKS

##### mkdir, touch, mv, cp, ls

```sh
# Create a file named test
touch test
# Move test to dir/test.txt, where dir is a new directory
mkdir dir
# Copy dir/test.txt to dir/test_copy.txt.
mv test dir/test.txt
# List all the files contained in dir.
ls -a dir
```

##### grep

```sh
# List all the files from /etc containing the pattern 127.0.0.1.
grep -rl "127.0.0.1" /etc
# Only print the lines containing your username and root in the file /etc/passwd (only one grep should be used)
grep -rE "($USER|root)" /etc/passwd
```

##### find

```sh
# List all the files from /etc that have been accessed less than 24 hours ago.
find /etc -atime 1
# List all the files from /etc whose name contains the pattern “netw”
find /etc -name "*netw*"
```

##### redirections

- `>`: Redirects the standard output to the file specified on the right of `>` (output overrides original contents of the file)
- `>>`: Redirects the standard output to the file specified on the right of `>>` (output is appended to the original contents of the file)
- `<<<`: Redirects the string on the right of `<<<` as the standard input of the command on the left of `<<<`.
- `>&1`: Make the file descriptor specified on the left as a copy of the standard output.
- `2>&1 >`: Redirects the standard output only.
- `tee`: Redirects to the file as well as printing to standard output.

##### xargs , |

- `xargs`: build and execute command lines from standard input.
- `|`: pipes standard output on the left as standard input to the right.

##### head, tail

- `head`: output the first few lines of the file
- `tail`: output the last few lines of the file
- To live display a file as new lines get appended, use `tail -f`

##### ps, top, free, vmstat

- `ps`: display a snapshot of the current processes
- `top`: display linux processes.
- `free`: display amount of used and free memory in the system.
- `vmstat`: report virtual memory statistics.

##### sh, bash, csh, zsh

- `sh`: the original shell.
- `bash`: the shell that we use a lot.
- `csh`: the shell written by C.
- `zsh`: compared to `bash`, `zsh` has more useful features.

##### $$$$

- `$0`: the first argument.
- `$1`: the second argument.
- `$?`: the exit code of the previous command.
- `$!`: the process ID of the most recently executed background (asynchronous) command.

##### PS3

`PS3` is an environment variable that defines the prompt inside the select loop.

```bash
#!/bin/bash
PS3='Enter a digit: '
select i in a b c d e
do
	case $i in
		a) echo "alpha";;
		b) echo "beta";;
		c) echo "charlie";;
		d) echo "delta";;
		e) echo "exit"; exit;;
	esac
done
```

##### iconv

`iconv` reads in text in one encoding and outputs the text in another encoding. When working on different platforms, we may work with texts with different encoding. `iconv` allow us to change encoding easily.

##### temp

- `${#temp} `: number of characters of the variable temp.
- `${temp%%word}`: displays $temp excluding the maximum part that matches with word.
- `${temp/pattern/string}`: displays $temp, where the parts of $temp matches with $pattern are replaced with $string.

##### Unix File System

- `/`: root directory
- `/bin` essential command binary files
- `/boot` static files of the boot loader
- `/etc` host-specific system configuration files 
- `/lib` essential shared system libraries and kernel modules
- `/media` mount point for removable media
- `/mnt` mount point for temporary file system (WSL: `/mnt/c`)
- `/usr/bin` user binary files for user applications
- `/usr/share` contains architecture-independent shareable text files
- `/usr/lib` user libraries
- `/usr/src` system-related source files
- `/proc` special system files related with process and kernel
- `/sys` an interface to the kernel that provides kernel-view information and configuration settings 
- `/srv` data for services provided by this system
- `/opt` add-on application software packages
- `/var` variable data
- `/sbin` essential system binaries
- `/dev` device files
- `/vmlinuz` linux kernel executables
- `/initrd.img` initrd provides the capability to load a RAM disk by the boot
  loader

##### GAME

```sh
#!/bin/bash
number=$((($RANDOM)%100))
guess=333
count=0
while [ $number -ne $guess ] ; do
        echo guess a number please:
        read guess
        count=$(($count+1))
        if [ $number -lt $guess ] ; then
                echo Smaller
        elif [ $number -gt $guess ] ; then
                echo Larger
        else
                echo "That is correct!"
                echo "You've guessed "$count" times!"
                break
        fi
done
```



