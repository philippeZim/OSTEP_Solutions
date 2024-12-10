Each program takes the following flags: 
- `-l <number of items each producer produces>`
- `-m <size of the shared producer/consumer buffer>`
- `-p <number of producers>`
- `-c <number of consumers>`
- `-P <sleep string: how producer should sleep at various points>`
- `-C <sleep string: how consumer should sleep at various points>`
- `-v [verbose flag: trace what is happening and print it]`
- `-t [timing flag: time entire execution and print total time]`



2. Run with one producer and one consumer, and have the producer
produce a few values. Start with a buffer (size 1), and then increase
it. How does the behavior of the code change with larger buffers?
(or does it?) What would you predict num full to be with different
buffer sizes (e.g., -m 10) and different numbers of produced items
(e.g., -l 100), when you change the consumer sleep string from
default (no sleep) to -C 0,0,0,0,0,0,1?

./main-two-cvs-while -l 2 -m 1 -p 1 -c 1 -v
./main-two-cvs-while -l 2 -m 10 -p 1 -c 1 -v
-> num full doesnt change
./main-two-cvs-while -l 10 -m 10 -p 1 -c 1 -v
./main-two-cvs-while -l 10 -m 10 -p 1 -c 1 -C 0,0,0,0,0,0,1 -v

Nr.4
Let’s look at some timings. How long do you think the following execution, with one producer, three consumers, a single-entry
shared buffer, and each consumer pausing at point c3 for a second, will take? ./main-two-cvs-while -p 1 -c 3 -m 1 -C
0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0 -l 10 -v
-t

~ 12-13s

Nr.5
It doesn't change. It would have changed the time if we had multiple producers

Nr.6

Now change the location of the sleep to c6 (this models a consumer taking something off the queue and then doing something
with it), again using a single-entry buffer. What time do you predict in this case? ./main-two-cvs-while -p 1 -c 3 -m 1
-C 0,0,0,0,0,0,1:0,0,0,0,0,0,1:0,0,0,0,0,0,1 -l 10
-v -t

5s

Nr.7

Finally, change the buffer size to 3 again (-m 3). What time do you
predict now?

same as in Nr. 5

Nr.8

Now let’s look at main-one-cv-while.c. Can you configure
a sleep string, assuming a single producer, one consumer, and a
buffer of size 1, to cause a problem with this code?

./main-one-cv-while -p 1 -c 1 -m 1 -l 1

Nein das Problem trit nur auf, wenn wir mehrer Concumer haben und ein Consumer einen anderen Consumer weckt.

Nr.9

9. Now change the number of consumers to two. Can you construct
sleep strings for the producer and the consumers so as to cause a
problem in the code?

./main-one-cv-while -p 1 -c 2 -m 1 -l 1 -P 0,0,0,0,0,0,1

Nr. 10

Now examine main-two-cvs-if.c. Can you cause a problem to
happen in this code? Again consider the case where there is only
one consumer, and then the case where there is more than one.

./main-two-cvs-if -p 1 -c 1 -m 1 -l 1
./main-two-cvs-if -p 1 -c 2 -m 1 -l 1
./main-two-cvs-if -p 1 -c 2 -l 10 -m 1 -C 0,0,0,0,0,0,0:0,0,0,0,2,0,0

Nr. 11

Finally, examine main-two-cvs-while-extra-unlock.c. What
problem arises when you release the lock before doing a put or a
get? Can you reliably cause such a problem to happen, given the
sleep strings? What bad thing can happen?

./main-two-cvs-while-extra-unlock -l 2 -m 1 -p 10 -c 1 -P 0,0,0,5,0,0,0:0,0,0,2,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0 -C 1,0 -v

normaly race conditions in do_fill() can accour.