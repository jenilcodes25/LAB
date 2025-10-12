#include <iostream>
using namespace std;

// Function to check if page exists in frame
bool isHit(int frame[], int f, int page) {
    for (int i = 0; i < f; i++)
        if (frame[i] == page) return true;
    return false;
}

// FIFO Page Replacement
int FIFO(int pages[], int n, int f) {
    int frame[f], index = 0, pageFaults = 0;
    for (int i = 0; i < f; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!isHit(frame, f, pages[i])) {
            frame[index] = pages[i];
            index = (index + 1) % f;
            pageFaults++;
        }
    }
    return pageFaults;
}

// LRU Page Replacement
int LRU(int pages[], int n, int f) {
    int frame[f], time[f], pageFaults = 0;
    for (int i = 0; i < f; i++) frame[i] = -1, time[i] = 0;

    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                hit = true;
                time[j] = i; // update last used
                break;
            }
        }
        if (!hit) {
            int lruIndex = 0;
            int minTime = time[0];
            for (int j = 1; j < f; j++)
                if (time[j] < minTime) { minTime = time[j]; lruIndex = j; }

            frame[lruIndex] = pages[i];
            time[lruIndex] = i;
            pageFaults++;
        }
    }
    return pageFaults;
}

// Optimal Page Replacement
int Optimal(int pages[], int n, int f) {
    int frame[f], pageFaults = 0;
    for (int i = 0; i < f; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!isHit(frame, f, pages[i])) {
            // find optimal replacement index
            int replaceIndex = -1, farthest = i;
            for (int j = 0; j < f; j++) {
                int k;
                for (k = i + 1; k < n; k++)
                    if (frame[j] == pages[k]) break;
                if (k == n) { replaceIndex = j; break; } // not used again
                if (k > farthest) { farthest = k; replaceIndex = j; }
            }
            if (replaceIndex == -1) replaceIndex = 0;
            frame[replaceIndex] = pages[i];
            pageFaults++;
        }
    }
    return pageFaults;
}

int main() {
    int n, f;
    cout << "Enter number of pages: ";
    cin >> n;
    int pages[n];
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> f;

    int fifoFaults = FIFO(pages, n, f);
    int lruFaults = LRU(pages, n, f);
    int optimalFaults = Optimal(pages, n, f);

    cout << "\nPage Replacement Results:\n";
    cout << "Algorithm\tPage Faults\tHit Ratio\tMiss Ratio\n";
    cout << "FIFO\t\t" << fifoFaults << "\t\t" << (float)(n - fifoFaults)/n << "\t\t" << (float)fifoFaults/n << endl;
    cout << "LRU\t\t" << lruFaults << "\t\t" << (float)(n - lruFaults)/n << "\t\t" << (float)lruFaults/n << endl;
    cout << "Optimal\t\t" << optimalFaults << "\t\t" << (float)(n - optimalFaults)/n << "\t\t" << (float)optimalFaults/n << endl;

    return 0;
}
