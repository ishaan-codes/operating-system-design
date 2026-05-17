// The producer-consumer problem involves two processes sharing a fixed-size buffer. Producers add items, consumers remove items. Semaphores ensure mutual exclusion and proper synchronization.

#include<iostream>
#include<thread>
#include<semaphore>
#include<queue>
#include<chrono>
using namespace std;
const int BUFFER_SIZE = 5;
// Binary semaphore for mutual exclusion
binary_semaphore mutex(1);
// Counting semaphores for empty and full slots
counting_semaphore empty_slots(BUFFER_SIZE);
counting_semaphore full_slots(0);
queue<int> buffer;
int item_counter = 0;
void producer(int id) {
    for(int i=0; i<5; i++) {
        // Wait for empty slot
        empty_slots.acquire();        
        // Critical section entry
        mutex.acquire();        
        // Produce item
        int item = ++item_counter;
        buffer.push(item);
        cout << "Producer " << id << " produced item: " << item 
             << " | Buffer size: " << buffer.size() << endl;        
        // Critical section exit
        mutex.release();        
        // Signal that a slot is full
        full_slots.release();        
        // Simulate production time
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
void consumer(int id) {
    for(int i=0; i<5; i++) {
        // Wait for full slot
        full_slots.acquire();        
        // Critical section entry
        mutex.acquire();        
        // Consume item
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed item: " << item 
             << " | Buffer size: " << buffer.size() << endl;        
        // Critical section exit
        mutex.release();
        
        // Signal that a slot is empty
        empty_slots.release();        
        // Simulate consumption time
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}
int main() {
    cout << "=== Producer-Consumer Problem using Semaphores ===\n";
    cout << "Buffer size: " << BUFFER_SIZE << "\n\n";    
    thread producers[2];
    thread consumers[2];    
    // Create producer threads
    for(int i=0; i<2; i++) {
        producers[i] = thread(producer, i+1);
    }    
    // Create consumer threads
    for(int i=0; i<2; i++) {
        consumers[i] = thread(consumer, i+1);
    }    
    // Wait for all threads to complete
    for(int i=0; i<2; i++) {
        producers[i].join();
        consumers[i].join();
    }    
    cout << "\nAll producers and consumers finished!\n";    
    return 0;
}