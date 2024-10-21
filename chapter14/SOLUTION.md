## 1. First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program?

$ ./null

Segmentation fault (core dumped)

## 2. Next, compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you?

```sh
Program received signal SIGSEGV, Segmentation fault.
main () at null.c:6
6           printf("%d\n", *a);
```

## 3. Finally, use the valgrind tool on this program. We’ll use memcheck that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool?

```sh
pocketlab@24f98a1f93c8:~/ostep-homework/chapter14$ valgrind --leak-check=yes ./null
==4782== Memcheck, a memory error detector
==4782== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==4782== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==4782== Command: ./null
==4782== 
==4782== Invalid read of size 4
==4782==    at 0x109044: main (null.c:6)
==4782==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==4782== 
==4782== 
==4782== Process terminating with default action of signal 11 (SIGSEGV)
==4782==  Access not within mapped region at address 0x0
==4782==    at 0x109044: main (null.c:6)
==4782==  If you believe this happened as a result of a stack
==4782==  overflow in your program's main thread (unlikely but
==4782==  possible), you can try to increase the size of the
==4782==  main thread stack using the --main-stacksize= flag.
==4782==  The main thread stack size used in this run was 8388608.
==4782== 
==4782== HEAP SUMMARY:
==4782==     in use at exit: 0 bytes in 0 blocks
==4782==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==4782== 
==4782== All heap blocks were freed -- no leaks are possible
==4782== 
==4782== For lists of detected and suppressed errors, rerun with: -s
==4782== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Segmentation fault (core dumped)
```

## 4. Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)?

gdb no-free
```sh
(gdb) run
Starting program: /home/pocketlab/ostep-homework/chapter14/no-free 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
0x7fffffffe030
[Inferior 1 (process 5587) exited normally]
```

valgrind --leak-check=yes ./no-free
```sh
pocketlab@24f98a1f93c8:~/ostep-homework/chapter14$ valgrind --leak-check=yes ./no-free
==5810== Memcheck, a memory error detector
==5810== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==5810== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==5810== Command: ./no-free
==5810== 
0x1ffeffffc0
==5810== 
==5810== HEAP SUMMARY:
==5810==     in use at exit: 20 bytes in 1 blocks
==5810==   total heap usage: 2 allocs, 1 frees, 1,044 bytes allocated
==5810== 
==5810== 20 bytes in 1 blocks are definitely lost in loss record 1 of 1
==5810==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==5810==    by 0x1090C1: main (no-free.c:5)
==5810== 
==5810== LEAK SUMMARY:
==5810==    definitely lost: 20 bytes in 1 blocks
==5810==    indirectly lost: 0 bytes in 0 blocks
==5810==      possibly lost: 0 bytes in 0 blocks
==5810==    still reachable: 0 bytes in 0 blocks
==5810==         suppressed: 0 bytes in 0 blocks
==5810== 
==5810== For lists of detected and suppressed errors, rerun with: -s
==5810== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## 5. Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?

undifined behaviour index out of bounds.

## 6. Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?

```sh
==7423== Memcheck, a memory error detector
==7423== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==7423== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==7423== Command: ./aufgabe6
==7423== 
==7423== Invalid read of size 4
==7423==    at 0x1090E0: printf (stdio2.h:112)
==7423==    by 0x1090E0: main (aufgabe6.c:10)
==7423==  Address 0x4a8c040 is 0 bytes inside a block of size 40 free'd
==7423==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7423==    by 0x1090DF: main (aufgabe6.c:8)
==7423==  Block was alloc'd at
==7423==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7423==    by 0x1090B1: main (aufgabe6.c:4)
==7423== 
0
1
2
3
4
5
6
7
8
9
==7423== 
==7423== HEAP SUMMARY:
==7423==     in use at exit: 0 bytes in 0 blocks
==7423==   total heap usage: 2 allocs, 2 frees, 1,064 bytes allocated
==7423== 
==7423== All heap blocks were freed -- no leaks are possible
==7423== 
==7423== For lists of detected and suppressed errors, rerun with: -s
==7423== ERROR SUMMARY: 10 errors from 1 contexts (suppressed: 0 from 0)
```



## 7. Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?
```sh
aufgabe7.c:8:5: error: 'free' called on pointer 'arr' with nonzero offset 20 [-Werror=free-nonheap-object]
    8 |     free(&arr[5]);
```