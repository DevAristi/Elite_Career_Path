# Python Cheat Sheet for Coding Interviews

## Sorting Algorithms and Mechanics

Python implements **Timsort** (an adaptive, stable hybrid of Merge Sort and Insertion Sort) for all built-in sorting routines. Understanding the distinction between mutating in-place sorting and non-destructive sequence duplication is fundamental for writing memory-optimal algorithms and passing Big Tech technical screens.

---

### In-Place Sorting: `list.sort()`

The `.sort()` method mutates the existing contiguous pointer array directly in heap memory and returns `None`. 

* **Time Complexity:** Average and Worst-Case $O(N \log N)$, Best-Case $O(N)$ when data is partially sorted.
* **Auxiliary Space Complexity:** $O(N)$ worst-case auxiliary buffer required by Timsort for merging runs.
* **Side-Effect Constraint:** Attempting to assign `sorted_list = my_list.sort()` binds `sorted_list` to `None`.

```python
# Lexicographical (strings) and Numerical (integers/floats) sorting in-place
def sort_words(words: list[str]) -> list[str]:
    words.sort()  # In-place mutation; returns None
    return words

def sort_numbers(numbers: list[int]) -> list[int]:
    numbers.sort()
    return numbers

def sort_decimals(numbers: list[float]) -> list[float]:
    numbers.sort()
    return numbers

# Lexicographical ordering aligns with Unicode code point values
print(sort_words(["cherry", "apple", "blueberry", "banana"]))
# Output: ['apple', 'banana', 'blueberry', 'cherry']

print(sort_numbers([5, 3, 2, 4, 11, 19, 2]))
# Output: [2, 2, 3, 4, 5, 11, 19]

print(sort_decimals([3.14, 2.82, 6.433, 7.9, 21.554]))
# Output: [2.82, 3.14, 6.433, 7.9, 21.554]
```

---

### Descending Order and Keyword Arguments

The direction of the sort is governed by the boolean keyword-only parameter `reverse`

* `reverse=False` (default): Ascending order.
* `reverse=True`: Inverts comparison operations during run merges to produce descending order.
* **Alternative (`.reverse()`):** `list.reverse()` performs an $O(N)$ in-place pointer swap inversion without running full $O(N \log N)$ sorting logic.

```python
def sort_words_descending(words: list[str]) -> list[str]:
    words.sort(reverse=True)
    return words

def sort_numbers_descending(numbers: list[int]) -> list[int]:
    numbers.sort(reverse=True)
    return numbers

print(sort_words_descending(["cherry", "apple", "banana", "watermelon"]))
# Output: ['watermelon', 'cherry', 'banana', 'apple']

print(sort_numbers_descending([1, 5, 3, 2, 4, 11, 19]))
# Output: [19, 11, 5, 4, 3, 2, 1]
```

---

### Custom Key Functions (Decorate-Sort-Undecorate)

Python utilizes a **key-extraction pattern** via the `key` parameter. The key function is executed **exactly once per element** prior to sorting, caching surrogate keys internally to avoid recomputing values during item comparisons.

* The `key` callable must accept a single argument and return a comparable proxy value.

```python
# Sorting strings by string length instead of lexicographical order
def sort_words_by_length(words: list[str]) -> list[str]:
    # Key function receives each str, evaluates len(), sorts based on returned int
    words.sort(key=len, reverse=True)
    return words

# Sorting numeric elements based on scalar magnitude (absolute value)
def sort_numbers_by_magnitude(numbers: list[int]) -> list[int]:
    numbers.sort(key=abs)
    return numbers

print(sort_words_by_length(["apple", "banana", "kiwi", "watermelon"]))
# Output: ['watermelon', 'banana', 'apple', 'kiwi']

print(sort_numbers_by_magnitude([1, -5, -3, 2, 4, 11, -19, 9]))
# Output: [1, 2, -3, 4, -5, 9, 11, -19]
```

---

### Anonymous Callables: Lambda Expressions

For ad-hoc transformations that do not warrant a formal function definition, pass a `lambda` expression to the `key` parameter.

* **Syntax:** `lambda parameter: expression`
* **Constraint:** Restricted to a single, implicitly returned expression; cannot contain statements (`return`, `pass`, assignments).

```python
# In-line extraction using anonymous functions
def sort_by_length_lambda(words: list[str]) -> list[str]:
    words.sort(key=lambda word: len(word), reverse=True)
    return words

def sort_by_abs_lambda(numbers: list[int]) -> list[int]:
    numbers.sort(key=lambda x: abs(x))
    return numbers

# Sorting composite data structures by specific index/attribute
tuples_list: list[tuple[str, int]] = [("Alice", 25), ("Bob", 19), ("Charlie", 32)]
tuples_list.sort(key=lambda item: item[1])  # Sort by age ascending
print(tuples_list)
# Output: [('Bob', 19), ('Alice', 25), ('Charlie', 32)]
```

---

### Non-Destructive Sorting: `sorted()`

Unlike `list.sort()`, the built-in `sorted()` function creates and returns an entirely **new sorted `list` object**, leaving the original collection unaltered.

* **Polymorphic Scope:** Can consume any arbitrary iterable (including `tuples`, `sets`, `dictionaries`, generators), always outputting a concrete `list`.
* **Complexity:** Time $O(N \log N)$, Space $O(N)$ (allocates buffer for the returned copy).

```python
def sort_words_immutable(words: list[str]) -> list[str]:
    # Preserves original words list; returns a new sorted instance
    return sorted(words)

def sort_numbers_immutable(numbers: list[int]) -> list[int]:
    # Returns a new list sorted by absolute magnitude in descending order
    return sorted(numbers, key=abs, reverse=True)

original_words: list[str] = ["cherry", "apple", "blueberry", "banana"]
new_sorted_words = sort_words_immutable(original_words)

print(original_words)   # Output: ['cherry', 'apple', 'blueberry', 'banana'] (Untouched)
print(new_sorted_words) # Output: ['apple', 'banana', 'blueberry', 'cherry']

original_nums: list[int] = [1, -5, -3, 2, 4, 11, -19]
new_sorted_nums = sort_numbers_immutable(original_nums)
print(new_sorted_nums)  # Output: [-19, 11, -5, 4, -3, 2, 1]
```

---

### Advanced DSA Concept: Stability in Timsort

Timsort is a **stable** sorting algorithm.

