 ## The first Linux tool you should check out is the very simple tool free. First, type man free and read its entire manual page; it’s short, don’t worry!

 The free command is used to display memory usage in Linux systems, including free and used physical and swap memory, buffers, and cache used by the kernel.

 ## 2. Now, run free, perhaps using some of the arguments that might be useful (e.g., -m, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?

 ##  4. Now, while running your memory-user program, also (in a different terminal window, but on the same machine) run the free tool. How do the memory usage totals change when your program is running? How about when you kill the memory-user program? Do the numbers match your expectations? Try this for different amounts of memory usage. What happens when you use really large amounts of memory?

 ```sh

$ free -m
               total        used        free      shared  buff/cache   available
Mem:            3878         688        2298           2         891        2951
Swap:           1024           0        1023

./memory-user -n 2000
$ free -m
               total        used        free      shared  buff/cache   available
Mem:            3878        2606         380           2         891        1033
Swap:           1024           0        1023

./memory-user -n 3000
$ free -m
               total        used        free      shared  buff/cache   available
Mem:            3878        3361         344           0         173         317
Swap:           1024         226         797

./memory-user -n 4000
$ free -m
               total        used        free      shared  buff/cache   available
Mem:            3878        2883         103           3         892         756
Swap:           1024           0        1023

./memory-user -n 8000
Killed
 ```


##  7. Now run pmap on some of these processes, using various flags (like -X) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?

Address: The start address of the memory region.

Kbytes: The size of the memory region in kilobytes.

RSS (Resident Set Size): The portion of memory held in RAM.

Dirty: Memory that has been modified and needs to be written to disk (if mapped from a file).

Mode: The memory access permissions for that region, and execution rights (e.g., r---- is read-only, r-x-- read and execute).

Mapping: The file or memory region associated with the address space (e.g., node, [anon] for anonymous memory).

<hr>

compared to the simple code/stack/heap model modern processes have several additional regions for various purposes:

Shared libraries, dynamic libraries, and memory-mapped files.

Anonymous memory allocations for the heap and stacks.

Multiple thread stacks, each with its own memory.

Guard pages, shared memory for inter-process communication.

Memory dedicated to handling complex virtual memory structures (e.g., file-backed, anonymous mappings).

```sh
pocketlab@24f98a1f93c8:~/ostep-homework$ pmap 224 -x
224:   /home/pocketlab/.vscode-server/cli/servers/Stable-384ff7382de624fb94dbaf6da11977bba1ecd427/server/node --dns-result-order=ipv4first /home/pocketlab/.vscode-server/cli/servers/Stable-384ff7382de624fb94dbaf6da11977bba1ecd427/server/out/bootstrap-fork --type=extensionHost --transformURIs --useHostProxy=false
Address           Kbytes     RSS   Dirty Mode  Mapping
0000000000400000    7644       0       0 r---- node
0000000000b77000       8       8       0 r-x-- node
0000000000b7a000   27304    9312       0 r-x-- node
0000000002800000       4       0       0 r-x-- node
0000000002801000   46840    1896       0 r---- node
00000000055bf000      16       8       8 r---- node
00000000055c3000     124      48      48 rw--- node
00000000055e2000     180     112     108 rw---   [ anon ]
00007f5d2934c000      92       4       0 r-x-- libgcc_s.so.1
00007f5d29363000      16       0       0 r---- libgcc_s.so.1
00007f5d29367000       4       0       0 r---- libgcc_s.so.1
00007f5d29368000       4       0       0 rw--- libgcc_s.so.1
00007f5d29369000      56       0       0 r---- libm.so.6
00007f5d29377000     496      12       0 r-x-- libm.so.6
00007f5d293f3000     364       0       0 r---- libm.so.6
00007f5d2944e000       4       0       0 r---- libm.so.6
00007f5d2944f000       4       0       0 rw--- libm.so.6
00007f5d29450000     616       0       0 r---- libstdc++.so.6.0.30
00007f5d294ea000    1092      52       0 r-x-- libstdc++.so.6.0.30
```

## 8. Finally, let’s run pmap on your memory-user program, with different amounts of used memory. What do you see here? Does the output from pmap match your expectations?

