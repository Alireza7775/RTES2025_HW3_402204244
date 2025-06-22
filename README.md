# 📚 Embedded Linux Exercise 3 : OrangePi Zero 2 Plus

Welcome to the Embedded Linux exercise for setting up and exploring the **OrangePi Zero 2 Plus** board. Follow the steps below to configure the board, connect to networks, and implement tasks to deepen your understanding of embedded systems. 🚀

# Assignment Submission Instructions

Push your repository to your GitHub account and set it to public. I will clone the repository and assign your grade based on its contents. Additionally, record a video (using your phone, not screen recording) demonstrating the stages of your code (e.g., development or execution). Create a text file named `repolink.txt` containing only your GitHub repository URL. Package the video, the repository folder, and `repolink.txt` into a single ZIP file named `RTES2025_HW3_{student_number}.zip`, where `{student_number}` is your student ID. Upload the ZIP file to CW. Answer the assignment questions in the repository's `README.md` file using Markdown syntax.

The ZIP file should follow this directory structure:

```
RTES2025_HW3_401234567
├── HW3.mp4  # Supported formats: mp4, mkv, mpeg, or similar
├── repolink.txt       # Contains the GitHub repository URL
└── RTES2025_HW3       # Repository folder
    ├── auto-wifi-connect
    ├── ipc
    └── ...
```

---

### 🛠️ Setting Up the OrangePi Zero 2 Plus
Follow the instructional video to configure the OrangePi Zero 2 Plus board.

---

### 🌐 Wi-Fi and SSH Connection
1. Create a Wi-Fi hotspot using your phone 📱 or laptop 💻 with a custom SSID and password. Ensure the frequency is set to **2.4 GHz** and internet access is enabled.
   - **💡 Tip**: Use the `nmcli` command to connect to Wi-Fi.
   - **💡 Tip**: Connect to the board via SSH using the **Remote – SSH** extension in VS Code or an SSH client (e.g., PuTTY) for a smoother workflow.

---

### 🗂️ Introduction to Git
Clone the provided repository 📂 using SSH. The repository contains incomplete code and testing tools for the tasks below.
---

### 📡 Automatic Wi-Fi Connection
Write a shell script 🖥️ using `nmcli` to automatically connect to a specified Wi-Fi network (e.g., **MySSID**) if the device is not already connected.
- Schedule the script to run **every minutes** using a **cron job**.
- Configure the script to execute once at **system boot** using the cron `@reboot` directive.
- Log connection status, available Wi-Fi networks, and other relevant details to a file named `auto-connect.log`.

---

### 🔗 Inter-Process Communication Mechanisms
Explore three inter-process communication (IPC) methods to understand task communication in Linux:
1. **FIFO** 📥📤
2. **Linux Signals** ⚡
3. **Shared Memory** 🗄️

