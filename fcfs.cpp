// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
struct Process{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
}proc[100];
/*void completionTime(Process proc[],int n){
    proc[0].completion_time=proc[0].burst_time;
    for(int i=1;i<n;i++){
        proc[i].completion_time=proc[i-1].completion_time+proc[i].burst_time;
    }
}*/
/*void turnaroundTime(Process proc[],int n){
    for(int i=0;i<n;i++){
        proc[i].turn_around_time=proc[i].completion_time-proc[i].arrival_time;
    }
}
void waitingTime(Process proc[],int n){
    proc[0].waiting_time=0;
    for(int i=1;i<n;i++){
        proc[i].waiting_time=proc[i].turn_around_time-proc[i].burst_time;
    }
}
void FCFS(Process proc[],int n){
    completionTime(proc,n);
    turnaroundTime(proc,n);
    waitingTime(proc, n);
}*/
void completionTime(Process proc[], int n) {
    proc[0].completion_time = proc[0].arrival_time + proc[0].burst_time;
    for (int i = 1; i < n; i++) {
        proc[i].completion_time = max(proc[i - 1].completion_time, proc[i].arrival_time) + proc[i].burst_time;
    }
}
void turnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turn_around_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

void waitingTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].waiting_time = proc[i].turn_around_time - proc[i].burst_time;
    }
}
float calculateAverageWaitingTime(Process proc[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += proc[i].waiting_time;
    }
    return sum / n;
}

float calculateAverageTurnaroundTime(Process proc[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += proc[i].turn_around_time;
    }
    return sum/n;
}
void FCFS(Process proc[],int n){
    completionTime(&proc[0], n);
    turnaroundTime(&proc[0], n);
    waitingTime(&proc[0], n);
    float avg_waiting_fcfs = calculateAverageWaitingTime(&proc[0], n);
    float avg_turnaround_fcfs = calculateAverageTurnaroundTime(&proc[0], n);
}
void printFCFS(Process proc[],int n){
    cout<<"FCFS Scheduling:"<<endl;
    cout<<"PID\tArrival time\tBurst Time\tCompletion Time\tTurn around time\tWaiting time"<<endl;
    for(int i=0;i<n;i++){
        cout<<proc[i].pid<<"\t\t"<<proc[i].arrival_time<<"\t\t"<<proc[i].burst_time<<"\t\t"<<proc[i].completion_time<<"\t\t"<<proc[i].turn_around_time<<"\t\t"<<proc[i].waiting_time<<endl;
    }
}

int main() {
   int n;
   float avg_waiting_fcfs;
   float avg_turnaround_fcfs;
   cout<<"Enter total number of processes: ";
   cin>>n;
   //Process proc[n]={{1,0,5},{2,1,3},{3,2,2},{4,3,4},{5,4,1}};
   for(int i=0;i<n;i++)
    {
        cout<<"\nEnter Process " <<i<< " Arrival Time: ";
        cin >> proc[i].arrival_time;
        proc[i].pid=i;
    }
    
    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter Process " <<i<< " Burst Time: ";
        cin >> proc[i].burst_time;
    }
    cout << "Average waiting time="<< avg_waiting_fcfs << endl;
    cout << "Average turnaround time="<< avg_turnaround_fcfs << endl;

//     // FCFS
//     completionTime(&proc[0], n);
//     turnaroundTime(&proc[0], n);
//     waitingTime(&proc[0], n);
//     float avg_waiting_fcfs = calculateAverageWaitingTime(&proc[0], n);
//     float avg_turnaround_fcfs = calculateAverageTurnaroundTime(&proc[0], n);
//     void completionTime(Process proc[], int n) {
//     proc[0].completion_time = proc[0].arrival_time + proc[0].burst_time;
//     for (int i = 1; i < n; i++) {
//         proc[i].completion_time = max(proc[i - 1].completion_time, proc[i].arrival_time) + proc[i].burst_time;
//     }
// }

// void turnaroundTime(Process proc[], int n) {
//     for (int i = 0; i < n; i++) {
//         proc[i].turn_around_time = proc[i].completion_time - proc[i].arrival_time;
//     }
// }

// void waitingTime(Process proc[], int n) {
//     for (int i = 0; i < n; i++) {
//         proc[i].waiting_time = proc[i].turn_around_time - proc[i].burst_time;
//     }
// }



   FCFS(proc,n);
   printFCFS(proc,n);
   
   
    return 0;
}