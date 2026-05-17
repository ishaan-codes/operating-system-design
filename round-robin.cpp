// Round Robin assigns a fixed time quantum to each process. Processes are executed in circular fashion. If a process doesn't complete within its time quantum, it's preempted and moved to the end of the queue.

#include<iostream>
using namespace std;
struct Process {
    int pid;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};
void calculateRoundRobin(Process proc[], int n, int quantum) {
    int time = 0;
    bool done;    
    // Initialize remaining time
    for(int i=0; i<n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
    }    
    do {
        done = true;        
        for(int i=0; i<n; i++) {
            if(proc[i].remaining_time > 0) {
                done = false;                
                if(proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].burst_time;
                    proc[i].remaining_time = 0;
                }
            }
        }
    } while(!done);    
    // Calculate turnaround time
    for(int i=0; i<n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}
void displayResults(Process proc[], int n) {
    float total_wt = 0, total_tat = 0;    
    cout << "\nProcess\tBurst\tWaiting\tTurnaround\n";
    for(int i=0; i<n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        cout << "P" << proc[i].pid << "\t" << proc[i].burst_time 
             << "\t" << proc[i].waiting_time << "\t" << proc[i].turnaround_time << endl;
    }    
    cout << "\nAverage Waiting Time: " << total_wt/n;
    cout << "\nAverage Turnaround Time: " << total_tat/n;
}
int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> quantum;    
    Process proc[n];    
    for(int i=0; i<n; i++) {
        proc[i].pid = i+1;
        cout << "Enter burst time for P" << i+1 << ": ";
        cin >> proc[i].burst_time;
    }    
    calculateRoundRobin(proc, n, quantum);
    displayResults(proc, n);    
    return 0;
}