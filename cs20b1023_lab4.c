/*
Name : M Praveen
Roll No : cs20b1023

Q1 : Implementing Round Robin Scheduling.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000
int context_switching_overhead, i;

struct Process
{
    int id, arrival_time, burst_time, completion_time, turn_around_time, waiting_time, temp_burst_time;
};

struct Process *process;
int start = -1, end = -2, ready_queue[SIZE], time_quantum, n;

// We are using the push function to perform push operation for the ready queue.
void push(int index)
{
    if (start == -1)
    {
        start = 0;
        end = start;
        ready_queue[end] = index;
    }
    else
    {
        end++;
        ready_queue[end] = index;
    }
}

//we are using to remove the completed process.
int pop()
{
    if (start == -1)
    {
        return -1;
    }
    else if (start == end)
    {
        int index = start;
        start = -1;
        end = start;
        return ready_queue[index];
    }
    else
    {
        int index = start;
        start++;
        return ready_queue[index];
    }
}


//function to sort the arrival time.
void sort_arrival_time()
{
    struct Process temp;
    for (i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (process[i].arrival_time > process[j].arrival_time)
            {
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
}

//function to sort pid's
void sort_PID()
{
    struct Process temp;
    for (i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (process[i].id > process[j].id)
            {
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
}

// function to perform Round Robin scheduling.
void schedule_processes()
{
    sort_arrival_time();    //sorting arrival time.
    int count = 0;
    
    //declaring a ready queue.
    int queued_process[n];
    
    //initialising the ready queue with '0'.
    for (i = 0; i < n; i++)
    {
        queued_process[i] = 0;
    }
    
    //loop until all the processes are completed.
    for (int time = 0; count != n; time += time_quantum)
    {
        int fcfs = n;
        
        //if the ready queue is empty, we will take the process with less arrival time.
        if (start == -1)
        {
            int arrival_time = time;
            for (i = 0; i < n; i++)
            {
                if ((process[i].arrival_time <= arrival_time) && (process[i].temp_burst_time > 0))
                {
                    arrival_time = process[i].arrival_time;
                    fcfs = i;
                }
            }
            
            //if fcfs is equal to number of processes then the loop ends.
            if (fcfs == n)
            {
                time += 1;
                time -= time_quantum;
                continue;
            }
        }
        else
        {   //we use the start element as the processes.
            fcfs = pop();
            queued_process[fcfs] = 0;
        }
    
        //if burst time is less than the quantum time.
        if (process[fcfs].temp_burst_time < time_quantum)
        {
            int time_to_finish;

            time_to_finish = process[fcfs].temp_burst_time;
            process[fcfs].temp_burst_time = 0;
            time += time_to_finish;
            count++;

            process[fcfs].completion_time = time;
            process[fcfs].turn_around_time = process[fcfs].completion_time - process[fcfs].arrival_time;
            process[fcfs].waiting_time = process[fcfs].turn_around_time - process[fcfs].burst_time;
            time -= time_quantum;
        }
        else
        {
            process[fcfs].temp_burst_time -= time_quantum;
            
            if (process[fcfs].temp_burst_time == 0)
            {
                count++;
                process[fcfs].completion_time = time + time_quantum;
                process[fcfs].turn_around_time = process[fcfs].completion_time - process[fcfs].arrival_time;
                process[fcfs].waiting_time = process[fcfs].turn_around_time - process[fcfs].burst_time;
            }
        }

        context_switching_overhead++;   //here we are counting the no.of context switching.

        for (i = 0; i < n; i++)
        {
            if ((process[i].arrival_time <= (time + time_quantum)) && (process[i].temp_burst_time > 0) && (i != fcfs) && (!queued_process[i]))
            {
                push(i);
                queued_process[i] = 1;      //adding the process to the ready queue.
            }
        }
        
        //add the process to the end of the ready queue if the burst time is not equal to 0.
        if (process[fcfs].temp_burst_time != 0)
        {
            push(fcfs);
            queued_process[fcfs] = 1;
        }
    }

    context_switching_overhead--;   //decrementing the context switching, because it is less than the no.of processes.
    
    sort_PID();
}


// function to print table and calculate average waiting time and arrival time.
void printTable()
{
    float sum_at, sum_wt, avg_at = 0, avg_wt = 0;
    printf("PID\tA.Time\tB.Time\tC.Time\tTA.Time\tW.Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", process[i].id, process[i].arrival_time, process[i].burst_time, process[i].completion_time, process[i].turn_around_time, process[i].waiting_time);
    }

    for(i = 0; i < n; i++)
    {
        sum_at += process[i].arrival_time;
        sum_wt += process[i].waiting_time;
    }
    
    //calculating the average.
    avg_at = sum_at / n;
    avg_wt = sum_wt / n;

    printf("\nAverage waiting time is : %f", avg_at);
    printf("\nAverage waiting time is : %f", avg_wt);
    printf("\nContext Switching Overhead : %d\n", context_switching_overhead);
}

//main driver function.
int main()
{
    printf("Enter the number of processes: ");      //asking the user to enter the no.of processes
    scanf("%d", &n);
    
    process = malloc((n) * sizeof(*process));
    
    for (i = 0; i < n; i++)
    {
        printf("Enter the id of process: ");
        scanf("%d", &process[i].id);            //entering the process id's
    }

    printf("\n");

    for(i = 0; i < n; i++)
    {
        printf("Enter the arrival time of process  %d: ", process[i].id);   //asking the user to enter the arrival time.
        scanf("%d", &process[i].arrival_time);
    }
    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("Enter the burst time of process  %d: ", process[i].id);     //asking the user to enter the burst time.
        scanf("%d", &process[i].burst_time);
        process[i].temp_burst_time = process[i].burst_time;
    }
    printf("\n");

    printf("Enter the time quantum of processes: ");            //asking the user to enter time quantum.
    scanf("%d", &time_quantum);
    schedule_processes();
    printTable();
    return 0;
}