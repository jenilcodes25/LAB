#include <iostream>
using namespace std;

void firstFit(int block[], int m, int process[], int n) {
    int allocation[n]; // store block index for each process
    int internalFrag = 0;

    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (block[j] >= process[i]) {
                allocation[i] = j;
                internalFrag += block[j] - process[i];
                block[j] -= process[i];
                break;
            }
        }
    }

    cout << "\n---First Fit Allocation---\n";
    cout << "Process\tSize\tBlock\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" << process[i] << "\t";
        if (allocation[i] != -1) cout << allocation[i]+1;
        else cout << "Not Allocated";
        cout << endl;
    }
    cout << "Total Internal Fragmentation: " << internalFrag << endl;
    int externalFrag = 0;
    for (int i = 0; i < m; i++) externalFrag += block[i];
    cout << "External Fragmentation: " << externalFrag << endl;
}

void bestFit(int block[], int m, int process[], int n) {
    int allocation[n];
    int internalFrag = 0;
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (block[j] >= process[i]) {
                if (bestIdx == -1 || block[j] < block[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            internalFrag += block[bestIdx] - process[i];
            block[bestIdx] -= process[i];
        }
    }

    cout << "\n---Best Fit Allocation---\n";
    cout << "Process\tSize\tBlock\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" << process[i] << "\t";
        if (allocation[i] != -1) cout << allocation[i]+1;
        else cout << "Not Allocated";
        cout << endl;
    }
    cout << "Total Internal Fragmentation: " << internalFrag << endl;
    int externalFrag = 0;
    for (int i = 0; i < m; i++) externalFrag += block[i];
    cout << "External Fragmentation: " << externalFrag << endl;
}

void worstFit(int block[], int m, int process[], int n) {
    int allocation[n];
    int internalFrag = 0;
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (block[j] >= process[i]) {
                if (worstIdx == -1 || block[j] > block[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            internalFrag += block[worstIdx] - process[i];
            block[worstIdx] -= process[i];
        }
    }

    cout << "\n---Worst Fit Allocation---\n";
    cout << "Process\tSize\tBlock\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" << process[i] << "\t";
        if (allocation[i] != -1) cout << allocation[i]+1;
        else cout << "Not Allocated";
        cout << endl;
    }
    cout << "Total Internal Fragmentation: " << internalFrag << endl;
    int externalFrag = 0;
    for (int i = 0; i < m; i++) externalFrag += block[i];
    cout << "External Fragmentation: " << externalFrag << endl;
}

int main() {
    int m, n;
    cout << "Enter number of memory blocks: ";
    cin >> m;
    int block[m];
    cout << "Enter block sizes:\n";
    for (int i = 0; i < m; i++) cin >> block[i];

    cout << "Enter number of processes: ";
    cin >> n;
    int process[n];
    cout << "Enter process sizes:\n";
    for (int i = 0; i < n; i++) cin >> process[i];

    int blockFF[m], blockBF[m], blockWF[m];
    for (int i = 0; i < m; i++) {
        blockFF[i] = block[i];
        blockBF[i] = block[i];
        blockWF[i] = block[i];
    }

    firstFit(blockFF, m, process, n);
    bestFit(blockBF, m, process, n);
    worstFit(blockWF, m, process, n);

    return 0;
}
