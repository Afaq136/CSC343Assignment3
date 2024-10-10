#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <climits>

int findMin(int arr[], int start, int end) {
    int min = INT_MAX;
    for (int i = start; i < end; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    const int size = 20;
    int arr[size];

    // Fill the array with random numbers
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100 + 1;  // Random numbers between 1 and 100
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    if (pid == 0) {
        // Child process
        int childMin = findMin(arr, size / 2, size);
        std::cout << "Child Process (PID: " << getpid() << ") - Minimum in second half: " << childMin << std::endl;
        exit(0);
    } else {
        // Parent process
        int parentMin = findMin(arr, 0, size / 2);
        std::cout << "Parent Process (PID: " << getpid() << ") - Minimum in first half: " << parentMin << std::endl;

        // Wait for child process to finish
        wait(NULL);
    }

    return 0;
}
