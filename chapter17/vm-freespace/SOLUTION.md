./malloc.py -n 10 -H 0 -p BEST -s 0 

seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList 
compute False

ptr[0] = Alloc(3) returned 0
List  Size 1 : addr:1003 sz 97

Free(ptr[0])
returned 0
List Size 2 : addr:1000 sz 3, 1003 sz 97

ptr[1] = Alloc(5) returned 0
List 2 : addr 1000 sz 3, 1008 sz 92

Free(ptr[1])
returned 0
List 3 :  addr 1000 sz 3, 1003 sz 5, 1008 sz 92

ptr[2] = Alloc(8) returned 0
List 3 : addr 1000 sz 3, 1003 sz 5, 1016 sz 84

Free(ptr[2])
returned 0
List 4 : addr 1000 sz 3, 1003 sz 5, 1008 sz 8, 1016 sz 76

ptr[3] = Alloc(8) returned 0
List 3 : addr 1000 sz 3, 1003 sz 5, 1016 sz 76

Free(ptr[3])
returned 0
List 4 : addr 1000 sz 3, 1003 sz 5, 1008 sz 8, 1016 sz 76

ptr[4] = Alloc(2) returned 0
List 4 : addr 1002 sz 1, 1003 sz 5, 1008 sz 8, 1016 sz 76

ptr[5] = Alloc(7) returned 0
List 4 : addr 1002 sz 1, 1003 sz 5, 1015 sz 1, 1016 sz 76


./malloc.py -n 10 -H 0 -p BEST -s 0 -p WORST

./malloc.py -n 10 -H 0 -p BEST -s 0 -p FIRST

Nr. 4
List ordering only affects First Fit policy because Best and Worst fit allways search the entire list.

Nr. 5

./malloc.py -n 10000 -H 0 -p BEST -s 0 

free list gets fragmented to a point where no more large allocs are possible.


Nr. 7

Worst fit, no coalesing, alignment to a large number, 

./malloc.py -n 10000 -H 0 -p WORST -A +10,-0,+5,-1,+2,-2 -a 16 -c