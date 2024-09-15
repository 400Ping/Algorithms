//Exmaple Resource allocation bandker algorithm

#include <iostream>
using namespace std;

int main() {
    int n, r, i, j, k;
    n = 3; // Indicates the Number of processes 
    r = 2; // Indicates the Number of resources 
    int alloc[3][2] = { { 1, 0 }, // Process P1, Allocation: R1=1, R2=0
                        { 0, 1 }, // Process P2, Allocation: R1=0, R2=1
                        { 0, 1 } }; // Process P3, Allocation: R1=0, R2=1

    int need[3][2] = { { 0, 1 }, // Process P1, Need: R1=0, R2=1
                       { 1, 0 }, // Process P2, Need: R1=1, R2=0
                       { 0, 0 } }; // Process P3, Need: R1=0, R2=0

    int avail[2] = { 1, 1 }; // These are Available Resources 

    int f[n], ans[n], ind = 0; 
    for (k = 0; k < n; k++) { 
        f[k] = 0; 
    } 

    int y = 0; 
    // First, check if P3 can be executed
    for (i = 0; i < n; i++) { 
        if (f[i] == 0) { 
            int flag = 0; 
            for (j = 0; j < r; j++) { 
                if (need[i][j] > avail[j]){ 
                    flag = 1; 
                    break; 
                } 
            } 
            if (flag == 0 && i == 2) { // Process P3
                ans[ind++] = i; 
                for (y = 0; y < r; y++) 
                    avail[y] += alloc[i][y]; 
                f[i] = 1; 
            } 
        } 
    } 
    // Then, check if P1 and P2 can be executed
    for (k = 0; k < n; k++) { 
        if (f[k] == 0) { 
            int flag = 0; 
            for (j = 0; j < r; j++) { 
                if (need[k][j] > avail[j]){ 
                    flag = 1; 
                    break; 
                } 
            } 
            if (flag == 0) { 
                ans[ind++] = k; 
                for (y = 0; y < r; y++) 
                    avail[y] += alloc[k][y]; 
                f[k] = 1; 
            } 
        } 
    } 

    cout << "The SAFE Sequence is as follows" << endl; 
    for (i = 0; i < n - 1; i++) 
        cout << " P" << ans[i]+1 << " ->"; 
    cout << " P" << ans[n - 1]+1 << endl;

    return 0; 
}


//Exmaple2 Resource allocation bandker algorithm

#include <iostream>
using namespace std;

int main() {
    // Given data
    int allocation[4][3] = {{1, 0, 1}, {1, 1, 0}, {0, 1, 0}, {0, 1, 0}};
    int need[4][3] = {{0, 1, 1}, {1, 0, 0}, {0, 0, 1}, {0, 2, 0}};
    int available[3] = {0, 0, 1}; // Available resources: R1=0, R2=0, R3=1

    int n = 4; // Number of processes
    int m = 3; // Number of resource types

    int work[3]; // Initialize the work vector with available resources
    for (int i = 0; i < m; ++i) {
        work[i] = available[i];
    }

    bool finish[4] = {false}; // Initialize finish vector, initially all processes are not finished
    int safeSequence[4]; // Store the safe sequence
    int count = 0;

    // Iterate until all processes are finished or no safe sequence is found
    while (count < n) {
        bool found = false;

        // Check for a process that can be executed
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                // If all resources for process i can be allocated
                if (canExecute) {
                    // Allocate resources to process i
                    for (int j = 0; j < m; ++j) {
                        work[j] += allocation[i][j];
                    }

                    // Mark process i as finished
                    finish[i] = true;

                    // Add process i to safe sequence
                    safeSequence[count++] = i;

                    found = true;
                }
            }
        }

        // If no process can be executed with the current available resources
        if (!found) {
            cout << "No safe sequence exists." << endl;
            return 0;
        }
    }

    // Print the safe sequence
    cout << "Safe sequence: ";
    for (int i = 0; i < n - 1; ++i) {
        cout << "P" << safeSequence[i] << " -> ";
    }
    cout << "P" << safeSequence[n - 1] << endl;

    return 0;
}