#### 1. FIFO
Complete the provided `fifo-sender.sh` and `fifo-receiver.sh` scripts in the GitHub repository. When executed:
- The sender script should create a FIFO (if it doesn't exist) and transmit terminal input to the receiver via the FIFO.
- The receiver should display the input immediately.

#### 2. Linux Signals
Complete the provided C++ programs `signal-receiver.cpp` and `signal-sender.cpp`:
- **Receiver** 🖨️: Prints its **PID** on startup, waits for signals, and logs each received signal to a file.
- **Sender** 📩: Accepts a PID and signal number as command-line arguments and sends the signal to the specified process.
Answer the following:
- ❓ What is the difference between the **SIGINT** and **SIGKILL** signals?
    - SIGINT (Signal Interrupt): This is typically sent when you press Ctrl+C in a terminal. It politely asks the process to terminate. The process can catch and handle this signal—for example, to clean up resources before exiting or even to ignore it entirely.
    - SIGKILL (Signal Kill): This is the heavy hammer. It immediately and unconditionally terminates the process. It can't be caught, blocked, or ignored. No cleanup, no questions asked. The process is gone as soon as the kernel delivers the signal.
- ❓ Which signals can be caught or handled by a process?
    - <code>SIGHUP (1) — Hangup detected on controlling terminal</code>
    - <code>SIGINT (2) — Interrupt (Ctrl+C)</code>
    - <code>SIGQUIT (3) — Quit from keyboard</code>
    - <code>SIGILL (4) — Illegal Instruction</code>
    - <code>SIGTRAP (5) — Trace/breakpoint trap</code>
    - <code>SIGABRT (6) — Abort signal from abort()</code>
    - <code>SIGBUS (7) — Bus error</code>
    - <code>SIGFPE (8) — Floating point exception</code>
    - <code>SIGUSR1 (10), SIGUSR2 (12) — User-defined signals</code>
    - <code>SIGSEGV (11) — Segmentation fault (can be caught, though usually fatal)</code>
    - <code>SIGPIPE (13) — Broken pipe</code>
    - <code>SIGALRM (14) — Timer signal</code>
    - <code>SIGTERM (15) — Termination request</code>
    - <code>SIGCHLD (17) — Child stopped or terminated</code>
    - <code>SIGCONT (18) — Continue if stopped</code>
    - <code>SIGTSTP (20) — Stop typed at terminal (Ctrl+Z)</code>
    - <code>SIGTTIN, SIGTTOU (21, 22) — Background I/O from terminal</code>
    - <code>SIGXCPU, SIGXFSZ (24, 25) — CPU/file size limits exceeded</code>
    - <code>SIGVTALRM, SIGPROF (26, 27) — Timers</code>
    - <code>SIGWINCH (28) — Window size change</code>
    - <code>SIGPOLL, SIGIO (29) — I/O now possible</code>
    - <code>SIGSYS</code>
- ❓ How many signals are defined in Linux?
    - Standard signals: These are the traditional signals, numbered from 1 to 31. They include signals like SIGINT, SIGKILL, SIGTERM, and SIGSEGV.
    - Real-time signals: These are newer and more flexible, introduced by POSIX. Linux supports 33 real-time signals, typically numbered from 32 to 64. However, some of these may be reserved internally by the system or libraries like glibc.

#### 3. Shared Memory
Complete the provided C++ programs `shm-writer.cpp` and `shm-reader.cpp`:
- **Writer** ✍️: Creates a shared memory segment and writes user input into a **10-character circular buffer**.
- **Reader** 📖: Reads and displays the contents of the shared memory upon execution.

Answer the following:
- ❓ What are the key differences between FIFO and shared memory for IPC?
    - **Communication Type**
        - FIFO (Named Pipe): It’s stream-based—like a regular pipe—transferring data byte by byte.
        - Shared Memory: It allows both processes to access a common memory region directly.
    - **Speed**
        - FIFO: Generally slower due to kernel buffering and the overhead of read/write system calls.
        - Shared Memory: Much faster because memory is accessed directly without intermediate copying.
    - **Synchronization**
        - FIFO: Offers implicit synchronization since read/write operations are blocking by nature.
        - Shared Memory: Needs explicit synchronization (like semaphores or mutexes) to coordinate access.
    - **Persistence**
        - FIFO: Exists as a special file in the filesystem (created with mkfifo or mknod).
        - Shared Memory: Exists in memory only, and is removed when no longer attached or used.
    - **Setup Complexity**
        - FIFO: Easier to set up—just create the file and use open/read/write.
        - Shared Memory: More complex—it involves allocating (shmget), attaching (shmat), and detaching (shmdt), often paired with synchronization.
    - **Use Cases**
        - FIFO: Best for sequential or simple data transfer (like logs or commands).
        - Shared Memory: Ideal for high-throughput or real-time needs (like sensor data processing or large buffer sharing).
---

### 🌍 Basic Web Server
Complete the provided shell script 🌐 to create a simple web server that listens on **port 80** and responds to HTTP requests with the system’s current **date and time**.
- It should print the response in the terminal too when run by terminal.
- Create a Systemd Service (webserver.service) so that:
    Start after the network is online (connected to wifi).
    Restart automatically if the script exits (with a 5-second delay).
    Log output and errors to the system journal.
    Run on system boot.
You should put the service file behind the webserver script in the submission and in the repository.

- **💡 Tip**: Use the `nc` (netcat) command for handling network connections.
    
---

### 📚 Useful Reference Websites
- **OrangePi Documentation**: [Official OrangePi Wiki](http://www.orangepi.org/orangepiwiki/) – Guides for setting up OrangePi boards.
- **Linux Networking**: [nmcli Documentation](https://networkmanager.dev/docs/api/latest/nmcli.html) – Manage Wi-Fi with `nmcli`.
- **Git Basics**: [Git SCM](https://git-scm.com/doc) – Official Git documentation for cloning and managing repositories.
- **Systemd Services**: [Systemd Documentation](https://www.freedesktop.org/software/systemd/man/systemd.service.html) – Guide to creating systemd services.
- **Linux IPC**: [Beej’s Guide to IPC](https://beej.us/guide/bgipc/) – Comprehensive resource on FIFO, signals, and shared memory.
- **Netcat Usage**: [Netcat Manual](http://nc110.sourceforge.net/) – Learn how to use `nc` for networking tasks.

---

Happy coding! 🎉
