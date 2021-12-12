<script>
   $(document).ready(function() {
     $head = $('#header');
     $head.prepend('<img src=\"cat.jpg\" style=\"float: right;width: 150px;z-index: 289;\"/>')
   });
</script>
<div><img src="cat.jpg" width="180px" align="right"></div>

# VE482 Homework 8
# <span style="font-family:Myriad Pro; font-size:0.6em;"> Weili Shi | 519370910011 | Dec 12, 2021</span>

## Ex. 1 — Input/Output

**1. Is it possible to scan a document and send it through a wireless network at full speed? Explain why, why not.**

No. The scanner reads the document while the network outputs the document. In practice, the scanner input may be slow, and may involve writing to the buffer block by block, which makes transferring through network at full speed unlikely.

**2. How can an OS facilitate the installation of a new device without any need to recompile the OS or even to reboot it?**

We can use the plug-in architecture. In Linux, we can load a device driver as a kernel module. The module registers itself (the device, the operations for the device) through the API provided by the kernel.

**3. In the slides four I/O software layers are listed; in which layers are the following operations done: **

**a) Computing the track, sector, and head for a disk read**

Device drivers.

**b) Writing command to the device registers **

Device drivers.

**c) Checking is the user is allowed to use the device **

Device independent OS software.

**d) Converting binary integers to ASCII for printing**

User level I/O software.

**4. A DMA controller has four channels. The controller is able to request a 32bit word every 100 nsec. A respond takes equally long. How fats should the bus be in order to avoid being a bottleneck?**

32 bit / 4 / 50 ns = 2*10^7 bit / second

**5.  Briefly explain what a thin client is.**

A thin client is a lightweight computer that has been optimized for establishing a remote connection with a server-based computer environment. The server does most of the work, and the thin client usually has low performance.

**6. Describe how a hard disk is working and give a few details regarding its geometry.**

A hard disk consists of several round platters where the data is stored. The platters are paired with magnetic heads, which read and write the data to the platter surfaces. The hands can rotate past the device and operate very close to the magnetic surface.

**7. What are differences between RAID 0, 1, 5, 6, and 10?**

- RAID 0: data are split into blocks. They can be written across all drives so that the read and write is fast.
- RAID 1: mirroring. Consists of an exact copy (or mirror) of a set of data on two or more disks.
- RAID 5: consists of block-level striping with distributed parity. The write speed is slower for the parity to be calculated.
- RAID 6: extends RAID 5 by adding another parity block; thus, it uses block-level striping with two parity blocks distributed across all member disks.
- RAID 10: mirroring and striping.

## Ex. 2 — Multiprocessors

**1.  Suppose that the TSL instruction was not available for synchronizing a multiprocessor. Instead, another instruction, SWP was provided that atomically swapped the contents of a register with a word in memory. How could that be used to provide multiprocessor synchronisation?**

First, load 1 into the register. Then, use SWP to automatically swap the register and the word in the memory. Then, the memory word is set to 1 and therefore the lock is set. Then, we check whether the room is locked by inspecting the value in the register. If it is 0, the room is not locked previously and is now locked by us. If it is 1, the room is previously locked.

**2. Virtualization**

Virtualization is to use software to emulate the functionality of hardware.

Major challenges: reasonable distribution of resources, monitoring the performance, backup the data, and security.

## Ex. 3  — File systems

**1. Assuming the current working directory is /usr/share/doc/mutt/examples what is the absolute path of ../../../doc/../../lib/mutt? **

`/usr/lib/mutt`

**2. A Unix system has 1KB blocks and 4B disk addresses. What is the maximum file size if i-nodes contain 13 direct entries, and one single, double , and triple indirect entry each? **

13 + 256 + 256\*256 + 256\*256\*256 = 16843021 KB

around 16 GB

**3. The time required to read a certain number of bytes can be approximated by summing the seek, rotation delay, and transfer times. Given a disk with mean seek time of 8 msec, a rotation rate of 15,000 rpm and 262,144 bytes per track what are the data rates for block sizes of (i) 1 KB, (ii) 2 KB, and (iii) 4 KB?**

