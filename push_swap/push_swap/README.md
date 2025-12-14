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
- Greedy algorithms
- Time and space complexity

### References

- https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
- https://en.wikipedia.org/wiki/Sorting_algorithm

---

## AI Usage Disclosure

Artificial Intelligence tools (such as ChatGPT) were used during the development of this project to clarify project requirements, refactor functions to comply with Norminette constraints, improve code structure, and debug logical issues.

All algorithmic decisions, implementations, and final code validation were performed by the author.

---

## Project Structure

### Source Files

| File | Description |
|------|-------------|
| `main.c` | Program entry point |
| `input_utils.c` | Input parsing (`take_input`, `inputs_array`, `check_input`, `init_stack`) |
| `validation_utils.c` | Input validation (`check_duplicates`, `is_sorted`) |
| `swap_moves.c` | Swap operations (`sa`, `sb`, `ss`) |
| `push_moves.c` | Push operations (`pa`, `pb`) |
| `rotate_moves.c` | Rotate operations (`ra`, `rb`, `rr`) |
| `reverse_rotate.c` | Reverse rotate operations (`rra`, `rrb`, `rrr`) |
| `cycle_sort.c` | Main sorting algorithm (`cycle_sort`, `normalize_stack`) |
| `insert_utils.c` | Insertion helpers (`find_best_index`, `get_cost`, `target_position`) |
| `insert_helpers.c` | Additional helpers (`find_closest_bigger`, `fill_normalized`, `rotate_count`) |
| `find_min_pos.c` | Position utilities (`find_min_pos`, `find_min_pos_index`) |
| `sort_three.c` | Small stack sorting (`sort_three`, `bring_to_top`) |
| `push_swap.h` | Header file with struct definitions and prototypes |

### Data Structures

```c
t_stack  // Main stack structure containing arrays a/b, sizes, and metadata
```

### Operations

| Operation | Description |
|-----------|-------------|
| `sa/sb/ss` | Swap first two elements of stack A/B/both |
| `pa/pb` | Push top element from B to A / A to B |
| `ra/rb/rr` | Rotate stack A/B/both (first becomes last) |
| `rra/rrb/rrr` | Reverse rotate stack A/B/both (last becomes first) |

---

## Program Flow

```
🔹 Entry point
main
 └── take_input
 └── cycle_sort
 └── free_all

🔹 Main sorting flow
cycle_sort
 ├── is_sorted ?
 │    └── (if yes) return
 │
 ├── normalize_stack
 │    └── fill_normalized
 │
 ├── sort_three (if size_a == 3)
 │
 ├── push elements from A to B
 │    └── pb
 │
 ├── while (stack B not empty)
 │    ├── find_best_index
 │    │    ├── target_position
 │    │    │    ├── find_closest_bigger
 │    │    │    └── find_min_pos_index
 │    │    ├── get_cost
 │    │    └── get_cost
 │    │
 │    ├── bring_to_top (A)
 │    │    └── rotate_count
 │    │         └── ra / rra
 │    │
 │    ├── bring_to_top (B)
 │    │    └── rotate_count
 │    │         └── rb / rrb
 │    │
 │    └── pa
 │
 └── final alignment
      ├── find_min_pos
      └── ra / rra
```

---

## Author

**yel-moha** – 42 Student
