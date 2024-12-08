Nr.2

python3 x86.py -p flag.s -M flag,count -R ax,bx


 flag count      ax    bx          Thread 0                Thread 1         

    0     ?       ?     ?   
    0     ?       ?     ?   1000 mov  flag, %ax
    0     ?       ?     ?   1001 test $0, %ax
    0     ?       ?     ?   1002 jne  .acquire
    1     ?       ?     ?   1003 mov  $1, flag
    1     ?       ?     ?   1004 mov  count, %ax
    1     ?       ?     ?   1005 add  $1, %ax
    1     ?       ?     ?   1006 mov  %ax, count
    0     ?       ?     ?   1007 mov  $0, flag
    0     ?       ?     ?   1008 sub  $1, %bx
    0     ?       ?     ?   1009 test $0, %bx
    0     ?       ?     ?   1010 jgt .top
    0     ?       ?     ?   1011 halt
    0     ?       ?     ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
    0     ?       ?     ?                            1000 mov  flag, %ax
    0     ?       ?     ?                            1001 test $0, %ax
    0     ?       ?     ?                            1002 jne  .acquire
    1     ?       ?     ?                            1003 mov  $1, flag
    1     ?       ?     ?                            1004 mov  count, %ax
    1     ?       ?     ?                            1005 add  $1, %ax
    1     ?       ?     ?                            1006 mov  %ax, count
    0     ?       ?     ?                            1007 mov  $0, flag
    0     ?       ?     ?                            1008 sub  $1, %bx
    0     ?       ?     ?                            1009 test $0, %bx
    0     ?       ?     ?                            1010 jgt .top
    0     ?       ?     ?                            1011 halt


Nr. 3

python3 x86.py -p flag.s -M flag,count -R ax,bx -a bx=2,bx=2

flag will still be 0 at the end of the programm
count will be 4 in the end

Nr. 4

python3 x86.py -p flag.s -M flag,count -R ax,bx -a bx=100,bx=100 -i x -c

allways correct for k * 11 -> 11 is the number of instructions in the critical section

Nr. 6

python3 x86.py -p test-and-set.s -M mutex,count -R ax,bx -a bx=100,bx=100 -i 4 -c

inefficient use of CPU -> uses more instructions can be shown with -S again the best results for multiples of 11

Nr. 7

python3 x86.py -p test-and-set.s -M mutex,count -R ax,bx -a bx=2,bx=2 -i 4 -c -P 001111111111111

I tested all posibilities with my plotting program -> no race conditions no deadlocks


Nr. 9 / 10

python3 x86.py -p peterson.s -M flag,turn,count -R ax,bx -a bx=0,bx=1 -i 5 -c -P 0000011111

Beide Threads setzten flag auf 1, es kommt jedoch nur 1er in den kritischen Bereich da turn gesetzt ist.

Nr. 11

python3 x86.py -p ticket.s -M ticket,turn,count -R ax,bx,cx -i 5 -c -a bx=1000,bx=1000 -S

viel spin warten, best i = 5, corectness erfüllt

Nr. 12

a lot more spinning 3x treads -> 10x instructions

Nr. 13

python3 x86.py -p test-and-set.s -M count,mutex -R ax,bx -a bx=5,bx=5 -c -i 7 -S
python3 x86.py -p yield.s -M count,mutex -R ax,bx -a bx=5,bx=5 -c -i 7 -S


Nr. 14

Change mutex to 1 only if lock is free. That will avoid unnecessary writing.
Setzt den Mutex nur auf 1 wenn lock frei ist, daturch wird unötiges überschreiben vermeidet.