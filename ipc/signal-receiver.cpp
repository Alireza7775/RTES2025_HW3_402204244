#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <fstream>
#include <csignal>

std::ofstream log_file;

void signal_handler(int signal) {
    log_file << "Received signal: " << signal << std::endl;
    log_file.flush();
}

int main() {
    // Print PID
    pid_t pid = getpid();
    std::cout << "Receiver PID: " << pid << std::endl;

    // Open log file
    log_file.open("signal_log.txt", std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return 1;
    }

    // Register signal handlers for common signals
    for (int sig = 1; sig < 32; ++sig) {
        signal(sig, signal_handler);
    }

    // Wait for signals indefinitely
    while (true) {
        pause(); // Wait for signal
    }

    log_file.close();
    return 0;
}