* **Definition of Stability:** Elements with identical key values retain their relative insertion order after sorting.
* **Algorithmic Utility (Multi-level Sort):** To sort records by multiple criteria (e.g., primary: `department` ascending, secondary: `salary` descending), sort sequentially from lowest priority key to highest priority key using Python's native sort, or supply a composite tuple as the key extractor:

```python
# Primary: Score descending (-item[1]), Secondary: Name ascending (item[0])
students = [("Bob", 85), ("Alice", 90), ("Charlie", 85), ("David", 90)]
students.sort(key=lambda s: (-s[1], s[0]))
print(students)
# Output: [('Alice', 90), ('David', 90), ('Bob', 85), ('Charlie', 85)]
```

---

## Pythonic Idioms and Sequence Unpacking

Pythonic syntax emphasizes readable, expressive operations that compile into concise bytecode instructions. In coding interviews (DSA) and system design implementations, mastering multi-variable assignment, iterator pairing, lazy evaluation, and scalar clamping reduces cognitive overhead and eliminates off-by-one errors.

---

### Sequence Unpacking (Destructuring Assignment)

Python allows direct destructuring assignment across any iterable interface (`list`, `tuple`, `str`, `set`).

* **Structural Contract:** The number of identifiers on the left side of the `=` operator must match the cardinality of the iterable on the right side.
* **Cardinality Mismatch:** Providing too few or too many targets raises a `ValueError` (`ValueError: too many values to unpack` or `ValueError: not enough values to unpack`).
* **Bytecode Efficiency:** Unpacking translates directly to the `UNPACK_SEQUENCE` bytecode instruction, unpacking elements directly onto the execution stack without individual index lookups.

```python
# Unpacking 2D coordinate pairs
point1: list[int] = [0, 0]
point2: list[int] = [2, 4]

x1, y1 = point1  # x1 = 0, y1 = 0
x2, y2 = point2  # x2 = 2, y2 = 4

slope = (y2 - y1) / (x2 - x1)
print(slope)  # Output: 2.0

# Destructuring lists and tuples into distinct variables
def sum_3_integers(triplet: list[int]) -> int:
    a, b, c = triplet
    return a + b + c

def compute_volume(box_dimensions: tuple[int, int, int]) -> int:
    width, height, depth = box_dimensions
    return width * height * depth

print(sum_3_integers([1, 2, 3]))          # Output: 6
print(compute_volume((3, 2, 1)))          # Output: 6
```

> **Advanced Extended Unpacking (`*` operator):** Use the starred expression (`*rest`) to capture arbitrary middle or trailing elements into a dynamic list:
> ```python
> head, *middle, tail = [1, 2, 3, 4, 5]  # head=1, middle=[2, 3, 4], tail=5
> ```

---

### In-Loop Destructuring

When traversing arrays of structured composite records (e.g., coordinate pairs, graph adjacency lists, or key-value entries), unpack elements directly within the `for` loop declaration.

```python
# Cartesian points traversal
points: list[list[int]] = [[0, 0], [2, 4], [3, 6], [5, 10]]

# Idiomatic: direct stack unpacking per iteration cycle
for x, y in points:
    print(f"x: {x}, y: {y}")

# Finding max score record without redundant indexing
def best_student(scores: list[tuple[str, int]]) -> str:
    best_name: str = ""
    max_score: int = -1
    
    for name, score in scores:
        if score > max_score:
            max_score = score
            best_name = name
            
    return best_name

print(best_student([("Alice", 90), ("Bob", 100), ("Charlie", 70)]))  # Output: Bob
```

---

### Enumeration (`enumerate()`)

Iterating with `range(len(nums))` requires manual array subscript lookups (`nums[i]`) on every cycle. The built-in `enumerate(iterable, start=0)` constructor wraps an iterable in an iterator yielding `(index, item)` tuples on the fly.

* **Complexity:** Runs in **$O(1)$ auxiliary memory** via lazy state generation.
* **Safety:** Completely prevents `IndexError` exceptions while providing self-documenting code.

```python
def get_index_of_seven(nums: list[int]) -> int:
    for i, n in enumerate(nums):
        if n == 7:
            return i
    return -1

def get_dist_between_sevens(nums: list[int]) -> int:
    first_index: int = -1
    for i, n in enumerate(nums):
        if n == 7:
            if first_index == -1:
                first_index = i
            else:
                return i - first_index
    return 0

print(get_index_of_seven([1, 2, 3, 4, 5, 6, 7, 8, 9]))        # Output: 6
print(get_dist_between_sevens([2, 7, 7, 7, 8]))               # Output: 1 (Index 2 - Index 1)
print(get_dist_between_sevens([7, 4, 8, 4, 2, 7]))            # Output: 5 (Index 5 - Index 0)
```

---

### Parallel Sequence Iteration (`zip()`)

The `zip(*iterables)` constructor aggregates elements from multiple sequences into an iterator of tuples.

* **Lazy Evaluation:** Generates paired tuples on demand; instantaneous construction in **$O(1)$ Time and $O(1)$ Space**.
* **Termination Semantic:** By default, `zip()` stops iteration as soon as the **shortest** input iterable is exhausted.
* **Strict Alignment:** In Python 3.10+, `zip(a, b, strict=True)` raises a `ValueError` if the sequences are of unequal lengths, safeguarding against silent data truncation bugs in ingestion pipelines.

```python
names: list[str] = ["Alice", "Bob", "Charlie"]
scores: list[int] = [90, 80, 70]

# Multi-stream traversal
for name, score in zip(names, scores):
    print(f"{name} scored {score}")

# Hash map construction from dual-column sequences in O(N) Time
def group_names_and_scores(names: list[str], scores: list[int]) -> dict[str, int]:
    # Feeds zip iterator directly into the PyDictObject constructor
    return dict(zip(names, scores))

print(group_names_and_scores(["Alice", "Bob"], [90, 80]))  # Output: {'Alice': 90, 'Bob': 80}
```

---

### Chained Comparison Syntactic Sugar

Python converts relational chains (`a < b <= c`) into a single combined boolean expression. 

* **Single Evaluation Protocol:** In `0 < len(names) <= max_length`, the intermediate expression `len(names)` is evaluated **only once** by the virtual machine, optimizing CPU instruction branches and preventing unintended side-effects compared to `0 < len(names) and len(names) <= max_length`.

