#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    // Your code
    // initialize remaining time for each process
    for(int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    int current_time = 0; // records currnet process's waiting time
    int jobFlag = 1; // flag to check if all jobs are done or not
    do {
        jobFlag = 1; // set it to true at the beginning of the loop

        for(int i = 0; i < n; i++) { // in this for-loop, checks if any process needs to run
            if(proc[i].remaining_time > 0) { // if current process still got remaining time, 
                jobFlag = 0; // set the flag to 0 so that the outer loop run again

                if(proc[i].burst_time <= quantum) { // if currently selected process's burst time is less than quantum, 
                    proc[i].remaining_time = 0; // set the remaining time to 0
                    current_time += proc[i].burst_time; // add the current process's burst time for the next running process
                }
                else {
                    proc[i].remaining_time -= quantum; // subtract quantum to remaining time of current process
                    current_time += quantum; // add the quantum for the next running process
                }
                proc[i].waiting_time = (current_time - proc[i].burst_time); // calculate current process's waiting time
            }
        }

    }while(!jobFlag);
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
   // Your code
   // turnaround time = burst time + waiting time
    for(int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}

void printProcesses(Process proc[], int n) {
    int sum_wt = 0;
    int sum_tt = 0;
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
        sum_wt += proc[i].waiting_time;
        sum_tt += proc[i].turnaround_time;
    }
    printf("Average waiting time\tAverage turnaround time\n");
    printf("%d\t\t\t%d\n", (sum_wt / n), (sum_tt / n));
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling
 

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
