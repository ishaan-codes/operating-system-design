// SJF selects the process with smallest burst time for execution next. It can be preemptive or non-preemptive. It provides minimum average waiting time but requires knowledge of burst times in advance.

#include<iostream>
#include<algorithm>
using namespace std;
struct Process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};
bool compare(Process a, Process b) {
    return a.burst_time < b.burst_time;
}
void calculateSJF(Process proc[], int n) {
    // Sort processes by burst time
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
    int n;
    cout << "Enter number of processes: ";
    cin >> n;    
    Process proc[n];    
    for(int i=0; i<n; i++) {
        proc[i].pid = i+1;
        cout << "Enter burst time for P" << i+1 << ": ";
        cin >> proc[i].burst_time;
    }    
    calculateSJF(proc, n);
    displayResults(proc, n);    
    return 0;
}