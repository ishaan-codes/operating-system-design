// Memory allocation algorithms find suitable memory blocks for processes:
// First Fit: Allocates first sufficient block
// Best Fit: Allocates smallest sufficient block
// Worst Fit: Allocates largest sufficient block

#include<iostream>
using namespace std;
void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];    
    for(int i=0; i<n; i++)
        allocation[i] = -1;    
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }    
    cout << "\nFirst Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock no.\n";
    for(int i=0; i<n; i++) {
        cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t";
        if(allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}
void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];    
    for(int i=0; i<n; i++)
        allocation[i] = -1;    
    for(int i=0; i<n; i++) {
        int bestIdx = -1;
        for(int j=0; j<m; j++) {
            if(blockSize[j] >= processSize[i]) {
                if(bestIdx == -1)
                    bestIdx = j;
                else if(blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }        
        if(bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }    
    cout << "\nBest Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock no.\n";
    for(int i=0; i<n; i++) {
        cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t";
        if(allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}
void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];    
    for(int i=0; i<n; i++)
        allocation[i] = -1;    
    for(int i=0; i<n; i++) {
        int worstIdx = -1;
        for(int j=0; j<m; j++) {
            if(blockSize[j] >= processSize[i]) {
                if(worstIdx == -1)
                    worstIdx = j;
                else if(blockSize[worstIdx] < blockSize[j])
                    worstIdx = j;
            }
        }        
        if(worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }    
    cout << "\nWorst Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock no.\n";
    for(int i=0; i<n; i++) {
        cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t";
        if(allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}
int main() {
    int m, n;    
    cout << "Enter number of memory blocks: ";
    cin >> m;
    int blockSize[m];
    cout << "Enter sizes of memory blocks: ";
    for(int i=0; i<m; i++)
        cin >> blockSize[i];    
    cout << "Enter number of processes: ";
    cin >> n;
    int processSize[n];
    cout << "Enter sizes of processes: ";
    for(int i=0; i<n; i++)
        cin >> processSize[i];    
    // Create copies for each algorithm
    int block1[m], block2[m], block3[m];
    for(int i=0; i<m; i++) {
        block1[i] = blockSize[i];
        block2[i] = blockSize[i];
        block3[i] = blockSize[i];
    }    
    firstFit(block1, m, processSize, n);
    bestFit(block2, m, processSize, n);
    worstFit(block3, m, processSize, n);    
    return 0;
}