Processes (procs)

r: The number of processes currently running and waiting for CPU time. In this case, 1 process is runnable.

b: The number of processes in uninterruptible sleep. These processes are usually waiting for I/O operations to complete. Here, there are 0 processes in this state.

Memory

swpd (kb): The amount of swap space currently being used, in kilobytes. Here, 81224 KB (approximately 79.3 MB) of swap space is in use. This indicates some memory pressure, as the system is using swap instead of just physical RAM.

free (kb): The amount of free physical memory, in kilobytes. 3056544 KB (approximately 2.9 GB) of RAM is free. This suggests there is still a decent amount of available memory.

buff (kb): The amount of memory used as buffers. Buffers are used for temporary storage of data being read from or written to disk. 1320 KB (approximately 1.3 MB) is being used for buffers.

cache (kb): The amount of memory used as cache. Cache holds recently accessed data, speeding up future access. 201924 KB (approximately 197.2 MB) is being used for cache.

Swap

si (kb/s): The amount of data swapped in from disk per second (in kilobytes). Here, it is 0 KB/s, indicating no swapping in at the moment.

so (kb/s): The amount of data swapped out to disk per second (in kilobytes). Again, 0 KB/s, meaning no swapping out is occurring right now.

I/O

bi (blocks/s): The number of blocks read from block devices (e.g., disks) per second. It's 0 blocks/s, suggesting no read I/O activity.

bo (blocks/s): The number of blocks written to block devices per second. Also 0 blocks/s, indicating no write I/O activity.

System

in: The number of interrupts per second. There are 91 interrupts per second. This is a measure of how frequently the system is being interrupted by hardware or software events.

cs: The number of context switches per second. There are 507 context switches per second. This indicates how often the system is switching between different processes.

CPU

us: The percentage of CPU time spent running user processes (non-kernel code). It's 0%, meaning no user processes are currently consuming CPU time.

sy: The percentage of CPU time spent running kernel processes (system code). It's also 0%, indicating no kernel processes are actively using the CPU.

id: The percentage of CPU time spent idle. It's 99%, meaning the CPU is mostly idle.

wa: The percentage of CPU time spent waiting for I/O operations to complete. It's 0%, suggesting there is no CPU waiting due to I/O.

st: The percentage of CPU time stolen by a virtual machine (in virtualized environments). It's 0%, indicating no CPU stealing is occurring.




# swapon -s
Filename: The path to the swap device or file. In this case, it's /dev/sdb, which indicates a partition on a disk (likely a secondary drive).

Type: Specifies whether the swap space is a partition or a file. Here, it's "partition".

Size: The total allocated size of the swap space in kilobytes (KB). 1048576 KB translates to 1 GB (1048576 / 1024 = 1024 MB, 1024 MB / 1024 = 1 GB).

Used: The amount of swap space currently being used, also in KB. In the first output, it's 203008 KB (~203 MB), and in the second, it's 202496 KB (~202 MB). This slight difference reflects the dynamic nature of swap usage. Processes might have written data to swap in between the two commands and then released some space.

Priority: The priority assigned to the swap device. Lower priority numbers have higher priority. A negative priority like -2 means this swap space will be used before any swap space with a higher priority (e.g., 0 or positive values).