```python
def is_arr_valid(names: list[str], max_length: int) -> bool:
    # Single-pass chained comparison (0 < length <= max_length)
    return 0 < len(names) <= max_length

print(is_arr_valid(["Alice", "Bob", "Charlie"], 3))  # Output: True
print(is_arr_valid(["Alice", "Bob", "Charlie"], 2))  # Output: False
print(is_arr_valid([], 5))                           # Output: False
```

---

### Value Clamping via Built-in `min()` and `max()`

Branching statements (`if/else`) used solely for scalar bounds clamping can be replaced using standard `min()` and `max()` functions. This pattern avoids branch mispredictions in hot CPU paths and flattens code readability.

* **Lower Bound Clamping (Floor):** `max(lower_bound, val)` guarantees `val` never drops below `lower_bound`.
* **Upper Bound Clamping (Ceiling):** `min(upper_bound, val)` guarantees `val` never exceeds `upper_bound`.
* **Range Clamping (Interval $[A, B]$):** `max(A, min(val, B))` clamps `val` strictly inside the interval.

```python
# Clamping values: eliminate negative transactions
def disallow_negatives(num: int) -> int:
    return max(0, num)

print(disallow_negatives(-2))  # Output: 0
print(disallow_negatives(5))   # Output: 5

# Sliding difference tracker in O(N) Time, O(1) Auxiliary Space
def max_difference(nums: list[int]) -> int:
    max_diff: int = nums[1] - nums[0]
    
    for i in range(1, len(nums)):
        current_diff = nums[i] - nums[i - 1]
        max_diff = max(max_diff, current_diff)  # Constant-time running maximum update
        
    return max_diff

print(max_difference([10, 1, 3, 7]))  # Output: 4 (7 - 3)
print(max_difference([2, 4, 7, 5, 7, 8, 4, 2]))  # Output: 3 (7 - 4 or 8 - 5)
```

---

## Resizable Arrays (Lists in Depth) and Memory Layout

In CPython, a `list` is a **dynamically resized array of contiguous object pointers** (`PyListObject`). It is not a linked list; elements are indexed directly via pointer arithmetic, providing $O(1)$ random access while requiring periodic buffer over-allocation during dynamic expansions.

---

### In-Place Mutation Mechanics and Complexities

| Method | Amortized Time | Worst-Case Time | Auxiliary Space | Operational Mechanism |
| :--- | :---: | :---: | :---: | :--- |
| `append(x)` | $O(1)$ | $O(N)$ | $O(1)$ | Inserts pointer at index `ob_size`; resizes buffer if capacity is reached. |
| `pop()` | $O(1)$ | $O(1)$ | $O(1)$ | Decrements `ob_size` counter; zero pointer movement. |
| `pop(i)` | $O(N)$ | $O(N)$ | $O(1)$ | Removes index $i$; shifts subsequent elements $i+1 \dots N-1$ left. |
| `insert(i, x)` | $O(N)$ | $O(N)$ | $O(1)$ | Shifts elements from $i$ rightward to open a slot; inserts pointer. |
| `extend(iterable)` | $O(M)$ | $O(N + M)$ | $O(1)$ | Iterates and appends elements from secondary collection in place. |
| `remove(x)` | $O(N)$ | $O(N)$| $O(1)$ | Linear scan for first occurrence of $x$, followed by left shift. |
| `index(x)` | $O(N)$ | $O(N)$ | $O(1)$ | Linear scan returning index of first match; raises `ValueError` if absent. |

```python
# 1. In-place extension vs list creation
def append_elements(arr1: list[int], arr2: list[int]) -> list[int]:
    # O(M) time where M = len(arr2); mutates arr1 directly without reallocating
    arr1.extend(arr2)
    return arr1

# 2. Bulk removal: truncating suffix elements safely
def pop_n(arr: list[int], n: int) -> list[int]:
    # Returns empty array if requested drop exceeds current size
    if n >= len(arr):
        return []
    return arr[:-n] if n > 0 else arr

# 3. Arbitrary index insertion with boundary tolerance
def insert_at(arr: list[int], index: int, element: int) -> list[int]:
    # O(N) operation due to pointer shifting; clamp handles out-of-bounds automatically
    arr.insert(index, element)
    return arr

print(append_elements([1, 2, 3], [4, 5, 6]))  # Output: [1, 2, 3, 4, 5, 6]
print(pop_n([1, 2, 3, 4, 5], 2))              # Output: [1, 2, 3]
print(insert_at([1, 2, 3, 4], 2, 6))           # Output: [1, 2, 6, 3, 4]
```

> **Boundary Behavior on `.insert()`:** Calling `arr.insert(len(arr) + 100, val)` does not raise an `IndexError`; CPython clamps the target index, appending the element to the tail. Similarly, negative indices beyond `-len(arr)` prepend to the head (`index 0`).

---

### In-Place Concatenation vs Sequence Addition

* **In-Place Mutation (`arr.extend(other)` or `arr += other`):** Appends elements into the existing array, resizing the buffer only as necessary ($O(M)$ Time, $O(1)$ Auxiliary Space).
* **Concatenation Operator (`arr1 + arr2`):** Allocates a **new `list` object** on the heap, copying pointers from both operands into it ($O(N + M)$ Time, $O(N + M)$ Space).

```python
# Pure functional concatenation without side-effects on input references
def combine_elements(arr1: list[int], arr2: list[int]) -> list[int]:
    # O(N + M) Time and Space; arr1 and arr2 remain unmodified
    return arr1 + arr2

a = [1, 3, 5]
b = [4, 6, 8]
combined = combine_elements(a, b)
print(combined)  # Output: [1, 3, 5, 4, 6, 8]
print(a)         # Output: [1, 3, 5] (Preserved)
```

---

### Pre-Allocation and Multiplication Traps

Pre-allocating lists of a fixed size using scalar multiplication (`[val] * size`) avoids dynamic reallocation overhead during subsequent index writes ($O(N)$ Time).

```python
# Initializing fixed-size buffer: O(N) allocation
def create_list_with_value(size: int, index: int, value: int) -> list[int]:
    buffer = [0] * size  # Allocates contiguous array of zeroes
    buffer[index] = value
    return buffer

print(create_list_with_value(5, 3, 7))  # Output: [0, 0, 0, 7, 0]
```

