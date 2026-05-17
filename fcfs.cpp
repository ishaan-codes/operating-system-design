// FCFS is the simplest CPU scheduling algorithm that executes processes in the order they arrive. It's non-preemptive and uses a FIFO queue. While simple to implement, it may suffer from convoy effect where short processes wait for long ones.

#include<iostream>
using namespace std;
struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
};
void calculateFCFS(Process proc[], int n) {
    int completion_time[n];    
    // Calculate completion time
    completion_time[0] = proc[0].arrival_time + proc[0].burst_time;
    for(int i=1; i<n; i++) {
        if(proc[i].arrival_time > completion_time[i-1])
            completion_time[i] = proc[i].arrival_time + proc[i].burst_time;
        else
            completion_time[i] = completion_time[i-1] + proc[i].burst_time;
    }    
    // Calculate turnaround and waiting time
    for(int i=0; i<n; i++) {
        proc[i].turnaround_time = completion_time[i] - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
}
void displayResults(Process proc[], int n) {
    float total_wt = 0, total_tat = 0;    
    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    for(int i=0; i<n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        cout << "P" << proc[i].pid << "\t" << proc[i].arrival_time 
             << "\t" << proc[i].burst_time << "\t" << proc[i].waiting_time 
             << "\t" << proc[i].turnaround_time << endl;
    }    
    cout << "\nAverage Waiting Time: " << total_wt/n;
    cout << "\nAverage Turnaround Time: " << total_tat/n;
}
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;    
    Process proc[n];    
    for(int i=0; i<n; i++) {
        proc[i].pid = i+1;
        cout << "Enter arrival time for P" << i+1 << ": ";
        cin >> proc[i].arrival_time;
        cout << "Enter burst time for P" << i+1 << ": ";
        cin >> proc[i].burst_time;
    }    
    calculateFCFS(proc, n);
    displayResults(proc, n);    
    return 0;
}