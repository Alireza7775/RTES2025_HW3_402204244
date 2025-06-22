#include <iostream>
#include <csignal>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <PID> <SIGNAL_NUMBER>" << std::endl;
        return 1;
    }

    pid_t pid = std::stoi(argv[1]);
    int signal_number = std::stoi(argv[2]);

    if (kill(pid, signal_number) == -1) {
        perror("Error sending signal");
        return 1;
    }

    std::cout << "Signal " << signal_number << " sent to process " << pid << std::endl;
    return 0;
}