> **Critical Big Tech Bug: 2D Matrix Multiplication Trap**
> Multiplying a list containing a mutable object duplicates the **reference**, not the underlying object:
> ```python
> # ANTI-PATTERN: All 3 rows point to the exact same list instance in memory
> matrix_bug = [[0] * 3] * 3
> matrix_bug[0][0] = 1
> print(matrix_bug)  # Output: [[1, 0, 0], [1, 0, 0], [1, 0, 0]]
>
> # PRODUCTION PATTERN: List comprehension ensures distinct row allocations
> matrix_correct = [[0] * 3 for _ in range(3)]
> matrix_correct[0][0] = 1
> print(matrix_correct)  # Output: [[1, 0, 0], [0, 0, 0], [0, 0, 0]]
> ```

---

### Cloning and Memory Mutability: Shallow vs Deep Copy

Cloning prevents unwanted side-effects across shared references.

* **Shallow Copy (`arr.copy()`, `arr[:]`, `list(arr)`):** Allocates a new outer array buffer but copies the raw pointer addresses of its elements ($O(N)$ Time). Modifying nested mutable objects affects both copies.
* **Deep Copy (`copy.deepcopy()`):** Recursively traverses and allocates brand-new memory instances for the outer list and every nested object within it ($O(N)$ Time and Memory).

```python
import copy

# Pure removal via shallow copy: isolates caller from mutations
def remove_element_pure(arr: list[int], element: int) -> list[int]:
    cloned_list = arr[:]# Shallow copy via slice syntax
    if element in cloned_list:
        cloned_list.remove(element)
    return cloned_list

source = [1, 3, 5, 7, 9]
result = remove_element_pure(source, 3)
print(source)  # Output: [1, 3, 5, 7, 9] (Original buffer unmutated)
print(result)  # Output: [1, 5, 7, 9]

# Deep copy example for nested collections
nested_source = [[1, 2], [3, 4]]
nested_clone = copy.deepcopy(nested_source)
nested_clone[0][0] = 999
print(nested_source[0][0])  # Output: 1 (Untouched)
```

---

### List Comprehensions: Bytecode Optimization and Filtering

List comprehensions provide optimized syntax for mapping and filtering collections. They compile down to the dedicated `LIST_APPEND` bytecode instruction, executing faster than standard `for` loops appending to a list variable.

$$\text{Syntax: } [\text{expression} \quad \text{for item in iterable} \quad \text{if condition}]$$

```python
# 1. Generating arithmetic progressions
def create_list_of_odds(n: int) -> list[int]:
    # O(N) Time and Space; range(1, n + 1, 2) evaluates step natively
    return [i for i in range(1, n + 1, 2)]

print(create_list_of_odds(10))  # Output: [1, 3, 5, 7, 9]

# 2. Parallel transformation via zip()
arr1 = [1, 2, 3]
arr2 = [4, 5, 6]
sums = [x + y for x, y in zip(arr1, arr2)]
print(sums)  # Output: [5, 7, 9]

# 3. Predicate filtering (Conditional selection)
nums = [1, 2, 3, 4, 5, 6]
evens = [x for x in nums if x % 2 == 0]
print(evens)  # Output: [2, 4, 6]
```

---

## Stacks and Queues

Linear abstract data types (ADTs) govern order-dependent data access.  
Python implements **Stacks** via native dynamic arrays (`list`) using a **LIFO (Last-In, First-Out)** protocol, and **Queues / Double-Ended Queues** via `collections.deque` using a **FIFO (First-In, First-Out)** protocol backed by a doubly linked list of fixed-size contiguous memory blocks.

---

### Stacks (LIFO) via Dynamic Arrays (`list`)

Python does not provide a dedicated stack primitive; standard lists serve this function natively via their tail operations:

* **Push (`list.append(x)`):** Inserts an element at the top of the stack in **$O(1)$ amortized time**.
* **Pop (`list.pop()`):** Removes and returns the top element in strictly **$O(1)$ constant time** (decrements the array length counter with zero pointer shifting).
* **Peek (`stack[-1]`):** Reads the top element via negative index offset in **$O(1)$ constant time**.
* **Empty Check (`not stack` / `len(stack) == 0`):** Evaluates truthiness or internal size in **$O(1)$ time**. Calling `.pop()` on an empty stack raises an `IndexError`.

```python
# Reversing a sequence using an auxiliary LIFO stack frame: O(N) Time, O(N) Space
def reverse_list(arr: list[int]) -> list[int]:
    stack: list[int] = []
    for item in arr:
        stack.append(item)  # Push onto stack

    reversed_arr: list[int] = []
    while stack:  # Idiomatic O(1) truthiness check (replaces while len(stack) > 0)
        reversed_arr.append(stack.pop())  # Pop from top

    return reversed_arr

print(reverse_list([1, 2, 3]))              # Output: [3, 2, 1]
print(reverse_list([3, 2, 1, 4, 6, 2]))     # Output: [2, 6, 4, 1, 2, 3]
print(reverse_list([1, 9, 7, 3, 2, 1, 4]))  # Output: [4, 1, 2, 3, 7, 9, 1]
```

> **Interview Trap:** Never use `list.pop(0)` or `list.insert(0, x)` to implement a Queue or Stack. Removing or inserting at index `0` forces CPython to shift all $N-1$ pointers in memory left or right, turning an $O(1)$ operation into a disastrous **$O(N)$ linear bottleneck**.

---

### Queues (FIFO) via Double-Ended Queue (`collections.deque`)

In CPython, `collections.deque` is implemented as a **doubly linked list of fixed-size chunk blocks** (each block holding 64 object pointers). This design delivers deterministic, allocation-free operations at both boundaries without requiring contiguous reallocation of the entire buffer.

* **Enqueue Right (`deque.append(x)`):** Adds an element to the tail in **$O(1)$ time**.
* **Dequeue Left (`deque.popleft()`):** Removes and returns the head element in **$O(1)$ time** without shifting remaining elements.
* **Boundary Peek (`q[0]` / `q[-1]`):** Inspects the head or tail pointers directly in **$O(1)$ time**.
* **Arbitrary Index Lookup (`q[i]`):** Accessing elements deep inside the middle scales to **$O(N)$ linear time** due to block-chain traversal. For frequent random middle access, default to a standard `list`.

```python
from collections import deque

# Standard FIFO Queue Pipeline
fifo_queue: deque[int] = deque()
fifo_queue.append(10)      # Enqueue right
fifo_queue.append(20)
head = fifo_queue.popleft() # Dequeue left -> returns 10 in O(1)
print(head)                # Output: 10
```

---

### Left-Rotation Cycle via Queue Dequeue/Enqueue

