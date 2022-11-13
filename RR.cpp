#include <bits/stdc++.h>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;

struct process {
	int pid;
	int arrival_time;
	int burst_time;
	int start_time;
	int completion_time;
	int turnaround_time;
	int waiting_time;
};

bool compare1(process p1, process p2)
{
	return p1.arrival_time < p2.arrival_time;
}

bool compare2(process p1, process p2)
{
	return p1.pid < p2.pid;
}

int main() {

	int n,i;
	int tq;
	struct process p[100];
	float avg_turnaround_time, avg_waiting_time, cpu_utilisation;
	int total_turnaround_time = 0, total_waiting_time = 0;
	float throughput;
	int burst_remaining[100];
	int idx;

	cout << setprecision(2) << fixed;

	cout << "Enter the number of processes: ";
	cin >> n;
	cout << "Enter time quantum: ";
	cin >> tq;
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
	for (int i = 0; i < n; i++) {
		
		burst_remaining[i] = p[i].burst_time;
		p[i].pid = i + 1;
		cout << endl;
	}

	sort(p, p + n, compare1);

	queue<int> q;
	int current_time = 0;
	q.push(0);
	int completed = 0;
	int mark[100];
	memset(mark, 0, sizeof(mark));
	mark[0] = 1;

	while (completed != n) {
		idx = q.front();
		q.pop();

		if (burst_remaining[idx] == p[idx].burst_time) {
			p[idx].start_time = max(current_time, p[idx].arrival_time);
			current_time = p[idx].start_time;
		}

		if (burst_remaining[idx] > tq) {
			burst_remaining[idx] -= tq;
			current_time += tq;
		}
		else {
			current_time += burst_remaining[idx];
			burst_remaining[idx] = 0;
			completed++;

			p[idx].completion_time = current_time;
			p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
			p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

			total_turnaround_time += p[idx].turnaround_time;
			total_waiting_time += p[idx].waiting_time;
		}

		for (int i = 1; i < n; i++) {
			if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
				q.push(i);
				mark[i] = 1;
			}
		}
		if (burst_remaining[idx] > 0) {
			q.push(idx);
		}

		if (q.empty()) {
			for (int i = 1; i < n; i++) {
				if (burst_remaining[i] > 0) {
					q.push(i);
					mark[i] = 1;
					break;
				}
			}
		}


	}

	avg_turnaround_time = (float) total_turnaround_time / n;
	avg_waiting_time = (float) total_waiting_time / n;

	sort(p, p + n, compare2);

	cout << endl;
	cout << "Process\t\t" << "Arrival Time\t" << " Burst Time\t" << " Turnaround Time\t" << "Waiting Time\t"<< "\n" << endl;

	for (int i = 0; i < n; i++) {
		cout << "  P"<<p[i].pid << "\t\t\t" << p[i].arrival_time << "\t\t" << p[i].burst_time << "\t\t"  << p[i].turnaround_time << "\t\t\t" << p[i].waiting_time << "\t" << "\n" << endl;
	}
	cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
	cout << "Average Waiting Time = " << avg_waiting_time << endl;
}