#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

#define SHM_SIZE 10
const char* SHM_NAME = "/my_shm";

struct SharedBuffer {
    char buffer[SHM_SIZE];
    int write_index;
    int read_index;
};

int main() {
    // Create and truncate shared memory object
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "shm_open failed: " << strerror(errno) << "\n";
        return 1;
    }

    size_t total_size = sizeof(SharedBuffer);
    if (ftruncate(shm_fd, total_size) == -1) {
        std::cerr << "ftruncate failed: " << strerror(errno) << "\n";
        return 1;
    }

    // Map shared memory into address space
    void* ptr = mmap(0, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "mmap failed: " << strerror(errno) << "\n";
        return 1;
    }

    // Initialize buffer
    SharedBuffer* shared = static_cast<SharedBuffer*>(ptr);
    shared->write_index = 0;
    shared->read_index = 0;
    memset(shared->buffer, 0, SHM_SIZE);

    std::cout << "Enter text (Ctrl+C to quit):\n";
    char ch;
    while (std::cin.get(ch)) {
        shared->buffer[shared->write_index] = ch;
        shared->write_index = (shared->write_index + 1) % SHM_SIZE;
    }

    // Cleanup
    munmap(ptr, total_size);
    close(shm_fd);
    return 0;
}
