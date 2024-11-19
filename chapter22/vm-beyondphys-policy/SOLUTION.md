./paging-policy.py -s 0 -n 10

-n 10
ARG addresses -1
ARG addressfile 
ARG numaddrs 10
ARG policy FIFO
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Assuming a replacement policy of FIFO, and a cache of size 3 pages,
figure out whether each of the following page references hit or miss
in the page cache.

Access: 8  Hit/Miss? m  State of Memory? 8
Access: 7  Hit/Miss? m  State of Memory? 7 8
Access: 4  Hit/Miss? m  State of Memory? 4 7 8
Access: 2  Hit/Miss? m  State of Memory? 2 4 7
Access: 5  Hit/Miss? m  State of Memory? 5 2 4
Access: 4  Hit/Miss? h  State of Memory? 5 2 4
Access: 7  Hit/Miss? m State of Memory? 7 5 2
Access: 3  Hit/Miss? m State of Memory? 3 7 5
Access: 4  Hit/Miss? m State of Memory? 4 3 7
Access: 5  Hit/Miss? m State of Memory? 5 4 3

./paging-policy.py -s 0 -n 10 -p LRU

Access: 8  Hit/Miss? m  State of Memory? 8
Access: 7  Hit/Miss? m  State of Memory? 7 8
Access: 4  Hit/Miss? m  State of Memory? 4 7 8
Access: 2  Hit/Miss? m  State of Memory? 2 4 7
Access: 5  Hit/Miss? m  State of Memory? 5 2 4
Access: 4  Hit/Miss? h  State of Memory? 4 5 2
Access: 7  Hit/Miss? m State of Memory? 7 4 5
Access: 3  Hit/Miss? m State of Memory? 3 7 4
Access: 4  Hit/Miss? h State of Memory? 4 3 7
Access: 5  Hit/Miss? m State of Memory? 5 4 3

./paging-policy.py -s 0 -n 10 -p OPT

Access: 8  Hit/Miss? m  State of Memory? 8
Access: 7  Hit/Miss? m  State of Memory? 7 8
Access: 4  Hit/Miss? m  State of Memory? 4 7 8
Access: 2  Hit/Miss? m  State of Memory? 2 4 7
Access: 5  Hit/Miss? m  State of Memory? 5 4 7
Access: 4  Hit/Miss? h  State of Memory? 5 4 7
Access: 7  Hit/Miss? h State of Memory? 5 4 7
Access: 3  Hit/Miss? m State of Memory? 3 5 4
Access: 4  Hit/Miss? h State of Memory? 3 5 4
Access: 5  Hit/Miss? h State of Memory? 3 5 4


# Nr. 2

## worst case FIFO, cache size 5

Access list = [1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, ...]

## worst case LRU, cache size 5

Access list = [1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, ...]

## worst case MRU, cache size 5

Access list = [1, 2, 3, 4, 5, 6, 5, 6, 5, 6, 5, 6, ...]

## to reach OPT hitrate a cache of size 6 would be needed


# Nr. 3

## Hitrate of FIFO on random access with cache 5
49.76%
## Hitrate of LRU on random access with cache 5
49.76%
## Hitrate of MRU on random access with cache 5
50.56%
## Hitrate of RAND on random access with cache 5
49.70%
## Hitrate of OPT on random access with cache 5
72.64%

## Hitrate of FIFO on locality access with cache 5
78.04%
## Hitrate of LRU on locality access with cache 5
80.19%
## Hitrate of MRU on locality access with cache 5
59.35%
## Hitrate of RAND on locality access with cache 5
75.48%
## Hitrate of OPT on locality access with cache 5
87.99%
