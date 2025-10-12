#include <iostream>
using namespace std;

int main() {
    int n, q;
    cout << "Enter number of queues: ";
    cin >> q;

    int tq[q]; // time quantum for each queue
    for (int i = 0; i < q; i++) {
        cout << "Enter Time Quantum for Queue " << i + 1 << ": ";
        cin >> tq[i];
    }

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[n], at[n], bt[n], rem_bt[n];
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time for P" << i + 1 << ": ";
        cin >> at[i];
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> bt[i];
        rem_bt[i] = bt[i];
    }

    int ct[n] = {0}, tat[n], wt[n];
    bool done[n] = {false};

    cout << "\n===== Multilevel Feedback Queue Scheduling =====\n";
    cout << "Gantt Chart:\n";

    int time = 0, completed = 0;
    int level = 0; // start with highest priority queue

    while (completed < n) {
        bool executed = false;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0 && !done[i]) {
                executed = true;
                cout << "| P" << pid[i] << " ";

                // Run for the queue's time quantum
                if (rem_bt[i] > tq[level]) {
                    rem_bt[i] -= tq[level];
                    time += tq[level];
                } else {
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    ct[i] = time;
                    done[i] = true;
                    completed++;
                }

                // After each process execution, move to next queue level (if any)
                if (level < q - 1) level++;
            }
        }

        // If no process arrived yet, increment time
        if (!executed) time++;
    }
    cout << "|\n";

    float avgTAT = 0, avgWT = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avgTAT += tat[i];
        avgWT += wt[i];
        cout << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    cout << "\nAverage Turnaround Time: " << avgTAT / n;
    cout << "\nAverage Waiting Time: " << avgWT / n << endl;

    return 0;
}