A left cyclic rotation shifts elements toward index `0`, wrapping displaced prefix elements around to the right boundary:

* **Modulo Optimization:** Shifting by $k$ when $k \ge N$ introduces redundant full-cycle loops. Normalizing the shift distance via `k = k % len(q)` guarantees the algorithm never performs more than $N - 1$ operations.

```python
# Left Cyclic Rotation: O(K) Time, O(N) Space
def rotate_left(arr: list[int], k: int) -> deque[int]:
    q: deque[int] = deque(arr)
    if not q:
        return q

    k = k % len(q)  # Clamps redundant full-cycle rotations
    for _ in range
```

---

## Multi-Dimensional Lists and 2D Grids

In Python, multi-dimensional structures are implemented as **arrays of arrays** (nested lists). Unlike contiguous native 2D matrices in C/C++ (`int grid[R][C]`), a Python 2D grid (`list[list[T]]`) is a **primary dynamic pointer array whose elements reference separate, independently allocated heap arrays**.

---

### Memory Layout and Pointer Chaining

Because each row is an independent `PyListObject`, sublists do not need to be contiguous in physical memory, nor are they required to share identical lengths (ragged/jagged arrays).

* **Access Mechanics (`grid[r][c]`):** Performs two sequential pointer dereferences in **$O(1)$ constant time**. First, `grid[r]` resolves the memory address of the target row; second, `[c]` retrieves the object pointer at column index `c`.
* **Jagged Traversal:** Iterating through ragged arrays requires nested loops over the sub-elements directly or bounding inner ranges to `len(row)`.

```python
# Rectangular 3x3 matrix definition
nested_list: list[list[int]] = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

print(nested_list[0])     # Output: [1, 2, 3] (Row 0 pointer dereference)
print(nested_list[1][2])  # Output: 6         (Row 1, Column 2)

# Extracting running maximum per row: O(R * C) Time, O(R) Space
def find_max_in_each_list(nested_arr: list[list[int]]) -> list[int]:
    # List comprehension optimizing bytecode execution
    return [max(sublist) for sublist in nested_arr]

print(find_max_in_each_list([[1, 2], [3, 4, 2]]))                    # Output: [2, 4]
print(find_max_in_each_list([[1, 2, 3], [4, 5, 6], [7, 8, 9]]))      # Output: [3, 6, 9]
print(find_max_in_each_list([[5, 6, 2, 8], [9], [9, 10], [11, 10, 11]])) # Output: [8, 9, 10, 11]
```

---

### Grid Dimensions and In-Bounds Validation

In graph traversal algorithms (BFS, DFS, Matrix DP), keeping coordinates strictly within grid boundaries is an essential invariant to prevent `IndexError` exceptions.

* **Dimension Properties:** For an $R \times C$ matrix, `rows = len(grid)` and `cols = len(grid[0])` (assuming at least one row exists).
* **Chained Relational Boundary Check:** The valid coordinate space satisfies $0 \le r < R$ and $0 \le c < C$. Python evaluates this in single-pass chained syntax.

```python
def in_bounds(grid: list[list[int]], r: int, c: int) -> bool:
    # Early guard against completely empty grids
    if not grid or not grid[0]:
        return False
    
    rows: int = len(grid)
    cols: int = len(grid[0])
    
    # O(1) Time boundary validation via chained operators
```

---

## Hash Maps and Hash Sets for Technical Interviews

Hashing-based data structures provide near-instantaneous search, insertion, and deletion capabilities, forming the core algorithmic optimization engine in technical interviews ($O(1)$ amortized average time vs. $O(N)$ linear scans). In CPython, both `dict` and `set` are implemented using open-addressing hash tables with pseudo-random probing for collision resolution, accompanied by compact arrays to preserve deterministic insertion order.

---

### Hash Map (`dict`): Architecture and Core Primitives

A `dict` associates unique, hashable keys with arbitrary memory references.

* **Insertion & Mutation (`map[k] = v`):** Calculates `hash(k)`, resolves collision buckets, and binds or overrides the value reference in **$O(1)$ amortized time**.
* **Subscript Access (`map[k]`):** Directly dereferences the key pointer in **$O(1)$ time**; raises a `KeyError` if the key is missing.
* **Safe Retrieval (`map.get(k, default)`):** Returns `default` (or `None`) without throwing an exception if the key is absent.
* **Deletion:**
  * `del map[k]`: Removes the slot binding in **$O(1)$ time**; raises `KeyError` if absent.
  * `map.pop(k, default)`: Removes and returns the value in **$O(1)$ time**; returns `default` if the key does not exist, avoiding unhandled errors.
* **Membership Testing (`k in map`):** Evaluates whether a key exists in **$O(1)$ average time** (only inspects keys, never scans values).

```python
# Efficient sequence pairing into hash map: O(N) Time, O(N) Space
def build_hash_map(keys: list[str], values: list[int]) -> dict[str, int]:
    # dict(zip(...)) delegates allocation directly to the CPython C-API
    return dict(zip(keys, values))

# Key-based value extraction preserving input query sequence
def get_values(hash_map: dict[str, int], keys: list[str]) -> list[int]:
    return [hash_map[key] for key in keys]

sample_map = build_hash_map(["Alice", "Bob", "Charlie"], [90, 80, 70])
print(sample_map)  # Output: {'Alice': 90, 'Bob': 80, 'Charlie': 70}
print(get_values(sample_map, ["Charlie", "Alice"]))  # Output: [70, 90]
```

---

### `collections.defaultdict`: Branchless Frequency and Graph Construction

`defaultdict` inherits from `dict` and overrides the `__missing__(key)` dunder method. When accessing an absent key, it invokes the factory callable passed during instantiation (`default_factory`) and inserts the default return value without requiring explicit `if key not in dict:` branches.

* **Numeric Accumulators (`defaultdict(int)`):** Automatically initializes absent keys to `0`.
* **Graph Adjacency Lists (`defaultdict(list)`):** Automatically initializes absent keys to `[]` in $O(1)$ time.