- Data transfer rate = amount of data / transfer time
- Rotation latency: 1/(15000/60)*(1/2) = 2ms
- Transfer time:
  - (i) 8 + 2 + (1024 / 262144) * 1000 = 12.45 ms
  - (ii) 8 + 2 + (2*1024 / 262144) * 1000 = 12.91 ms
  - (iii) 8 + 2 + (4*1024 / 262144) * 1000 = 13.81 ms

## Ex. 4 — Security

**1. If using only lowercase letters how many possible 8 letter words can be chosen? Explain why a password should always contain lower and uppercase letters, numbers and symbols.**

26^8 = 208827064576 possible words.

Using lower and uppercase letters, numbers and symbols can make the password harder to guess. It also makes the number of possible password much greater. If someone tries to crack the password using brute force, he would use much more time.

**2. Explain why memory dynamically allocated using malloc is sometimes random and some other times set to 0.**

There are two possible things, and only one will happen:

1. `malloc()` returns recycled memory that was previously allocated and freed from the process.

   In this case, the memory will contain data leftover from previous allocations, and the data won't be zero. This usually happens when making small allocations.

2. `malloc()` requests new pages from the OS.

   In this case, the OS gives you the memory (which is likely freed from another process). To improve security, and prevent you from reading the data from other processes, the OS will zero the allocated memory before giving to you.

**3. A computer system is made of several components each featuring a different level of security. How secure is this system?**

It is likely that the system is not secure. The system may be hacked through the weakest part, and the whole system is down.

**4. Can security be achieved? Explain your answer**

It is almost impossible. If we want to achieve complete security, we need to spend lots of resources to enhance the security, such as filtering the network traffic, keeping a checksum of all the files and so on. We may even isolate the computer, encrypt all the disks including the swap and block all ports for external devices. The price is huge, and there may still exist loopholes.

## Ex. 5 — Research

References: 

- https://www.geeksforgeeks.org/how-to-setup-firewall-in-linux/
- https://opensource.com/article/18/9/linux-iptables-firewalld
- https://linux.die.net/man/8/iptables
- https://linux.die.net/man/8/ebtables
- https://linux.die.net/man/8/arptables

Firewall is a network security system that filters and controls the traffic on a predetermined set of rules. The system sits between the device and the Internet.

`IPTables` is the default tool provided by Linux. It controls IPv4 and IPv6 filtering rules. Three chains (set of rules) are defined: INPUT, OUTPUT and FORWARD (coming from external and going to another). Three actions are provided: ACCEPT, DROP and REJECT (similar to REJECT but sends a message to the sender that the data transfer has failed). Using the command `iptables` under root privilege, we can modify the rules. There are currently three independent tables, the filter, nat and mangle.

`etables` -- ethernet bridge frame table administration. Etables is used to setup and maintain the table of rules inside the Linux kernel that inspect Ethernet frames. It is analogous to the **iptables** application, but less complicated, due to the fact that the Ethernet protocol is much simpler than the IP protocol. There are also chains in etables that are unordered lists of rules. A firewall rule specifies criteria for an Ethernet frame and a frame processing specification called a target. There are four rules: ACCEPT (let the frame through), DROP (stop the frame), CONTINUE (check next rule) and RETURN (stop traversing this chain, go to previous chain).

`arptables` is another tool that maintains the address resolution protocol packet filter rules in  Linux. Similar to the above tools, several different tables may be defined. Each table contains a number of built-in chains and may also contain user-defined chains. `arptables` also provides chains, similar to iptables and etables.

## Ex. 6 — Linux

A kernel panic is a safety measure taken by the OS's kernel when an internal fatal error is detected. It is likely that the kernel cannot safely recover or that continue running will lead to major data loss. For Unix and Unix-like system, we have kernel panic. For windows, the equivalent term is "Stop error".

I tried to generate the kernel panic through:

```shell
su
echo c > /proc/sysrq-trigger
```

However I forgot the root password for the virtual machine.

![](panic.png)

When the panic is generated, the system will get frozen, and the operating system will try to recover and clean everything (the file system (inodes) and so on) when we reboot.

## Ex 7. Survey

Completed!
