## 1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

```sh
./scheduler.py -p FIFO -l 200,200,200
./scheduler.py -p SJF -l 200,200,200
```

No difference between FIFO and SJF because all jobs have the same length
Average -- Response: 200.00  Turnaround 400.00  Wait 200.00

## 2. Now do the same but with jobs of different lengths: 100, 200, and 300.

```sh
./scheduler.py -p FIFO -l 300,200,100
./scheduler.py -p SJF -l 300,200,100
```

FIFO Average -- Response: 266.67  Turnaround 466.67  Wait 266.67
SJF Average -- Response: 133.33  Turnaround 333.33  Wait 133.33

## 3. Now do the same, but also with the RR scheduler and a time-slice of 1.

```sh
./scheduler.py -p RR -l 300,200,100 -q 1
```

Average -- Response: 1.00  Turnaround 466.67  Wait 266.67

## 4. For what types of workloads does SJF deliver the same turnaround times as FIFO?

all jobs have the same length or jobs are already sorted by increasing length

## 5. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?

If all jobs have the length of one quantum.

## 6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?

![Alt text](./graph1.png)



## 7. What happens to response time with RR as quantum lengths increase? <br>Can you write an equation that gives the worst-case response time, given N jobs?

$$R_{worst}=\sum_{i=1}^{N-1}\text{min}(t_{i},Q)$$