*This project has been created as part of the 42 curriculum by yel-moha.*

# Philosophers

## Description

**Philosophers** is a threads project developed as part of the 42 curriculum that implements the classic dining philosophers problem.

The program simulates n philosophers sitting at a round table, each with a fork on either side. Each philosopher must acquire both forks to eat. The goal is to prevent deadlocks and starvation using proper thread synchronization.

The program takes the following arguments:
- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time (in milliseconds) a philosopher can survive without eating
- `time_to_eat`: Time (in milliseconds) it takes for a philosopher to eat
- `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping
- `[number_of_times_each_philosopher_must_eat]`: Optional - stop after each philosopher has eaten this many times

This project focuses on:
- Thread management and synchronization
- Mutex locks and avoiding deadlocks
- Race condition prevention
- Clean and norm-compliant C code

---

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will generate the executable `philo`.

### Execution

Run the program with the required arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

Example:
```bash
./philo 5 800 200 200
```

For each philosopher, the program outputs:
- When they take a fork
- When they start eating
- When they start sleeping
- When they are thinking

Example output:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

---

## Resources

### Theory

- Dining Philosophers Problem
- Thread synchronization
- Mutex locks and condition variables
- Deadlock prevention strategies

### References

- https://en.wikipedia.org/wiki/Dining_philosophers_problem
- POSIX Threads (pthreads) documentation

---

## AI Usage Disclosure

Artificial Intelligence tools (such as ChatGPT) were used during the development of this project to clarify project requirements, debug logical issues, and improve code structure.

All algorithmic decisions, implementations, and final code validation were performed by the author.

---

## Project Structure

### Source Files

| File | Description |
|------|-------------|
| `philo.h` | Header file with struct definitions and function prototypes |
| `threads.c` | Thread initialization and creation |
| `threads_helpers.c` | Helper functions for thread management |
| `routine.c` | Main philosopher routine (eat, sleep, think) |
| `routine_helpers.c` | Helper functions for philosopher actions |
| `parse_and_simulate.c` | Argument parsing and simulation setup |
| `print.c` | Output formatting and logging |
| `time.c` | Time-related utilities and tracking |
| `utils.c` | General utility functions |

### Key Features

- **Thread Safety**: Uses mutexes to protect shared resources (forks)
- **Race Condition Prevention**: Implements proper synchronization mechanisms (see RACE_CONDITIONS_SOLVED.md)
- **Deadlock Avoidance**: Philosophers acquire forks in a consistent order
- **Time Tracking**: Accurate millisecond-level timing using system calls

## Author

**yel-moha** – 42 Student
