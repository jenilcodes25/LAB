#include <iostream>
#include <climits>
using namespace std;

int main() {
    int n;
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

    int complete = 0, time = 0, minm = INT_MAX, shortest = 0, finish_time;
    bool check = false;
    int ct[n] = {0}, tat[n], wt[n];
    cout << "\nGantt Chart (SRTF): ";

    while (complete != n) {
        minm = INT_MAX;
        for (int j = 0; j < n; j++) {
            if ((at[j] <= time) && (rem_bt[j] < minm) && rem_bt[j] > 0) {
                minm = rem_bt[j];
                shortest = j;
                check = true;
            }
        }

        if (!check) { time++; continue; }

        rem_bt[shortest]--;
        cout << "| P" << pid[shortest] << " ";
        if (rem_bt[shortest] == 0) {
            complete++;
            check = false;
            finish_time = time + 1;
            ct[shortest] = finish_time;
        }
        time++;
    }
    cout << "|\n";

    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avgTAT += tat[i];
        avgWT += wt[i];
    }

    cout << "\n===== SRTF Results =====\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
        cout << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;

    cout << "\nAverage Turnaround Time: " << avgTAT / n;
    cout << "\nAverage Waiting Time: " << avgWT / n << endl;

    return 0;
}
