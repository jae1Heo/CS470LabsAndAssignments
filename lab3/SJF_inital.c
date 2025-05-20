#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[]) {
    int min = INT_MAX; 
    int min_idx;
    for(int i = 0; i < n; i++) {
        // if current process is still in the ready queue with the shortest remaining time,
        if(min > proc[i].burst_time && (!proc[i].is_completed)) {
            min = proc[i].burst_time; // save current min
            min_idx = i; // save current index
        }
    }

    return min_idx; // return min index
}

// Function to print the processes and their details
void printProcesses(Process proc[], int order[]) {
    int sum_wt = 0; // sum of waiting time for average
    int sum_tt = 0; // sum of turnaround time for average
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[order[i]].process_id, proc[order[i]].arrival_time, proc[order[i]].burst_time,
               proc[order[i]].waiting_time, proc[order[i]].turnaround_time);
        sum_wt += proc[order[i]].waiting_time;
        sum_tt += proc[order[i]].turnaround_time;
    }

    printf("\nAverage waiting time\tAverage turnaround time\n");
    printf("%.02f\t\t\t%.02f\n", (double)(sum_wt / n), (double)(sum_tt / n));
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    int order[n]; // array to save order 
    int idx; 
    for(int i = 0; i < n; i++) {
        idx = findNextProcess(proc); // store index of next process to run
        order[i] = idx; // save its index
        proc[idx].is_completed = 1; // mark it as complete
    }

    
    proc[order[0]].waiting_time = 0; // set the first starting process's waiting time to 0
    for(int i = 1; i < n; i++) { // calculate waiting time for each process
        proc[order[i]].waiting_time = proc[order[i-1]].waiting_time + proc[order[i - 1]].burst_time;
    }

    for(int i = 0; i < n; i++) { // calculate turnaround time for each process
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
    
    printProcesses(proc, order); // print calculated results
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);

    return 0;
}
