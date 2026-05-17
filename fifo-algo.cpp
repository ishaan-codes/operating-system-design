// FIFO page replacement algorithm replaces the oldest page in memory. It uses a queue to track page order. Simple to implement but may suffer from Belady's Anomaly.

#include<iostream>
using namespace std;
bool search(int key, int frame[], int frame_size) {
    for(int i=0; i<frame_size; i++)
        if(frame[i] == key)
            return true;
    return false;
}
int predict(int pages[], int frame[], int page_count, int frame_size, int index) {
    int pos = -1, farthest = index;
    for(int i=0; i<frame_size; i++) {
        int j;
        for(j=index; j<page_count; j++) {
            if(frame[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if(j == page_count)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}
void fifoPageReplacement(int pages[], int page_count, int frame_size) {
    int frame[frame_size];
    int faults = 0;
    int front = 0;    
    for(int i=0; i<frame_size; i++)
        frame[i] = -1;    
    cout << "Page\tFrames\t\tPage Faults\n";    
    for(int i=0; i<page_count; i++) {
        cout << pages[i] << "\t";        
        if(!search(pages[i], frame, frame_size)) {
            frame[front] = pages[i];
            front = (front + 1) % frame_size;
            faults++;            
            for(int j=0; j<frame_size; j++) {
                if(frame[j] != -1)
                    cout << frame[j] << " ";
                else
                    cout << "- ";
            }
            cout << "\t\tYes\n";
        } else {
            for(int j=0; j<frame_size; j++) {
                if(frame[j] != -1)
                    cout << frame[j] << " ";
                else
                    cout << "- ";
            }
            cout << "\t\tNo\n";
        }
    }
    cout << "\nTotal Page Faults: " << faults << endl;
}
int main() {
    int page_count, frame_size;    
    cout << "Enter number of pages: ";
    cin >> page_count;    
    int pages[page_count];
    cout << "Enter page reference sequence: ";
    for(int i=0; i<page_count; i++)
        cin >> pages[i];    
    cout << "Enter frame size: ";
    cin >> frame_size;    
    fifoPageReplacement(pages, page_count, frame_size);    
    return 0;
}