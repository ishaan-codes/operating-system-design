// SRTF is the preemptive version of SJF where the process with smallest remaining burst time is executed. It requires tracking remaining time and can provide better response time than SJF.

#include<iostream>
#include<climits>
using namespace std;
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};
void calculateSRTF(Process proc[], int n) {
    int complete = 0, time = 0, min_remaining = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;    
    // Initialize remaining time
    for(int i=0; i<n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }    
    while(complete != n) {
        // Find process with minimum remaining time
        for(int j=0; j<n; j++) {
            if((proc[j].arrival_time <= time) && 
               (proc[j].remaining_time < min_remaining) && 
               (proc[j].remaining_time > 0)) {
                min_remaining = proc[j].remaining_time;
                shortest = j;
                check = true;
            }
        }        
        if(!check) {
            time++;
            continue;
        }        
        // Reduce remaining time
        proc[shortest].remaining_time--;
        min_remaining = proc[shortest].remaining_time;        
        if(min_remaining == 0) {
            min_remaining = INT_MAX;
        }        
        // If process completes execution
        if(proc[shortest].remaining_time == 0) {
            complete++;
            check = false;
            finish_time = time + 1;            
            proc[shortest].completion_time = finish_time;
            proc[shortest].turnaround_time = finish_time - proc[shortest].arrival_time;
            proc[shortest].waiting_time = proc[shortest].turnaround_time - proc[shortest].burst_time;
        }
        time++;
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
    calculateSRTF(proc, n);
    displayResults(proc, n);    
    return 0;
}