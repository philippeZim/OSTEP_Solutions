 ## The first Linux tool you should check out is the very simple tool free. First, type man free and read its entire manual page; it’s short, don’t worry!

 The free command is used to display memory usage in Linux systems, including free and used physical and swap memory, buffers, and cache used by the kernel.

 ## Now, run free, perhaps using some of the arguments that might be useful (e.g., -m, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?

 ```sh
$ free -m
               total        used        free      shared  buff/cache   available
Mem:            7611        1501        3663           5        2446        5835
Swap:           2048           0        2048
 ```

##  Now, while running your memory-user program, also (in a different terminal window, but on the same machine) run the free tool. How do the memory usage totals change when your program is running? How about when you kill the memory-user program? Do the numbers match your expectations? Try this for different amounts of memory usage. What happens when you use really large amounts of memory?
