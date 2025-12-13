*This project has been created as part of the 42 curriculum by yel-moha.*

# Push_swap

## Description

**push_swap** is a sorting algorithm project developed as part of the 42 curriculum.  
The goal of the project is to sort a stack of integers using a limited set of allowed operations and an auxiliary stack, while minimizing the total number of operations.

The program takes a list of integers as input, stores them in stack **A**, and sorts them in ascending order using stack **B** and predefined operations such as swap, push, rotate, and reverse rotate.

This project focuses on:
- Algorithmic thinking
- Optimization
- Stack manipulation
- Clean and norm-compliant C code

---

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will generate the executable `push_swap`.

### Execution

Run the program with a list of integers as arguments:

```bash
./push_swap 3 2 1
```

The program outputs a sequence of operations (one per line) that sorts the stack.

### Example

```bash
$ ./push_swap 5 1 4 2 3
pb
ra
pb
sa
pa
pa
```

If the input is already sorted or invalid, the program produces no output.

---

## Resources

### Algorithm & Theory

- Stack data structure
- Sorting algorithms
- Radix sort
- Greedy algorithms
- Time and space complexity

### References

- https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
- https://en.wikipedia.org/wiki/Sorting_algorithm
- https://en.wikipedia.org/wiki/Radix_sort

---

## AI Usage Disclosure

Artificial Intelligence tools (such as ChatGPT) were used during the development of this project to clarify project requirements, refactor functions to comply with Norminette constraints, improve code structure, and debug logical issues.

All algorithmic decisions, implementations, and final code validation were performed by the author.

---

## Project Structure

- `main.c` – Program entry point
- `input_utils.c` – Input parsing and validation
- `swap_moves.c`, `push_moves.c`, `rotate_moves.c`, `reverse_rotate.c` – Stack operations
- `cycle_sort.c`, `insert_utils.c` – Sorting logic
- `push_swap.h` – Project header file

---

## Author

**yel-moha** – 42 Student
