#include <iostream>
using namespace std;

bool isSafe(int n, int m, int available[], int max[][10], int alloc[][10], int need[][10], int safeSeq[]) {
    int work[10];
    bool finish[10] = {false};
    for (int i = 0; i < m; i++) work[i] = available[i];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j]) break;
                if (j == m) { // can allocate
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) return false; // deadlock
    }
    return true;
}

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    int max[10][10], alloc[10][10], need[10][10], available[10], safeSeq[10];

    cout << "Enter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max[i][j];

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "Enter Available Resources:\n";
    for (int i = 0; i < m; i++)
        cin >> available[i];

    // Compute Need Matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << need[i][j] << " ";
        cout << endl;
    }

    if (isSafe(n, m, available, max, alloc, need, safeSeq)) {
        cout << "\nSystem is in SAFE state.\nSafe sequence: ";
        for (int i = 0; i < n; i++)
            cout << "P" << safeSeq[i] << " ";
        cout << endl;
    } else {
        cout << "\nSystem is in UNSAFE state. Deadlock may occur.\n";
    }

    // Handle new request
    char choice;
    cout << "\nDo you want to enter a new request? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        int p, req[10];
        cout << "Enter process number (0 to " << n-1 << "): ";
        cin >> p;
        cout << "Enter request for each resource: ";
        for (int i = 0; i < m; i++) cin >> req[i];

        bool valid = true;
        for (int i = 0; i < m; i++)
            if (req[i] > need[p][i] || req[i] > available[i])
                valid = false;

        if (valid) {
            // Pretend allocation
            for (int i = 0; i < m; i++) {
                available[i] -= req[i];
                alloc[p][i] += req[i];
                need[p][i] -= req[i];
            }

            if (isSafe(n, m, available, max, alloc, need, safeSeq)) {
                cout << "Request can be granted.\nNew safe sequence: ";
                for (int i = 0; i < n; i++) cout << "P" << safeSeq[i] << " ";
                cout << endl;
            } else {
                cout << "Request CANNOT be granted. System would be unsafe.\n";
                // Rollback
                for (int i = 0; i < m; i++) {
                    available[i] += req[i];
                    alloc[p][i] -= req[i];
                    need[p][i] += req[i];
                }
            }
        } else {
            cout << "Request exceeds Need or Available resources. Cannot be granted.\n";
        }
    }

    return 0;
}