```python
from collections import defaultdict

# Character frequency counter: O(N) Time, O(U) Auxiliary Space (U = unique characters)
def count_chars(s: str) -> dict[str, int]:
    freq: defaultdict[str, int] = defaultdict(int)
    for char in s:
        freq[char] += 1  # Initializes to 0 on first encounter and increments
    return freq

# Directed Graph Adjacency List / Grouped Mapping Construction
def nested_list_to_dict(nums: list[list[int]]) -> dict[int, list[int]]:
    graph: defaultdict[int, list[int]] = defaultdict(list)
    for sublist in nums:
        if sublist:
            key = sublist[0]
            values = sublist[1:]
            graph[key].extend(values)
    return graph

print(count_chars("helloworld"))
# Output: defaultdict(<class 'int'>, {'h': 1, 'e': 1, 'l': 3, 'o': 2, 'w': 1, 'r': 1, 'd': 1})

print(nested_list_to_dict([[1, 2, 3], [4, 5, 6], [1, 4]]))
# Output: defaultdict(<class 'list'>, {1: [2, 3, 4], 4: [5, 6]})
```

---

### `collections.Counter`: Specialized Frequency Multiset

`Counter` is an optimized dictionary subclass engineered specifically for tallying hashable objects.

* **Missing Key Fallback:** Accessing an unregistered key returns `0` instead of raising a `KeyError`.
* **Batch Mutation (`.update()`):** Aggregates counts from another iterable or mapping in $O(M)$ linear time.

```python
from collections import Counter

def count_combined_chars(s1: str, s2: str) -> Counter:
    counter = Counter(s1)  # Tallies s1 in O(len(s1)) Time
    counter.update(s2)     # Merges tallies of s2 in O(len(s2)) Time
    return counter
print(count_combined_chars("hello", "world"))
# Output: Counter({'l': 3, 'o': 2, 'h': 1, 'e': 1, 'w': 1, 'r': 1, 'd': 1})
```

---

### Comprehensions: Dictionaries and Sets

Comprehensions construct collections through optimized bytecode loops (`MAP_ADD` and `SET_ADD`), eliminating method lookup overhead associated with `.append()` or `.add()`.

* **Dict Comprehension:** `{key_expr: val_expr for item in iterable if condition}`
* **Set Comprehension:** `{val_expr for item in iterable if condition}`

```python
# Inverted index lookup (Value -> Array Index) in O(N) Time
def num_to_index(nums: list[int]) -> dict[int, int]:
    return {num: index for index, num in enumerate(nums)}

# Set Comprehension: Deduplication and scalar arithmetic in O(N) Time
def double_unique_nums(nums: list[int]) -> set[int]:
    return {num * 2 for num in nums}

print(num_to_index([10, 20, 30]))        # Output: {10: 0, 20: 1, 30: 2}
print(double_unique_nums([1, 2, 2, 3]))   # Output: {2, 4, 6}
```

---

### Dictionary Views (`dict.items()`)

The `.items()` method provides a dynamic zero-copy view (`dict_items`) yielding `(key, value)` pairs without allocating detached memory buffers.

```python
def get_dict_items(age_dict: dict[str, int]) -> list[tuple[str, int]]:
    # Materializes key-value tuples into a concrete list in O(N) Time
    return list(age_dict.items())

print(get_dict_items({"Alice": 25, "Bob": 30}))
# Output: [('Alice', 25), ('Bob', 30)]
```

---

### Hash Sets (`set`): Mathematical Set Theory

A `set` is a hash table stripped of value references, storing only distinct keys.

* **Insertion (`.add(x)`):** Evaluates `hash(x)` and inserts in **$O(1)$ amortized time**; silently ignores duplicates.
* **Strict Deletion (`.remove(x)`):** Deletes in **$O(1)$ time**; raises `KeyError` if absent.
* **Safe Deletion (`.discard(x)`):** Deletes in **$O(1)$ time**; executes as an idempotent no-op if absent (no exceptions).
* **Membership (`x in set`):** Constant **$O(1)$ average time** lookup.

```python
def build_hash_set(keys: list[str]) -> set[str]:
    return set(keys)

def check_keys(hash_set: set[str], keys: list[str]) -> list[bool]:
    return [key in hash_set for key in keys]

s = build_hash_set(["a", "b", "c"])
print(check_keys(s, ["a", "z", "b"]))  # Output: [True, False, True]
```

---

### Hashable Composite Keys: Tuples as Keys

Hash table structures require all keys to be **hashable and immutable**. Mutable collections like `list` cannot serve as dictionary keys or set elements because their memory contents can shift, which would invalidate their computed hash slot (`TypeError: unhashable type: 'list'`).

* **Tuples as Composite Keys:** Tuples containing only immutable elements are hashable. They provide the standard mechanism to represent composite states (such as 2D matrix coordinates `(row, col)`, graph edges `(u, v)`, or memoization states in Dynamic Programming) without defining custom classes.

```python
# Using tuples to index 2D coordinates in sparse matrices / memoization tables
dict_of_pairs: dict[tuple[int, int], int] = {}
dict_of_pairs[(0, 0)] = 1
dict_of_pairs[(0, 1)] = 2
print(dict_of_pairs)  # Output: {(0, 0): 1, (0, 1): 2}

# Storing unique visited coordinate pairs in BFS/DFS grid traversals
set_of_pairs: set[tuple[int, int]] = set()
set_of_pairs.add((0, 0))
set_of_pairs.add((0, 1))
print(set_of_pairs)   # Output: {(0, 0), (0, 1)}

# Grid Coordinate Extraction Pattern: O(R * C) Time, O(K) Space (K = number of target cells)
def grid_to_set(grid: list[list[int]]) -> set[tuple[int, int]]:
    result_set: set[tuple[int, int]] = set()
    for r in range(len(grid)):
        for c in range(len(grid[r])):
            if grid[r][c] == 1:
                result_set.add((r, c))  # Inserts immutable coordinate pair
    return result_set

sample_grid = [
    [1, 0, 1],
    [0, 1, 0],
    [1, 0, 1]
]

print(grid_to_set(sample_grid))
# Output: {(0, 0), (0, 2), (1, 1), (2, 0), (2, 2)}
```

---

### Complexity Matrix: Hash Table Collections vs. Arrays

| Operation | `dict` (Hash Map) | `set` (Hash Set) | `list` (Dynamic Array) |
| :--- | :---: | :---: | :---: |
| **Search / Membership (`in`)** | $O(1)$ amortized | $O(1)$ amortized | $O(N)$ (Linear scan) |
| **Insertion** | $O(1)$ amortized | $O(1)$ amortized | $O(1)$ amortized (`.append`) |
| **Key/Index Deletion** | $O(1)$ amortized | $O(1)$ amortized | $O(N)$ (Pointer shifting) |
| **Key Hashability Requirement** | Strict (`__hash__` & `__eq__`) | Strict (`__hash__` & `__eq__`) | None (Stores arbitrary pointers) |
| **Memory Layout** | Compact index array + dense entries | Sparse hash bucket array | Contiguous 64-bit pointer array |