```sh
pocketlab@24f98a1f93c8:~/ostep-homework/chapter13$ pmap 2122 -x
2122:   ./memory-user -n 2000
Address           Kbytes     RSS   Dirty Mode  Mapping
0000558eefc70000       4       4       0 r---- memory-user
0000558eefc71000       4       4       0 r-x-- memory-user
0000558eefc72000       4       4       0 r---- memory-user
0000558eefc73000       4       4       4 r---- memory-user
0000558eefc74000       4       4       4 rw--- memory-user
0000558ef03d8000     132       4       4 rw---   [ anon ]
00007f140c43e000 1953140 1953136 1953136 rw---   [ anon ]
00007f148379b000     160     160       0 r---- libc.so.6
00007f14837c3000    1620     948       0 r-x-- libc.so.6
00007f1483958000     352     152       0 r---- libc.so.6
00007f14839b0000       4       0       0 ----- libc.so.6
00007f14839b1000      16      16      16 r---- libc.so.6
00007f14839b5000       8       8       8 rw--- libc.so.6
00007f14839b7000      52      20      20 rw---   [ anon ]
00007f14839c9000       8       4       4 rw---   [ anon ]
00007f14839cb000       8       8       0 r---- ld-linux-x86-64.so.2
00007f14839cd000     168     168       0 r-x-- ld-linux-x86-64.so.2
00007f14839f7000      44      32       0 r---- ld-linux-x86-64.so.2
00007f1483a03000       8       8       8 r---- ld-linux-x86-64.so.2
00007f1483a05000       8       8       8 rw--- ld-linux-x86-64.so.2
00007fffba44f000     132      12      12 rw---   [ stack ]
00007fffba584000      16       0       0 r----   [ anon ]
00007fffba588000       8       4       0 r-x--   [ anon ]
---------------- ------- ------- ------- 
total kB         1955904 1954708 1953224

pocketlab@24f98a1f93c8:~/ostep-homework/chapter13$ pmap 2879 -x
2879:   ./memory-user -n 3000
Address           Kbytes     RSS   Dirty Mode  Mapping
0000561d8fae5000       4       4       0 r---- memory-user
0000561d8fae6000       4       4       0 r-x-- memory-user
0000561d8fae7000       4       4       0 r---- memory-user
0000561d8fae8000       4       4       4 r---- memory-user
0000561d8fae9000       4       4       4 rw--- memory-user
0000561d8fc50000     132       4       4 rw---   [ anon ]
00007f2311ede000 2929700 2929696 2929696 rw---   [ anon ]
00007f23c4be7000     160     160       0 r---- libc.so.6
00007f23c4c0f000    1620    1064       0 r-x-- libc.so.6
00007f23c4da4000     352     168       0 r---- libc.so.6
00007f23c4dfc000       4       0       0 ----- libc.so.6
00007f23c4dfd000      16      16      16 r---- libc.so.6
00007f23c4e01000       8       8       8 rw--- libc.so.6
00007f23c4e03000      52      20      20 rw---   [ anon ]
00007f23c4e15000       8       4       4 rw---   [ anon ]
00007f23c4e17000       8       8       0 r---- ld-linux-x86-64.so.2
00007f23c4e19000     168     168       0 r-x-- ld-linux-x86-64.so.2
00007f23c4e43000      44      40       0 r---- ld-linux-x86-64.so.2
00007f23c4e4f000       8       8       8 r---- ld-linux-x86-64.so.2
00007f23c4e51000       8       8       8 rw--- ld-linux-x86-64.so.2
00007ffd2b73c000     132      12      12 rw---   [ stack ]
00007ffd2b775000      16       0       0 r----   [ anon ]
00007ffd2b779000       8       4       0 r-x--   [ anon ]
---------------- ------- ------- ------- 
total kB         2932464 2931408 2929784

pocketlab@24f98a1f93c8:~/ostep-homework/chapter13$ pmap 3091 -x
3091:   ./memory-user -n 4000
Address           Kbytes     RSS   Dirty Mode  Mapping
0000561d76368000       4       0       0 r---- memory-user
0000561d76369000       4       4       0 r-x-- memory-user
0000561d7636a000       4       4       0 r---- memory-user
0000561d7636b000       4       4       4 r---- memory-user
0000561d7636c000       4       0       0 rw--- memory-user
0000561d77ca8000     132       4       4 rw---   [ anon ]
00007f42eeaf3000 3906264 3252720 3252720 rw---   [ anon ]
00007f43dd1a9000     160     160       0 r---- libc.so.6
00007f43dd1d1000    1620    1060       0 r-x-- libc.so.6
00007f43dd366000     352     160       0 r---- libc.so.6
00007f43dd3be000       4       0       0 ----- libc.so.6
00007f43dd3bf000      16      12      12 r---- libc.so.6
00007f43dd3c3000       8       8       8 rw--- libc.so.6
00007f43dd3c5000      52       4       4 rw---   [ anon ]
00007f43dd3d7000       8       0       0 rw---   [ anon ]
00007f43dd3d9000       8       8       0 r---- ld-linux-x86-64.so.2
00007f43dd3db000     168     168       0 r-x-- ld-linux-x86-64.so.2
00007f43dd405000      44      40       0 r---- ld-linux-x86-64.so.2
00007f43dd411000       8       0       0 r---- ld-linux-x86-64.so.2
00007f43dd413000       8       0       0 rw--- ld-linux-x86-64.so.2
00007ffd620a2000     132      12      12 rw---   [ stack ]
00007ffd621d0000      16       0       0 r----   [ anon ]
00007ffd621d4000       8       4       0 r-x--   [ anon ]
---------------- ------- ------- ------- 
total kB         3909028 3254372 3252764
```

