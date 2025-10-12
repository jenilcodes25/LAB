#include <iostream>
#include <cmath>
using namespace std;

// FIFO Disk Scheduling
void FIFO(int request[], int n, int head) {
    int totalSeek = 0;
    int current = head;
    for (int i = 0; i < n; i++) {
        totalSeek += abs(request[i] - current);
        current = request[i];
    }
    cout << "\nFIFO Total Seek Time: " << totalSeek;
    cout << "\nFIFO Average Seek Time: " << (float)totalSeek / n << endl;
}

// SSTF Disk Scheduling
void SSTF(int request[], int n, int head) {
    int seekCount = 0, visited[100] = {0};
    int current = head;

    for (int i = 0; i < n; i++) {
        int minDist = 1e9, idx = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(request[j] - current) < minDist) {
                minDist = abs(request[j] - current);
                idx = j;
            }
        }
        visited[idx] = 1;
        seekCount += minDist;
        current = request[idx];
    }
    cout << "\nSSTF Total Seek Time: " << seekCount;
    cout << "\nSSTF Average Seek Time: " << (float)seekCount / n << endl;
}

// SCAN Disk Scheduling
void SCAN(int request[], int n, int head, int diskSize, int direction) {
    int seekCount = 0;
    int left[100], right[100];
    int lCount = 0, rCount = 0;

    for (int i = 0; i < n; i++) {
        if (request[i] < head) left[lCount++] = request[i];
        else right[rCount++] = request[i];
    }

    // Sort left and right arrays
    for (int i = 0; i < lCount-1; i++)
        for (int j = i+1; j < lCount; j++)
            if (left[i] > left[j]) swap(left[i], left[j]);

    for (int i = 0; i < rCount-1; i++)
        for (int j = i+1; j < rCount; j++)
            if (right[i] > right[j]) swap(right[i], right[j]);

    int current = head;

    if (direction == 0) { // Move towards 0 first
        for (int i = lCount-1; i >= 0; i--) {
            seekCount += abs(current - left[i]);
            current = left[i];
        }
        seekCount += current; // Move to start (0)
        current = 0;
        for (int i = 0; i < rCount; i++) {
            seekCount += abs(current - right[i]);
            current = right[i];
        }
    } else { // Move towards end first
        for (int i = 0; i < rCount; i++) {
            seekCount += abs(current - right[i]);
            current = right[i];
        }
        seekCount += abs(current - (diskSize-1));
        current = diskSize-1;
        for (int i = lCount-1; i >= 0; i--) {
            seekCount += abs(current - left[i]);
            current = left[i];
        }
    }

    cout << "\nSCAN Total Seek Time: " << seekCount;
    cout << "\nSCAN Average Seek Time: " << (float)seekCount / n << endl;
}

int main() {
    int n, head, diskSize, direction;
    cout << "Enter number of requests: ";
    cin >> n;

    int request[n];
    cout << "Enter request sequence: ";
    for (int i = 0; i < n; i++) cin >> request[i];

    cout << "Enter initial head position: ";
    cin >> head;
    cout << "Enter disk size: ";
    cin >> diskSize;
    cout << "Enter direction for SCAN (0: towards 0, 1: towards end): ";
    cin >> direction;

    FIFO(request, n, head);
    SSTF(request, n, head);
    SCAN(request, n, head, diskSize, direction);

    return 0;
}