---

## Heaps and Priority Queues (`heapq`)

A **Priority Queue** is an abstract data type where each element has an associated priority, and elements are served based on priority rather than arrival order. In Python, priority queues are implemented using the `heapq` module, which provides binary heap algorithms built directly on top of standard dynamic arrays (`list`)

---

### Min-Heap Invariant and Array Representation

By default, Python's `heapq` strictly implements a **Min-Heap**.

* **Min-Heap Property:** The key stored in any parent node is less than or equal to the keys stored in its children ($A[\text{parent}] \le A[\text{child}]$).
* **Array Index Mapping:** For any element at index $i$ (0-indexed):
  * Left Child: $2i + 1$
  * Right Child: $2i + 2$
  * Parent Node: $\lfloor (i - 1) / 2 \rfloor$
* **Root Minimum:** The smallest element is always maintained at `heap[0]`, providing **$O(1)$ constant time** access without removal.

---

### Core Operations: Push and Pop

| Operation | Function | Time Complexity | Auxiliary Space | Internal Mechanism |
| :--- | :--- | :---: | :---: | :--- |
| **Peek Minimum** | `heap[0]` | $O(1)$ | $O(1)$ | Direct array index dereference. |
| **Push** | `heapq.heappush(heap, val)` | $O(\log N)$ | $O(1)$ | Appends element to tail; performs up-heap sift (*siftdown*). |
| **Pop** | `heapq.heappop(heap)` | $O(\log N)$ | $O(1)$ | Swaps root with tail, pops tail; sifts new root down (*siftup*). |
| **Push-Pop** | `heapq.heappushpop(heap, val)` | $O(\log N)$ | $O(1)$ | Pushes then pops; faster than separate calls because sift executes once. |

```python
import heapq

def heap_push_inspect(heap: list[int], value: int) -> int:
    heapq.heappush(heap, value)  # Maintains min-heap invariant in O(log N)
    return heap[0]               # Returns current minimum in O(1)

h = [1, 2, 3]
heapq.heapify(h)
print(heap_push_inspect(h, 4))  # Output: 1
print(heap_push_inspect(h, 0))  # Output: 0
```

```python
# Popping elements in priority order (Min-Heap Drainage Pattern)
def heap_drain(heap: list[int]) -> list[int]:
    res: list[int] = []
    while heap:  # O(1) truthiness check (stops when empty)
        res.append(heapq.heappop(heap))  # Extracts minimum element in O(log N)
    return res

h_sample = [1, 2, 3]
heapq.heapify(h_sample)
print(heap_drain(h_sample))  # Output: [1, 2, 3]
```

> **Empty Heap Boundary Error:** Executing `heapq.heappop(empty_heap)` on an empty list raises an `IndexError: index out of range`. Always ensure the heap is non-empty before popping.

---

### In-Place Transformation: `heapify()` vs. Incremental Pushes

Converting an arbitrary list of $N$ elements into a valid min-heap can be done via `heapq.heapify(nums)`.

* **Complexity Difference:** 
  * Inserting $N$ elements one by one via `heappush()` runs in $O(N \log N)$ time.
  * `heapq.heapify()` operates from the lowest internal nodes upward using Floyd's algorithm, completing in **$O(N)$ linear time** and **$O(1)$ auxiliary space** in-place.

```python
# In-place Heap Sort using linear heapify: O(N log N) Time, O(N) Space
def heap_sort(nums: list[int]) -> list[int]:
    heapq.heapify(nums)  # In-place conversion in strictly O(N) Time
    sorted_list: list[int] = []
    while nums:
        sorted_list.append(heapq.heappop(nums))  # N extractions at O(log N) each
    return sorted_list

print(heap_sort([3, 4, 5, 1, 2, 6]))
# Output: [1, 2, 3, 4, 5, 6]
```

---

### Simulating a Max-Heap (Negation Inversion)

Python does not expose an explicit `max_heap` class. To implement a Max-Heap using `heapq`, multiply all numerical values by `-1` prior to insertion, and negate them again upon extraction:

$$\forall a, b \in \mathbb{R}: \quad a > b \iff -a < -b$$

```python
# Descending order extraction via Max-Heap simulation: O(N log N) Time, O(N) Space
def get_reverse_sorted(nums: list[int]) -> list[int]:
    max_heap: list[int] = []
    for num in nums:
        heapq.heappush(max_heap, -num)  # Inverts sign to place largest values at root
    
    result: list[int] = []
    while max_heap:
        result.append(-heapq.heappop(max_heap))  # Restores original positive sign
        
    return result

print(get_reverse_sorted([5, 6, 4, 2, 7, 3, 1]))
# Output: [7, 6, 5, 4, 3, 2, 1]
```

---

### Custom Heap Priorities via Tuple Ordering

When storing complex payloads or defining non-standard priority metrics, store elements as tuples: `(priority_key, payload)`. Python compares tuples lexicographically from index `0` upward; if index `0` ties, it evaluates index `1`.

* **Absolute Value Sorting:** To prioritize elements by magnitude while preserving access to the original value, push `(abs(val), val)`.
* **Max-Heap with Metadata:** Store `(-priority, unique_id, task_data)` to break priority ties cleanly without triggering uncomparable object errors.

```python
# Custom priority queue using tuple keys
def custom_priority_sort(nums: list[int]) -> list[int]:
    heap: list[tuple[int, int]] = []
    for num in nums:
        # Tuple format: (-num, num) sets highest number as lowest value for min-heap root
        heapq.heappush(heap, (-num, num))
        
    res: list[int] = []
    while heap:
        priority, original_num = heapq.heappop(heap)
        res.append(original_num)
        
    return res
```

---

## Sorted Containers (`SortedDict` and `SortedSet`)

Standard Python dictionaries preserve insertion order, but they do **not** keep keys sorted by their natural comparable values (`<`, `>`). Similarly, standard `set` instances are unordered hash tables. 

In competitive programming and technical interviews (e.g., LeetCode sliding window, dynamic order-statistic queries, range lookups), the third-party library `sortedcontainers` provides `SortedDict` and `SortedSet`. Unlike traditional Red-Black or AVL balanced Binary Search Trees ($O(\log N)$ tree traversals with pointer chasing and high memory overhead), `sortedcontainers` uses **B-tree-inspired segmented lists of contiguous arrays**, maximizing CPU L1/L2/L3 cache locality and outperforming pure tree implementations in Python runtime execution.

