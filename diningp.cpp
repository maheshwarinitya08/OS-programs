#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

const int N = 5; // Number of philosophers

enum State { THINKING, HUNGRY, EATING } state[N]; // States of philosophers
std::mutex mtx; // Mutex for critical section
std::condition_variable cv[N]; // Condition variables for each philosopher

void initialize() {
    for (int i = 0; i < N; ++i) {
        state[i] = THINKING;
    }
}

void test(int phil) {
    int left = (phil + N - 1) % N; // Left neighbor
    int right = (phil + 1) % N; // Right neighbor
    if (state[phil] == HUNGRY && state[left] != EATING && state[right] != EATING) {
        state[phil] = EATING;
        cv[phil].notify_one();
    }
}

void takeForks(int phil) {
    std::unique_lock<std::mutex> lock(mtx);
    state[phil] = HUNGRY;
    test(phil);
    while (state[phil] != EATING) {
        cv[phil].wait(lock);
    }
}

void putForks(int phil) {
    std::unique_lock<std::mutex> lock(mtx);
    state[phil] = THINKING;
    // Test left and right neighbors
    test((phil + N - 1) % N);
    test((phil + 1) % N);
}

void philosopher(int id) {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * id));
        takeForks(id);
        std::cout << "Philosopher " << id << " is eating." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        putForks(id);
    }
}

int main() {
    initialize();
    std::thread philosophers[N];
    for (int i = 0; i < N; ++i) {
        philosophers[i] = std::thread(philosopher, i);
    }
    
    for (int i = 0; i < N; ++i) {
        philosophers[i].join();
    }
    return 0;
}