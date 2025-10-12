#include <iostream>
using namespace std;

int main() {
    int n, tq;
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

    cout << "Enter Time Quantum: ";
    cin >> tq;

    int time = 0, completed = 0;
    int ct[n] = {0}, tat[n], wt[n];
    cout << "\nGantt Chart (RR): ";

    while (completed != n) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0) {
                done = false;
                if (rem_bt[i] > tq) {
                    cout << "| P" << pid[i] << " ";
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    cout << "| P" << pid[i] << " ";
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    ct[i] = time;
                    completed++;
                }
            }
        }
        if (done) time++; // if no process arrived, idle CPU
    }
    cout << "|\n";

    // Calculate TAT and WT
    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avgTAT += tat[i];
        avgWT += wt[i];
    }

    cout << "\n===== Round Robin Results =====\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
        cout << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;

    cout << "\nAverage Turnaround Time: " << avgTAT / n;
    cout << "\nAverage Waiting Time: " << avgWT / n << endl;

    return 0;
}