---

### Sorted Dictionary (`SortedDict`)

A `SortedDict` combines a hash table with a sorted key sequence, keeping keys ordered at all times while mapping them to values. Duplicate keys are disallowed (updating an existing key updates its value in place).

#### Complexity Blueprint
* **Key Insertion:** $O(\log N)$ via binary search + bounded array shift.
* **Key Lookup (`dict[k]` / `k in dict`):** $O(\log N)$.
* **Key Deletion (`pop(k)` / `del dict[k]`):** $O(\log N)$.
* **Index-Based Operations (`popitem(index)`):** $O(\log N)$.
* **Ordered Iteration:** $O(N)$ linear traversal across sorted keys.

```python
from sortedcontainers import SortedDict

# Instantiation and Automatic Key Sorting
sd: SortedDict[str, int] = SortedDict()
sd["c"] = 90
sd["b"] = 80
sd["a"] = 70

print(sd)  # Output: SortedDict({'a': 70, 'b': 80, 'c': 90}) (Sorted alphabetically)

# Subscript access: O(log N) lookup
print(sd["b"])  # Output: 80

# Positional removal using popitem(index)
last_pair = sd.popitem(-1)   # Removes and returns largest key pair in O(log N): ('c', 90)
first_pair = sd.popitem(0)   # Removes and returns smallest key pair in O(log N): ('a', 70)
print(last_pair)             # Output: ('c', 90)
print(first_pair)            # Output: ('a', 70)
```

#### Selective Deletion and Range Extraction
```python
# Batch key deletion in O(K log N) Time
def remove_keys(sorted_dict: SortedDict[str, int], keys: list[str]) -> SortedDict[str, int]:
    for key in keys:
        # pop(key, default) avoids throwing KeyError if key is missing
        sorted_dict.pop(key, None)
    return sorted_dict

# Linear scan over ordered keys up to a target boundary: O(K) Time
def get_values_before_target(sorted_dict: SortedDict[str, int], target: str) -> list[int]:
    values: list[int] = []
        if key == target:
            break
        values.append(value)
    return values

records = SortedDict({"Alice": 25, "Bob": 30, "Charlie": 35, "David": 40})
print(get_values_before_target(records, "Charlie"))  # Output: [25, 30]
print(remove_keys(records, ["Bob", "David"]))        # Output: SortedDict({'Alice': 25, 'Charlie': 35})
```

---

### Sorted Set (`SortedSet`)

A `SortedSet` maintains a collection of unique, hashable elements sorted continuously in ascending order. It combines the set uniqueness invariant with indexable, bisect-ready sequence storage.

#### Complexity Blueprint
* **Add (`add(x)`):** $O(\log N)$ binary search insertion; duplicate elements are ignored.
* **Strict Removal (`remove(x)`):** $O(\log N)$; raises `KeyError` if absent.
* **Safe Removal (`discard(x)`):** $O(\log N)$; acts as a no-op if element is absent (no exception).
* **Positional Pop (`pop(index)`):** $O(\log N)$ to pop extreme or arbitrary index elements (e.g., `pop(0)` for min, `pop(-1)` for max).
* **Clear (`clear()`):** $O(N)$ memory deallocation.
* **Membership (`x in s`):** $O(\log N)$ logarithmic verification.

```python
from sortedcontainers import SortedSet

# Instantiation with automatic deduplication and sorting: O(N log N)
s_set: SortedSet[int] = SortedSet([90, 80, 85, 95])
print(s_set)  # Output: SortedSet([80, 85, 90, 95])

# Insertion and safe discarding
s_set.add(82)        # Inserts into correct sorted position: [80, 82, 85, 90, 95]
s_set.discard(100)   # Safely ignores missing element without throwing KeyError

# Boundary pops
min_val = s_set.pop(0)   # O(log N) extraction of smallest element -> 80
max_val = s_set.pop(-1)  # O(log N) extraction of largest element -> 95
print(min_val, max_val)  # Output: 80 95
print(s_set)             # Output: SortedSet([82, 85, 90])
```

#### Mutation and Slicing Pattern
Unlike standard hash sets, a `SortedSet` supports random access indexing and sub-range slicing directly via `set[start:end]` in $O(K)$ time:

```python
def get_first_three(sorted_set: SortedSet[int], nums1: list[int], nums2: list[int]) -> list[int]:
    # Bulk addition: O(len(nums1) * log N)
    for num in nums1:
        sorted_set.add(num)
        
    # Bulk safe removal: O(len(nums2) * log N)
    for num in nums2:
        sorted_set.discard(num)
        
    # Returns the smallest 3 elements in ascending order via slice syntax
    return list(sorted_set[:3])

test_set = SortedSet([1, 4, 7, 2, 8, 9])
print(get_first_three(test_set, [], [10]))              # Output: [1, 2, 4]
print(get_first_three(SortedSet(), [1, 2, 3], [4]))      # Output: [1, 2, 3]
```

---

### Data Structure Comparison: Interview Architectural Trade-Offs

| Capability / Metric | `dict` / `set` (Built-in) | `heapq` (Min-Heap) | `SortedDict` / `SortedSet` |
| :--- | :---: | :---: | :---: |
| **Underlying Memory Architecture** | Hash Table (Sparse + Dense arrays) | Complete Binary Tree inside continuous array | B-Tree style segmented list of arrays |
| **Lookup (`x in collection`)** | $O(1)$ amortized | $O(N)$ (Requires linear scan) | $O(\log N)$ |
| **Insert** | $O(1)$ amortized | $O(\log N)$ | $O(\log N)$ |
| **Delete Arbitrary Element** | $O(1)$ amortized | $O(N)$ search + $O(\log N)$ sift | $O(\log N)$ |
| **Find Minimum / Maximum** | $O(N)$ scan (Unordered) | $O(1)$ for Min, $O(N)$ for Max | $O(1)$ (`[0]` for Min, `[-1]` for Max) |
| **Extract Min / Extract Max** | $O(N)$ | $O(\log N)$ for Min, $O(N)$ for Max | $O(\log N)$ for both ends (`pop(0)`, `pop(-1)`) |
| **Range Slicing / Bisection** | Unsupported | Unsupported | Supported (`bisect_left`, `bisect_right`, slices) |