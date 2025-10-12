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

    // Copy arrays for sorting based on (CPU + IO)
    int pidSJF[n], cpuSJF[n], ioSJF[n];
    for (int i = 0; i < n; i++) {
        pidSJF[i] = pid[i];
        cpuSJF[i] = cpu[i];
        ioSJF[i] = io[i];
    }

    // Sort using simple bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((cpuSJF[j] + ioSJF[j]) > (cpuSJF[j + 1] + ioSJF[j + 1])) {
                int temp;
                temp = pidSJF[j]; pidSJF[j] = pidSJF[j + 1]; pidSJF[j + 1] = temp;
                temp = cpuSJF[j]; cpuSJF[j] = cpuSJF[j + 1]; cpuSJF[j + 1] = temp;
                temp = ioSJF[j]; ioSJF[j] = ioSJF[j + 1]; ioSJF[j + 1] = temp;
            }
        }
    }

    int completion[n], turnaround[n], waiting[n];
    int time = 0;

    for (int i = 0; i < n; i++) {
        time += cpuSJF[i] + ioSJF[i];
        completion[i] = time;
        turnaround[i] = completion[i];
        waiting[i] = turnaround[i] - (cpuSJF[i] + ioSJF[i]);
    }

    cout << "\n===== SJF Scheduling =====\n";
    cout << "PID\tCPU\tIO\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
        cout << pidSJF[i] << "\t" << cpuSJF[i] << "\t" << ioSJF[i] << "\t"
             << completion[i] << "\t" << turnaround[i] << "\t" << waiting[i] << endl;

    cout << "\nGantt Chart (SJF): ";
    for (int i = 0; i < n; i++)
        cout << "| P" << pidSJF[i] << " ";
    cout << "|\n";

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
