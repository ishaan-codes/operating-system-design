// The Optimal page replacement algorithm replaces the page that will not be used for the longest period of time in the future. It's a theoretical algorithm that provides the minimum number of page faults. While not practical for real systems (as it requires future knowledge), it serves as a benchmark for comparing other page replacement algorithms.

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// Function to check if page exists in frames
bool search(int key, vector<int>& frames) {
    return find(frames.begin(), frames.end(), key) != frames.end();
}
// Function to find the page that won't be used for longest time
int predict(vector<int>& pages, vector<int>& frames, int page_count, int index) {
    int pos = -1, farthest = index;    
    for(int i = 0; i < frames.size(); i++) {
        int j;
        for(j = index; j < page_count; j++) {
            if(frames[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        // If page is never referenced again, return its index
        if(j == page_count)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}
void optimalPageReplacement(vector<int>& pages, int page_count, int frame_size) {
    vector<int> frames;
    int faults = 0;    
    cout << "Page Reference Sequence: ";
    for(int i = 0; i < page_count; i++) {
        cout << pages[i] << " ";
    }
    cout << "\n\n";    
    cout << "Page\tFrames\t\tPage Fault\n";
    cout << "-----\t------\t\t----------\n";    
    for(int i = 0; i < page_count; i++) {
        cout << pages[i]] << "\t";        
        // If page already exists in frames
        if(search(pages[i], frames)) {
            // Display current frames
            for(int j = 0; j < frames.size(); j++) {
                cout << frames[j] << " ";
            }
            for(int j = frames.size(); j < frame_size; j++) {
                cout << "- ";
            }
            cout << "\t\tNo\n";
            continue;
        }        
        // If frames are not full
        if(frames.size() < frame_size) {
            frames.push_back(pages[i]);
            faults++;
        } 
        // If frames are full, need replacement
        else {
            int pos = predict(pages, frames, page_count, i + 1);
            frames[pos] = pages[i];
            faults++;
        }        
        // Display current frames
        for(int j = 0; j < frames.size(); j++) {
            cout << frames[j] << " ";
        }
        for(int j = frames.size(); j < frame_size; j++) {
            cout << "- ";
        }
        cout << "\t\tYes\n";
    }    
    cout << "\nTotal Page Faults: " << faults << endl;
    cout << "Hit Ratio: " << (float)(page_count - faults) / page_count * 100 << "%" << endl;
}
void displayComparison() {
    cout << "\n\n=== Optimal Page Replacement Algorithm Characteristics ===\n";
    cout << "Advantages:\n";
    cout << "1. Provides minimum number of page faults\n";
    cout << "2. Serves as benchmark for other algorithms\n";
    cout << "3. Never suffers from Belady's Anomaly\n\n";    
    cout << "Disadvantages:\n";
    cout << "1. Not implementable in practice\n";
    cout << "2. Requires future knowledge of page references\n";
    cout << "3. High computational overhead\n";
}
int main() {
    int page_count, frame_size;    
    cout << "=== Optimal Page Replacement Algorithm ===\n\n";    
    cout << "Enter number of pages in reference string: ";
    cin >> page_count;    
    vector<int> pages(page_count);
    cout << "Enter page reference sequence: ";
    for(int i = 0; i < page_count; i++) {
        cin >> pages[i];
    }    
    cout << "Enter number of frames: ";
    cin >> frame_size;    
    cout << "\n";
    optimalPageReplacement(pages, page_count, frame_size);
    displayComparison();    
    return 0;
}