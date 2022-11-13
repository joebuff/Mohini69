#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

int main() {

    int n;
    int i;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
  
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
 
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    cout << setprecision(2) << fixed;

   cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"Enter "<<n<<" process: ";
            for(i=0;i<n;i++)
            {
            cin>>p[i].pid;
            }
        cout<<"Enter "<<n<<" arrival time: ";
    for(i=0;i<n;i++)
    {
    cin>>p[i].arrival_time;
    }
    cout<<"Enter " <<n<<" burst time: ";
    for(i=0;i<n;i++)
    {
   cin>>p[i].burst_time;
    }
     cout<<"Enter " <<n<<" priority: ";
    for(i=0;i<n;i++)
    {
   cin>>p[i].priority;
    }

    for(int i = 0; i < n; i++) {

        p[i].pid = i+1;
        cout<<endl;
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
        
            
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
 
            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else {
            current_time++;
        }
        
    }

   

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
   
   
    cout<<endl<<endl;

       cout<<"Process\t"<<"   Arrival Time\t"<<"  Brust Time\t"<<"   Priority\t"<<"Turnaround Time\t"<<"   Waiting Time\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<"P"<<p[i].pid<<"\t\t"<<p[i].arrival_time<<"\t\t"<<p[i].burst_time<<"\t\t"<<p[i].priority<<"\t\t"<<p[i].turnaround_time<<"\t\t"<<p[i].waiting_time<<"\t\t"<<"\n"<<endl;
    }
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
   
}