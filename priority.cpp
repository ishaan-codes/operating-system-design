// Priority scheduling assigns priorities to processes, and the process with highest priority executes first. It can be preemptive or non-preemptive. Lower priority numbers often indicate higher priority.

#include<iostream>
#include<algorithm>
using namespace std;
struct Process {
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};
bool compare(Process a, Process b) {
    return a.priority < b.priority;
}
void calculatePriority(Process proc[], int n) {
    sort(proc, proc+n, compare);    
    proc[0].waiting_time = 0;
    proc[0].turnaround_time = proc[0].burst_time;    
    for(int i=1; i<n; i++) {
        proc[i].waiting_time = proc[i-1].turnaround_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}
void displayResults(Process proc[], int n) {
    float total_wt = 0, total_tat = 0;    
    cout << "\nProcess\tBurst\tPriority\tWaiting\tTurnaround\n";
    for(int i=0; i<n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        cout << "P" << proc[i].pid << "\t" << proc[i].burst_time 
             << "\t" << proc[i].priority << "\t\t" << proc[i].waiting_time 
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
        cout << "Enter burst time for P" << i+1 << ": ";
        cin >> proc[i].burst_time;
        cout << "Enter priority for P" << i+1 << " (lower number = higher priority): ";
        cin >> proc[i].priority;
    }    
    calculatePriority(proc, n);
    displayResults(proc, n);    
    return 0;
}