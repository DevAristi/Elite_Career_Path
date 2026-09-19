# Python Cheat Sheet for OOP and Algorithms

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

