*This project has been created as part of the 42 curriculum by yel-moha.*

# Minitalk

## Description

**Minitalk** is an inter-process communication project developed as part of the 42 curriculum.  
The goal of the project is to create a client-server communication system using UNIX signals (`SIGUSR1` and `SIGUSR2`).

The server runs and displays its PID, then waits for incoming signals. The client takes the server PID and a message as arguments, then sends the message character by character using signals, where each bit is transmitted as a signal.

This project focuses on:
- UNIX signals handling
- Bit manipulation
- Inter-process communication (IPC)
- Clean and norm-compliant C code

---

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will generate two executables: `server` and `client`.

### Execution

First, start the server:

```bash
./server
```

The server will display its PID. Then, in another terminal, run the client:

```bash
./client <server_pid> "Your message here"
```

### Example

```bash
# Terminal 1
$ ./server
PID getpid() = 12345

# Terminal 2
$ ./client 12345 "Hello, World!"

# Terminal 1 output
Hello, World!
```

---

## Resources

### Concepts & Theory

- UNIX signals (SIGUSR1, SIGUSR2)
- Signal handlers and `sigaction`
- Bit manipulation and bitwise operations
- Process identification (PID)
- Inter-process communication

### References

- https://en.wikipedia.org/wiki/Signal_(IPC)
- https://man7.org/linux/man-pages/man2/sigaction.2.html
- https://man7.org/linux/man-pages/man2/kill.2.html

---

## AI Usage Disclosure

Artificial Intelligence tools (such as ChatGPT) were used during the development of this project to clarify project requirements, refactor functions to comply with Norminette constraints, improve code structure, and debug logical issues.

All algorithmic decisions, implementations, and final code validation were performed by the author.

---

## Project Structure

### Source Files

| File | Description |
|------|-------------|
| `server.c` | Server program that receives and decodes signals |
| `client.c` | Client program that sends messages as signals |
| `minitalk.h` | Header file with includes and declarations |
| `libft/` | Custom C library with utility functions |

### Key Functions

| Function | File | Description |
|----------|------|-------------|
| `write_pid` | server.c | Displays the server PID on startup |
| `signal_handler` | server.c | Reconstructs characters from received signals |
| `send_char` | client.c | Sends a character bit by bit using signals |

### Signal Protocol

| Signal | Bit Value | Description |
|--------|-----------|-------------|
| `SIGUSR1` | 0 | Represents a binary 0 |
| `SIGUSR2` | 1 | Represents a binary 1 |

---

## Program Flow

```
🔹 Server
server (main)
 └── write_pid
      └── displays PID using write()
 └── sigaction setup
      └── registers signal_handler for SIGUSR1/SIGUSR2
 └── infinite loop (pause)
      └── waits for signals

signal_handler
 ├── receives signal (SIGUSR1 or SIGUSR2)
 ├── shifts accumulated bits left
 ├── adds new bit (0 or 1)
 ├── increments bit counter
 └── if 8 bits received
      ├── converts to char
      ├── writes char to stdout
      └── resets state

🔹 Client
client (main)
 ├── validates arguments (argc == 3)
 ├── parses server PID (ft_atoi)
 ├── validates PID (> 0)
 └── for each character in message
      └── send_char
           └── for each bit (7 → 0)
                ├── if bit is 1 → kill(pid, SIGUSR2)
                └── if bit is 0 → kill(pid, SIGUSR1)
                └── usleep(100) delay
 └── send_char('\0') to signal end
```

---

## Communication Diagram

```
┌────────────┐                          ┌────────────┐
│   CLIENT   │                          │   SERVER   │
├────────────┤                          ├────────────┤
│            │   SIGUSR1 (bit = 0)      │            │
│  send_char │ ──────────────────────── │  handler   │
│            │   SIGUSR2 (bit = 1)      │            │
│            │ ──────────────────────── │  accumulate│
│            │                          │  bits      │
│            │         × 8 bits         │            │
│            │ ======================== │  = 1 char  │
│            │                          │  → write() │
└────────────┘                          └────────────┘
```

---

## Author

**yel-moha** – 42 Student
