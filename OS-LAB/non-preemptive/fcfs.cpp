#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int pid[n], cpu[n], io[n];
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter CPU Burst time for P" << i + 1 << ": ";
        cin >> cpu[i];
        cout << "Enter I/O Burst time for P" << i + 1 << ": ";
        cin >> io[i];
    }

    int completion[n], turnaround[n], waiting[n];
    int time = 0;

    for (int i = 0; i < n; i++) {
        time += cpu[i] + io[i]; // total burst (CPU + I/O)
        completion[i] = time;
        turnaround[i] = completion[i]; // since arrival time = 0
        waiting[i] = turnaround[i] - (cpu[i] + io[i]);
    }

    cout << "\n===== FCFS Scheduling =====\n";
    cout << "PID\tCPU\tIO\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
        cout << pid[i] << "\t" << cpu[i] << "\t" << io[i] << "\t"
             << completion[i] << "\t" << turnaround[i] << "\t" << waiting[i] << endl;

    // Gantt Chart
    cout << "\nGantt Chart (FCFS): ";
    for (int i = 0; i < n; i++)
        cout << "| P" << pid[i] << " ";
    cout << "|\n";

    // Averages
    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        avgTAT += turnaround[i];
        avgWT += waiting[i];
    }
    avgTAT /= n;
    avgWT /= n;

    cout << "\nAverage Turnaround Time: " << avgTAT;
    cout << "\nAverage Waiting Time: " << avgWT << endl;

    return 0;
}
