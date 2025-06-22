#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

#define SHM_SIZE 10
const char* SHM_NAME = "/my_shm";

struct SharedBuffer {
    char buffer[SHM_SIZE];
    int write_index;
    int read_index;
};

int main() {
    // Open existing shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        std::cerr << "shm_open failed: " << strerror(errno) << "\n";
        return 1;
    }

    size_t total_size = sizeof(SharedBuffer);
    void* ptr = mmap(0, total_size, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "mmap failed: " << strerror(errno) << "\n";
        return 1;
    }

    SharedBuffer* shared = static_cast<SharedBuffer*>(ptr);

    std::cout << "Shared memory contents:\n";
    for (int i = 0; i < SHM_SIZE; ++i) {
        char c = shared->buffer[i];
        if (c != 0) std::cout << c;
    }
    std::cout << "\n";

    munmap(ptr, total_size);
    close(shm_fd);
    return 0;
}
