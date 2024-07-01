#include <iostream>
using namespace std;

// Number of processes and resources
const int P = 5; // Number of processes
const int R = 3; // Number of resources

// Function to check if system is in a safe state
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];

    // Calculate the need matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    // Mark all processes as unfinished
    bool finish[P];
    for (int k = 0; k < P; k++) {
        finish[k] = false;
    }

    // To store the safe sequence
    int safeSeq[P];

    // Copy the available resources to work array
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    // Find an unfinished process whose needs can be satisfied
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j])
                        break;
                }
                if (j == R) {
                    // If all resources for this process can be allocated
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "System is not in a safe state" << endl;
            return false;
        }
    }

    // If system is in a safe state, print the safe sequence
    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < P; i++) {
        cout << safeSeq[i] << " ";
    }
    cout << endl;
    return true;
}

int main() {
    // Example processes
    int processes[P] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int avail[R] = {3, 3, 2}; // Updated available resources
    cout<<"Name: Nitya Maheshwari\n";
    // Maximum resources that can be allocated to processes
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Resources allocated to processes
    int allot[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Check if the system is in a safe state or not
    isSafe(processes, avail, max, allot);
    cout<<"Enrollment no: 0827CS221185";

    return 0;
}

