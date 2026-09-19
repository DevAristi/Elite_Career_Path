# Python Cheat Sheet for Beginners

## Comments

Use `#` for single-line comments.

Shortcut in most code editors (VS Code):
* **Windows / Linux:** `Ctrl + /`
* **macOS:** `Cmd + /`

---

## Variables and Assignment

In Python, a variable is not a memory container; it is a **name reference (pointer)** bound to an object in memory.

```python
message = "this string is stored in a variable"
print(message)
```

---

### Reassignment and Dynamic Typing
Python is dynamically and strongly typed. You do not declare types explicitly, and a variable can reference different data types over its lifecycle:

```python
x = 10         # bound to an int object
x = "Hello"    # rebound to a str object
x = [1, 2, 3]  # rebound to a list object
```

> **Contrast with Static Typing (e.g., Java / C++):** Variable types are bound at compile-time and cannot reference a different type.

---

### Multiple Assignment and Unpacking
Assign multiple variables in a single line using comma separation:

```python
msg1, msg2 = "Hello", "World"
```

---

### Core Data Types

```python
age = 25             # int (arbitrary precision integer)
temperature = 98.6   # float (double-precision 64-bit IEEE 754)
is_active = True     # bool (True / False, subclass of int)
name = "Alice"       # str (immutable Unicode sequence)
items = [1, 2, 3]    # list (mutable dynamic array)
```

To inspect an object's type at runtime, use `type()`:

```python
print(type(10))  # Output: <class 'int'>
```

---

### Explicit Type Casting

Convert objects explicitly using built-in constructors. Note that `int()` on a float truncates decimals towards zero without rounding:

```python
raw_value = 10.9
parsed_value = int(raw_value)

print(parsed_value)  # Output: 10
```

Strings containing non-numeric characters cannot be cast to numeric types and will raise a `ValueError`:

```python
int("hello")  # Raises ValueError: invalid literal for int() with base 10: 'hello'
```

---

### The `None` Object

Python does not support uninitialized variable declarations (e.g., `int x;`). To explicitly denote the absence of a value, bind the variable to the singleton object `None` (`NoneType`):

```python
val = None
```

---

## Math and Arithmetic Operators

Python supports standard arithmetic operations. True division (`/`) always returns a `float`, even if the quotient is a whole number.

```python
x, y = 3, 6

print(x + y)  # Output: 9   (Addition)
print(x - y)  # Output: -3  (Subtraction)
print(x * y)  # Output: 18  (Multiplication)
print(x / y)  # Output: 0.5 (Floating-point Division)
```

---

### Order of Operations (Precedence)
Python follows standard operator precedence (**PEMDAS**):  
1. Parentheses `()`
2. Exponents `**`
3. Multiplication `*`, Division `/`, Floor Division `//`, Modulus `%` (Left-to-Right)
4. Addition `+`, Subtraction `-` (Left-to-Right)

```python
result = 2 + 3 * 4    # 14 (Multiplication first)
result = (2 + 3) * 4  # 20 (Parentheses override precedence)
```

---

### Extended Arithmetic Operators

```python
x, y = 7, 2

# Floor Division (//): Mathematical floor division (rounds towards negative infinity)
print(x // y)   # Output: 3
print(-x // y)  # Output: -4 (Unlike C++/Java integer division, which truncates towards zero to -3)

# Modulus (%): Returns the remainder of division
print(x % y)    # Output: 1

# Exponentiation (**): Raises base to the power of exponent
print(x ** y)   # Output: 49 (7^2)
```

---

### In-Place (Shorthand) Assignment Operators

Shorthand operators allow modifying an existing bound value concisely:

```python
count = 0

count += 5   # count = count + 5
count -= 2   # count = count - 2
count *= 3   # count = count * 3
count /= 2   # count = count / 2
count //= 2  # count = count // 2
count %= 3   # count = count % 3
count **= 2  # count = count ** 2
```

---

## Logical Operators (Boolean Algebra)

Unlike languages where logical operators strictly return a boolean type (`true`/`false`), Python's `and` and `or` operators use **short-circuit evaluation** and return the **actual operand object** that determined the outcome, not necessarily a `bool`.

In Python, all objects have an inherent truth value:
* **Falsy values:** `None`, `False`, `0`, `0.0`, `""`, `[]`, `()`, `{}`, `set()`
* **Truthy values:** Any non-zero number, non-empty sequence, or valid object reference

### 1. Logical `or`
Returns `True` if **at least one** operand evaluates to `True`.

| A | B | A or B |
| :---: | :---: | :---: |
| `False` | `False` | `False` |
| `True` | `False` | `True` |
| `False` | `True` | `True` |
| `True` | `True` | `True` |

```python
a, b, c = False, False, True
print(a or b)       # Output: False
print(a or b or c)  # Output: True
```

---

### 2. Logical `and`
Returns `True` **only if all** operands evaluate to `True`.

| A | B | A and B |
| :---: | :---: | :---: |
| `False` | `False` | `False` |
| `True` | `False` | `False` |
| `False` | `True` | `False` |
| `True` | `True` | `True` |

```python
a, b, c = True, True, False
print(a and b)       # Output: True
print(a and b and c) # Output: False
```

---

### 3. Logical `not`
Inverts the Boolean value of the operand.

```python
is_active = True

print(not is_active)        # Output: False
print(not (False and True)) # Output: True (Evaluates inside parentheses first)
``` 

---

## Functions

Functions encapsulate reusable logic under a single identifier to prevent code duplication. Defined using the `def` keyword followed by the identifier, parentheses, and a colon. Code blocks require consistent indentation (PEP 8: 4 spaces).

```python
def greet():
    print("Hello, World!")

def say_goodbye():
    print("Goodbye, World!")

greet()        # Output: Hello, World!
say_goodbye()  # Output: Goodbye, World!
```

---

### Function Declaration and Execution Order

Python executes sequentially top-to-bottom. Functions must be declared in memory before they are invoked; calling prior to definition raises a `NameError`. Re-declaring a function overwrites the previous reference in the current namespace.

```python
# Calling print_number() here raises NameError: name 'print_number' is not defined

def print_number():
    print(10)

print_number()  # Output: 10

def print_number():
    print(20)

print_number()  # Output: 20
```

---

### Parameters and Arguments

* **Parameter:** Variable defined within the function signature.
* **Argument:** Concrete value or reference passed into the function call.

```python
def farewell(name):
    msg = "Goodbye, " + name
    print(msg)

farewell("Bob")       # Output: Goodbye, Bob
farewell("Charlie")   # Output: Goodbye, Charlie
farewell("NeetCode")  # Output: Goodbye, NeetCode
```

---

### Multiple Parameters

Separate multiple parameters and arguments using commas. Arguments are mapped positionally from left to right.

```python
def two_sum(a, b):
    frst_sum = a + b
    print(frst_sum)

def three_sum(x, y, z):
    scnd_sum = x + y + z
    print(scnd_sum)

two_sum(7, 10)       # Output: 17
three_sum(3, 5, 8)   # Output: 16
```

---

### The `return` Statement

Terminates function execution and sends the evaluated object back to the caller frame. Functions without an explicit `return` statement evaluate to `None`.

```python
def product(a, b):
    return a * b

print(product(2, 4))  # Output: 8
print(product(8, 2))  # Output: 16
print(product(4, 8))  # Output: 32
print(product(8, 8))  # Output: 64
```

---

### Type Hints (PEP 484)

Document expected input and output data types using `:` and `->`. Type hints are metadata for static analyzers (e.g., `mypy`) and IDEs; they are not enforced at runtime.

```python
def add(x: int, y: int) -> int:
    return x + y

def greet(name: str) -> None:
    print("Hello, " + name)

lala = greet("NeetCode")  # Output: Hello, NeetCode
print(type(lala))         # Output: <class 'NoneType'>
```

---

### Variable Scope and Namespaces

Scope determines the visibility and lifetime of a variable within a program:

* **Global Scope:** Variables defined outside of any function block. Accessible module-wide.
* **Local Scope:** Variables created within a function (including parameters). Created upon function invocation and destroyed upon exit. Attempting to reference them outside raises a `NameError`.

```python
# Demonstrating Local Scope isolation
def declare_variable() -> None:
    inside_function_only = 10
    return

declare_variable()
# print(inside_function_only)  # Raises NameError: name 'inside_function_only' is not defined

# Demonstrating Global Scope access
n = 10

def print_global_variable() -> None:
    print(n)

print_global_variable()  # Output: 10
```

#### Variable Shadowing and Scoping Precedence
When an identifier inside a local scope matches an identifier in the global scope, the local variable **shadows** the global one within that execution frame:

```python
n = 100

def print_local_variable(num: int) -> None:
    print(num)  # Uses local parameter value
    return

print_local_variable(n)  # Output: 100
print(n)                 # Output: 100 (Global variable untouched)
```

---

### Default Arguments

Parameters can define default fallback values assigned via the `=` operator in the function signature. If the caller omits that argument, the default is evaluated instead.

```python
def greet(name: str = "World") -> None:
    print("Hello, " + name + "!")

greet()        # Output: Hello, World!
greet("Bob")   # Output: Hello, Bob!
```

#### Parameter Order Rules (Syntactic Constraint)
Positional parameters without default values cannot follow parameters with default values (`SyntaxError: non-default argument follows default argument`).

```python
# Valid declarations
def greet_full(greeting: str = "Hello", name: str = "World") -> None:
    print(greeting + ", " + name + "!")

def greet_partial(name: str, punctuation: str = "!") -> None:
    print("Hello, " + name + punctuation)

greet_partial("World", "!")  # Output: Hello, World!
greet_partial("World")       # Output: Hello, World!

# Invalid declaration:
# def greet_invalid(greeting: str = "Hello", name: str) -> None:
```

#### Important Caveat: Mutable Default Arguments
Default arguments are evaluated once at function definition time, not dynamically on each invocation. Never bind mutable collections (`list`, `dict`, `set`) as default values, as subsequent calls mutate the shared instance:

```python
# Anti-pattern: shared state across calls
def append_bug(item: int, target: list = []) -> list:
    target.append(item)
    return target

# Idiomatic pattern: use None as a sentinel and instantiate defensively
def append_correct(item: int, target: list | None = None) -> list:
    if target is None:
        target = []
    target.append(item)
    return target
```

---

## Conditional Statements

Conditional control flow allows executing specific branches of code depending on whether expressions evaluate to boolean `True` or `False`.

---

### Comparison Operators

Comparison operators evaluate relational expressions between operands and strictly return a `bool` (`True` or `False`). Single `=` is reserved for variable assignment, while `==` tests for equality.

| Operator | Meaning |
| :---: | :--- |
| `==` | Equal to |
| `!=` | Not equal to |
| `<`  | Strictly less than |
| `>`  | Strictly greater than |
| `<=` | Less than or equal to |
| `>=` | Greater than or equal to |

```python
def check_equal(x: int, y: int) -> bool:
    return x == y

def check_not_equal(x: int, y: int) -> bool:
    return x != y

def check_less_than(x: int, y: int) -> bool:
    return x < y

def check_greater_than(x: int, y: int) -> bool:
    return x > y

def check_less_than_or_equal(x: int, y: int) -> bool:
    return x <= y

def check_greater_than_or_equal(x: int, y: int) -> bool:
    return x >= y

print(check_equal(2, 2))                   # Output: True
print(check_not_equal(-2, 2))              # Output: True
print(check_less_than(2, 3))               # Output: True
print(check_greater_than(3, 2))            # Output: True
print(check_less_than_or_equal(3, 3))      # Output: True
print(check_greater_than_or_equal(3, 3))   # Output: True
```

---

### If Statements

The `if` block executes its indented body only when its predicate expression evaluates to `True`. If the condition evaluates to `False`, the block is bypassed entirely.

```python
def is_balance_low(balance: int) -> None:
    if balance <= 100:
        print("Warning: Low balance.")

is_balance_low(99)   # Output: Warning: Low balance.
is_balance_low(100)  # Output: Warning: Low balance.
is_balance_low(101)  # No output (condition evaluates to False)
```

---

### Conditional Scope Behavior

Unlike functions, `if` statements **do not create a new local scope**. Variables declared or modified inside an `if` block persist in the surrounding execution scope.

```python
if True:
    message = "Hello"

print(message)  # Accessible outside the if statement: Output: "Hello"

# Variables defined inside functions remain local to that function,
# even if declared within an if block inside it.
def check_scoped_balance(balance: int) -> None:
    if balance <= 100:
        warning_msg = "Warning: Low balance."
        print(warning_msg)

check_scoped_balance(50)
# print(warning_msg)  # Raises NameError: name 'warning_msg' is not defined
```

---

### If-Else Statements

Provides a fallback execution path via `else:`. Exactly one branch executes depending on the condition.

```python
def pay_bill(balance: int, bill: int) -> int:
    if balance >= bill:
        return balance - bill
    else:
        return balance

print(pay_bill(100, 50))   # Output: 50
print(pay_bill(100, 100))  # Output: 0
print(pay_bill(100, 150))  # Output: 100

def get_min(a: int, b: int) -> int:
    if a < b:
        return a
    else:
        return b

print(get_min(10, 11))  # Output: 10
print(get_min(5, -7))   # Output: -7
print(get_min(20, 20))  # Output: 20
```

---

### Else-If Statements (`elif`)

Chains multiple mutually exclusive predicates from top to bottom. Once any branch matches, its body executes and the remainder of the ladder is skipped. The optional trailing `else` acts as the default catch-all. Supports chained relational comparisons (`0 < num < 10`):

```python
def check_range(num: int) -> str:
    if num < 0:
        return "negative"
    elif num == 0:
        return "zero"
    elif 0 < num < 10:  # Idiomatic chained comparison (equivalent to num > 0 and num < 10)
        return "positive single digit"
    else:
        return "positive multi digit"

print(check_range(-10))   # Output: negative
print(check_range(0))     # Output: zero
print(check_range(9))     # Output: positive single digit
print(check_range(1000))  # Output: positive multi digit
```

---

### Compound Logical Conditions

Combine multiple conditions inside a single branch using short-circuit boolean operators (`and`, `or`, `not`). Return boolean expressions directly rather than wrapping them in redundant `if/else` returns:

```python
def discount_applies(age: int) -> bool:
    return age < 18 or age >= 65

print(discount_applies(17))  # Output: True
print(discount_applies(18))  # Output: False
print(discount_applies(40))  # Output: False
print(discount_applies(65))  # Output: True
print(discount_applies(70))  # Output: True
```

---

### Truthy and Falsy Evaluation

Python evaluates non-boolean objects directly inside boolean contexts without requiring explicit comparison operators:

* **Falsy Values:** `False`, `None`, `0`, `0.0`, `""` (empty string), `[]` (empty list), `()`, `{}`, `set()`
* **Truthy Values:** Non-zero numbers, non-empty collections, and valid instance references

```python
from typing import Any

def is_truthy(value: Any) -> str:
    return "Truthy" if value else "Falsy"

print(is_truthy(0))          # Output: Falsy
print(is_truthy(10))         # Output: Truthy
print(is_truthy(0.0))        # Output: Falsy
print(is_truthy(10.0))       # Output: Truthy
print(is_truthy(""))         # Output: Falsy
print(is_truthy("NeetCode")) # Output: Truthy

# Pythonic idiomatic check vs explicit check
x = 10

if x:         # Idiomatic truthiness check
    print("x is not zero/empty")

if x != 0:    # Explicit comparison (functionally equivalent for numbers)
    print("x is not zero")
```

---

## Loops and Iteration

Loops control iterative code execution. Python provides two primary loop constructs: condition-driven (`while`) and sequence-driven (`for`). Like conditional blocks, loops in Python **do not** introduce a separate local scope; loop-bound variables remain accessible in the surrounding scope.

---

### While Loops

A `while` loop repeatedly executes its indented block as long as its conditional predicate evaluates to `True`. Requires explicit manual updates to the termination state to prevent infinite execution cycles.

```python
# Fixed iteration counter
i = 0
while i < 12:
    print("I know how to use while loops")
    i += 1  # Mandatory step update to guarantee termination

# Counting up sequence [0, 9]
i = 0
while i < 10:
    print(i)
    i += 1

# Stepped iteration with boundary checks (Multiples of 10)
i = 10
while 10 <= i <= 90:
    print(i)
    i += 10
```

---

### For Loops and `range()` Sequence Generation

The `for ... in` statement provides deterministic iteration over an iterable. The built-in `range()` constructor generates immutable arithmetic sequences on demand without allocating entire arrays in memory ($O(1)$ memory consumption via lazy sequence evaluation).

#### `range()` Parameter Signatures
* `range(stop)`: Generates integers from `0` up to `stop - 1` with step `1`.
* `range(start, stop)`: Generates integers from `start` up to `stop - 1` with step `1`.
* `range(start, stop, step)`: Generates integers from `start` stepping by `step` up to, but excluding, `stop`.

```python
# 1. Single Argument: range(stop) -> [0, 12]
for i in range(13):
    print(i)

# 2. Two Arguments: range(start, stop) -> [10, 20]
for i in range(10, 21):
    print(i)

# 3. Three Arguments: range(start, stop, step) -> [0, 100] by 10s
for i in range(0, 101, 10):
    print(i)
```

---

### Reverse Iteration

Decrementing iteration can be configured using a negative `step` value in `range()`, or by wrapping a forward sequence in the built-in iterator `reversed()`. `reversed(range(...))` achieves $O(1)$ memory overhead by relying on the sequence's internal indexing protocol without copying elements.

```python
# Decrementing with negative step: range(start, stop_exclusive, step)
for i in range(20, 9, -1):
    print(i)  # Iterates 20 down to 10

# Pythonic reversal using reversed()
for i in reversed(range(10)):
    print(i)  # Iterates 9 down to 0 without extra index arithmetic
```

---

### Nested Loops and Algorithmic Complexity

Placing a loop inside another creates nested iteration cycles. The inner loop runs to full completion for every single tick of the outer loop.

* **Variable Isolation:** Outer and inner control variables must use distinct names to avoid unwanted variable collisions.
* **Time Complexity:** Nesting iterations directly scales complexity. Two nested loops of size $N$ evaluate the inner payload in $O(N^2)$ quadratic time.

```python
# Generating cartesian products / pairs from [3, 5]
# Outer loop executes 3 times; inner loop executes 3 times per outer tick -> 9 total iterations
for i in range(3, 6):
    for j in range(3, 6):
        print(i, j)
```

---

## Strings

In Python, a string (`str`) is an **immutable sequence of Unicode code points** stored contiguously in memory. Because strings are sequences, they support length inspection, zero-based indexing, iteration, and slicing protocols.

---

### String Length and Time Complexity

The built-in `len()` function returns the number of characters in a string. In CPython, `str` instances are defined as C structs (`PyASCIIObject` / `PyCompactUnicodeObject`) that store their length explicitly as an internal metadata field (`ob_size`). 

* **Time Complexity:** Calling `len(s)` is strictly **$O(1)$ constant time** because it performs an internal field lookup rather than traversing characters.

```python
def get_longer_word(word1: str, word2: str) -> str:
    # O(1) length comparison; returns word1 if lengths are equal
    return word1 if len(word1) >= len(word2) else word2

print(get_longer_word("yellow", "orange"))  # Output: yellow
print(get_longer_word("red", "blue"))        # Output: blue
print(get_longer_word("green", "blue"))      # Output: green
```

---

### Zero-Based Indexing and Negative Offsets

Strings use zero-based positioning: indices span from `0` to `len(s) - 1`. 

* **Negative Indexing:** Python natively supports negative offsets mapping backward from the end, where `-1` points to `s[len(s) - 1]`.
* **Out-of-Bounds Constraint:** Accessing an explicit index $\ge \text{len}(s)$ or $< -\text{len}(s)$ raises an `IndexError`.

```python
s = "Hello"

print(s[0])   # Output: H (First character)
print(s[1])   # Output: e
print(s[-1])  # Output: o (Last character, equivalent to s[len(s) - 1])

# print(s[5]) # Raises IndexError: string index out of range
```

```python
def print_char_at_indices(word: str) -> None:
    print(word[0])   # First char
    print(word[1])   # Second char
    print(word[-1])  # Last char

print_char_at_indices("hello")
# Output:
# h
# e
# o
```

---

### String Traversal (Index vs Iteration Protocol)

Python provides two approaches to string traversal:

1. **Direct Sequence Iteration (Idiomatic):** Employs Python's iterator protocol directly over the collection. Minimizes indexing boilerplate and prevents off-by-one errors.
2. **Index-Based Iteration (`range(len(s))`):** Required when character index tracking is necessary.

```python
word = "Hello"

# Idiomatic traversal: O(N) Time, O(1) Auxiliary Space
for char in word:
    print(char)

# Index-based traversal
for i in range(len(word)):
    print(i, word[i])
```

Nested iterations over separate string sequences execute their inner frames completely for every outer tick, compounding to $O(N \times M)$ runtime:

```python
def print_string_characters(word1: str, word2: str) -> None:
    for word in (word1, word2):
        for char in word:
            print(char)

print_string_characters("Hello", "Hi")
```

---

### String Concatenation and Memory Reallocation

Because strings are immutable, the `+` operator does not mutate the existing buffer. It allocates a brand-new string object in heap memory and copies the bytes from both operands into it.

* **Complexity Warning:** Chaining concatenations across loops using `s += char` generates an anti-pattern scaling to **$O(N^2)$ quadratic time** due to repeated heap reallocations and copies. For bulk string assembly, the industry standard is appending elements to a dynamic array (`list`) and joining them in a single batch using `''.join(list)` in **$O(N)$ linear time**.

```python
def concatenate(s1: str, s2: str) -> str:
    joined = s1 + s2
    return "Too long!" if len(joined) > 10 else joined

print(concatenate("He", "llo"))            # Output: Hello
print(concatenate("Hello ", "world!"))      # Output: Too long!
print(concatenate("Length", "of10"))        # Output: Lengthof10
```

---

### String Slicing

Slicing extracts a substring using the structural syntax `sequence[start:stop:step]`.

* **Boundary Rules:** `start` is inclusive, `stop` is exclusive (`[start, stop)`).
* **Fault Tolerance:** Unlike single-character indexing (`s[i]`), slicing expressions **never raise an `IndexError`** when indices fall out of bounds; Python automatically truncates slices to valid sequence boundaries.
* **Allocation Cost:** Slicing creates a shallow copy of the requested character range, taking $O(K)$ time and $O(K)$ space where $K = \text{stop} - \text{start}$.

```python
# Basic Slicing [start, end)
s = "Hello, World!"
print(s[1:5])  # Output: ello (Indices 1, 2, 3, 4)

def get_substring(input_string: str, start: int, end: int) -> str:
    # Explicit validation example: guard against out-of-range bounds
    if end > len(input_string):
        return ""
    return input_string[start:end]

print(get_substring("NeetCode", 1, 7))  # Output: eetCod
print(get_substring("NeetCode", 1, 9))  # Output: "" (Exceeds length 8)
```

#### Omitted Slicing Parameters
Omitting parameters causes them to fall back to their default structural positions:
* `[:n]` captures the prefix from index `0` up to `n - 1`.
* `[n:]` captures the suffix from index `n` up to the string termination.
* `[:]` generates a shallow copy of the entire string sequence.

```python
def first_n_characters(s: str, n: int) -> str:
    return s[:n]

def last_n_characters(s: str, n: int) -> str:
    return s[-n:]

print(first_n_characters("NeetCode", 3))  # Output: Nee
print(last_n_characters("NeetCode", 4))   # Output: Code
```

---

### Extended Slicing and Reversal

The third slicing parameter (`step`) indicates stride and direction. A negative step strides backward across the memory buffer.

* **Reversal Syntax (`[::-1]`):** Traverses the entire sequence backward in **$O(N)$ Time** and **$O(N)$ Space** (allocating a new inverted string).

```python
s = "Hello"

# Stride slicing: s[start:stop:step]
print(s[1:4:1])   # Output: ell
print(s[3:0:-1])  # Output: lle (Indices 3, 2, 1 traversed backward)

# Sequence reversal
def reverse_string(input_string: str) -> str:
    return input_string[::-1]

print(reverse_string("NeetCode"))  # Output: edoCteeN
print(reverse_string("Hello!"))    # Output: !olleH
```

---

### String Immutability and In-Place Workarounds

Strings in Python cannot be mutated in place. Reassigning an index directly raises a `TypeError`.

```python
message = "I will never change."
# message[0] = "X"  # Raises TypeError: 'str' object does not support item assignment
```

To modify characters at specific positions, extract segments using slices and concatenate them into a new buffer, or cast the string to a mutable array (`list`), mutate indices in $O(1)$, and rejoin:

```python
# Strategy 1: Slicing and Concatenation
def remove_fourth_character(word: str) -> str:
    # Removes index 3 (4th character) by joining preceding and trailing slices
    return word[:3] + word[4:]

print(remove_fourth_character("NeetCode"))  # Output: NeeCode
print(remove_fourth_character("Hello"))     # Output: Helo

# Strategy 2: In-place Array Mutation (For complex character replacements)
raw_str = "bake"
char_list = list(raw_str)
char_list[0] = "m"
mutated_str = "".join(char_list)
print(mutated_str)  # Output: make
```

---

### String Interpolation and Formatting

Python supports multiple string interpolation mechanisms.

* **Legacy `str.format()`:** Replaces `{}` positional or indexed placeholders with evaluated arguments.
* **Formatted String Literals (`f-strings` / PEP 498):** Evaluated at runtime via optimized bytecode instructions (`BUILD_STRING`), making them faster than both `%` formatting and `.format()`. Expressions within `{}` are parsed and evaluated directly in place.

```python
# 1. str.format() syntax
msg_positional = "Hello, {}. You are {} years old.".format("Alice", 25)
msg_indexed    = "Hello, {1}. You are {0} years old.".format(25, "Alice")

# 2. Idiomatic f-strings (Industry Standard)
def say_goodbye(name: str, hour: int) -> str:
    return f"Goodbye, {name}. See you again at {hour} o'clock."

print(say_goodbye("Bob", 12))       # Output: Goodbye, Bob. See you again at 12 o'clock.
print(say_goodbye("NeetCode", 9))   # Output: Goodbye, NeetCode. See you again at 9 o'clock.
```

---

## Lists and Tuples

Lists and tuples are sequence data structures storing ordered collections of elements. Their primary architectural distinction lies in **mutability**, **memory allocation strategy**, and **runtime overhead**.

---

### Memory Architecture: The Dynamic Array

In CPython, a `list` is not a linked list; it is an **over-allocated, contiguous array of pointers** (`PyListObject`). Each slot in the array stores a 64-bit memory address pointing to the actual target object in heap memory.

* **Heterogeneous Storage:** Because lists store pointers rather than raw primitive bytes, a single list can reference distinct, arbitrary data types.
* **Random Access:** Index lookup (`nums[i]`) is strictly **$O(1)$ constant time**, calculated via pointer arithmetic: `address = base_address + (i * pointer_size)`.
* **Zero-Based & Negative Indexing:** Indices span $[0, N-1]$. Negative indices calculate offsets from the array boundary (`nums[-k]` resolves to `nums[len - k]`).

```python
# Contiguous pointer array referencing distinct heap objects
mixed_list: list[object] = [1, "Hello", 3.14, True]

print(mixed_list[0])   # Output: 1       (O(1) pointer dereference)
print(mixed_list[1])   # Output: Hello
print(mixed_list[-1])  # Output: True    (Resolves to mixed_list[len - 1])
print(len(mixed_list)) # Output: 4       (O(1) internal ob_size lookup)

# Mutation in-place: rebinds the pointer at index 0
nums: list[int] = [1, 2, 3, 4, 5]
nums[0] = 10
print(nums)  # Output: [10, 2, 3, 4, 5]
```

---

### Membership Testing and Truthiness

* **Truthiness:** An empty list `[]` evaluates to `False` in a boolean context; a list with elements evaluates to `True`. Checking `if not my_list:` is the idiomatic, performant pattern.
* **Linear Scan (`in` / `not in`):** Checking membership traverses elements sequentially via `PySequence_Contains`, running in **$O(N)$ linear time**.

```python
def check_list_empty(my_list: list[int]) -> bool:
    # Idiomatic truth-value testing (PEP 8)
    return not bool(my_list)

def check_element_in_list(my_list: list[str], target: str) -> bool:
    # O(N) linear search across pointer array
    return target in my_list

print(check_list_empty([]))                                # Output: True
print(check_list_empty([1, 2, 3]))                         # Output: False
print(check_element_in_list(["Apple", "Banana"], "Apple")) # Output: True
print(check_element_in_list(["Apple", "Banana"], "Grape")) # Output: False
```

> **Engineering Note:** If algorithm requirements involve frequent membership lookups (`x in collection`), cast or store elements in a `set` or `dict` to achieve **$O(1)$ amortized lookup time** via hashing.

---

### Iteration and Search Patterns

#### Traversal Approaches
* **Direct Iteration:** Idiomatic and clean when array indices are irrelevant.
* **Indexed Traversal:** Use `range(len(nums))` only when index manipulation or swap mechanics are needed.

```python
# Linear scan frequency counter: O(N) Time, O(1) Auxiliary Space
def count_occurrences(nums: list[int], target: int) -> int:
    count = 0
    for num in nums:
        if num == target:
            count += 1
    return count

print(count_occurrences([1, 2, 5, 6, 5], 5))  # Output: 2

# Equivalent to the C-optimized built-in method
print([1, 2, 5, 6, 5].count(5))               # Output: 2
```

#### First-Index Lookup (`.index()`)
Finds the lowest index where `target` appears. Operates via linear search in $O(N)$ time. If the element does not exist, it raises a `ValueError`.

```python
def find_index(nums: list[int], target: int) -> int:
    # Custom linear search implementation
    for i in range(len(nums)):
        if nums[i] == target:
            return i
    raise ValueError(f"{target} is not in list")

print(find_index([1, 2, 3, 4, 5], 3))  # Output: 2
print([1, 2, 3, 4, 5].index(3))        # Output: 2 (Built-in equivalent)
```

---

### Built-in Aggregations and Namespace Shadowing

Python exposes built-in global aggregators `sum()`, `min()`, and `max()`, executing in **$O(N)$ linear time**.

```python
dataset: list[int] = [7, 3, 4, 5]

print(sum(dataset))  # Output: 19
print(min(dataset))  # Output: 3
print(max(dataset))  # Output: 7
```

> **Critical Anti-Pattern (Shadowing Built-ins):** Never use `sum`, `min`, `max`, `list`, or `len` as variable or parameter identifiers. Doing so rebinds the identifier in the local scope, breaking access to the underlying built-in function until the frame exits.
>
> ```python
> # BUG: Rebinds 'sum' to an integer; subsequent calls to sum() will raise TypeError
> sum = 10 + 20 
> # sum([1, 2, 3])  # TypeError: 'int' object is not callable
> ```

---

### List Mutation Mechanics: Append vs Pop

| Operation | Syntax | Average Time Complexity | Worst-Case Time | Structural Mechanism |
| :--- | :--- | :---: | :---: | :--- |
| **Append** | `nums.append(x)` | $O(1)$ amortized | $O(N)$ | Inserts at the end; triggers resize and pointer copy when buffer is saturated. |
| **Pop Last** | `nums.pop()` | $O(1)$ | $O(1)$ | Decrements `ob_size` counter; zero memory shifting. |
| **Pop Arbitrary** | `nums.pop(i)` | $O(N)$ | $O(N)$ | Deletes element at $i$; shifts all subsequent elements $i+1 \dots N$ left. |

```python
# 1. Amortized O(1) Append: modifies array in place
def append_batch(base_list: list[int], new_elements: list[int]) -> list[int]:
    for element in new_elements:
        base_list.append(element)
    return base_list

print(append_batch([1, 2, 3], [4, 5]))  # Output: [1, 2, 3, 4, 5]

# 2. O(1) Tail Pop vs O(N) Shift Pop
stack: list[int] = [10, 20, 30, 40]

tail = stack.pop()      # O(1) Tail Removal -> Returns 40, list is [10, 20, 30]
head = stack.pop(0)     # O(N) Left Shift   -> Returns 10, list is [20, 30]
```

> **DSA Optimization:** If your algorithm requires an efficient FIFO queue (`pop(0)`), **do not use a standard list**. Use `collections.deque`, an implementation of a doubly linked list / array of blocks providing **$O(1)$ push/pop operations from both ends**.

---

### Slicing and Subarray Allocation

Slicing creates an entirely new `list` object and copies the specified pointer references into the new contiguous buffer.

* **Complexity:** Constructing `nums[start:end]` requires **$O(K)$ time and $O(K)$ space**, where $K = \text{end} - \text{start}$.
* **Shallow Copy Protocol:** Slicing duplicates the pointer array, **not** the underlying objects. If the list contains nested mutable structures, mutating a nested object mutates it across both lists.

```python
nums = [1, 2, 3, 4, 5]

# Slice operations: list[start:stop:step]
print(nums[1:3])   # Output: [2, 3]    (Subarray slice [1, 3))
print(nums[:3])    # Output: [1, 2, 3] (Prefix slice)
print(nums[-3:])   # Output: [3, 4, 5] (Suffix slice via negative index)
print(nums[::-1])  # Output: [5, 4, 3, 2, 1] (Reversed shallow copy)
```

---

### Tuples: Immutability and Memory Optimization

A `tuple` is an **immutable sequence** (`PyTupleObject`). Once instantiated, its length and pointer bindings cannot be altered.

```python
# Tuple instantiation
point: tuple[int, int] = (10, 20)
single_element_tuple: tuple[int] = (5,)  # Trailing comma required to avoid operator precedence syntax

# Access and slicing (Identical to lists)
print(point[0])     # Output: 10
print(point[-1])    # Output: 20
print(point[0:1])   # Output: (10,)
```

#### Architectural Differences: `list` vs `tuple`

| Architectural Metric | `list` | `tuple` |
| :--- | :--- | :--- |
| **Mutability** | Mutable (In-place modification supported) | Immutable (Read-only buffer) |
| **Memory Footprint** | Higher (Over-allocates memory for future inserts) | Minimal (Allocated to exact element length) |
| **Methods Available** | Mutators (`.append()`, `.pop()`, `.sort()`, `.extend()`) | Read-only only (`.count()`, `.index()`) |
| **Hashability** | Unhashable (Cannot be used as dictionary keys) | Hashable (Can serve as `dict` key or `set` element if contents are immutable) |
| **Allocation Speed** | Slower (Heap allocation and tracking overhead) | Faster (CPython caches small fixed tuples for reuse) |

```python
# Tuples as hashable keys (Valid composite key pattern in graph/DP algorithms)
memo: dict[tuple[int, int], int] = {}
memo[(0, 1)] = 42

# Attempting mutation raises TypeError
coordinates: tuple[int, int] = (4, 5)
# coordinates[0] = 10  # Raises TypeError: 'tuple' object does not support item assignment

# Safe record creation function (No variable shadowing)
def create_pair(name: str, age: int) -> tuple[str, int]:
    pair_record: tuple[str, int] = (name, age)
    return pair_record

print(create_pair("Alice", 25))  # Output: ('Alice', 25)
```

---

## Sets

A `set` is a **mutable, unordered collection of unique, hashable elements**. In CPython, sets are implemented via a hash table (`PySetObject`), structurally identical to a dictionary that stores keys with dummy values.

---

### Core Properties and Memory Mechanics

* **Uniqueness:** Duplicate insertions are discarded without raising exceptions.
* **Unordered Nature:** Elements are not sequenced by insertion order or numerical value; they occupy buckets determined by their hash value (`hash(x)`). Indexing (`s[0]`) and slicing (`s[:]`) raise a `TypeError`.
* **Hashability Requirement:** Only immutable/hashable objects (implementing `__hash__()` and `__eq__()` consistently) can reside in a set. Adding a `list` or `set` raises a `TypeError: unhashable type`.
* **Empty Set Instantiation:** Empty curly braces `{}` instantiate a `dict` by default in Python syntax. An empty set **must** be created using the constructor `set()`.

```python
# Literal syntax with duplicates (automatically deduped)
unique_numbers: set[int] = {1, 2, 3, 3, 2, 1}
print(unique_numbers)  # Output: {1, 2, 3}

# Instantiation pitfall
empty_dict = {}       # type: dict
empty_set = set()     # type: set

# O(1) Amortized insertion
empty_set.add(1)
empty_set.add(2)
empty_set.add(1)      # Redundant insertion ignored
print(empty_set)      # Output: {1, 2}
```

---

### Algorithmic Complexity: `list` vs `set`

| Operation | `list` Complexity | `set` Average Complexity | `set` Worst-Case Complexity | Underlying Mechanism |
| :--- | :---: | :---: | :---: | :--- |
| **Membership (`x in s`)** | $O(N)$ | $O(1)$ | $O(N)$ | Direct hash bucket lookup vs linear scan. |
| **Insertion (`.add(x)`)** | $O(1)$ amortized (`.append`) | $O(1)$ | $O(N)$ | Computes `hash(x)`, probes bucket, inserts pointer. |
| **Deletion (`.remove(x)`)** | $O(N)$ (`.remove`) | $O(1)$ | $O(N)$ | Locates hash bucket directly without shifting elements. |
| **Iteration** | $O(N)$ | $O(N)$ | $O(N)$ | Iterates through sparse hash table buckets. |

> **DSA Takeaway:** Any interview problem asking for repeated lookups, existence checks, or frequency filters must default to a `set` (or `dict`) to avoid falling into $O(N^2)$ brute-force traps.

---

### Set Operations and Removals

* **`.remove(x)`:** Deletes `x` in $O(1)$ amortized time. Raises a `KeyError` if `x` is absent.
* **`.discard(x)`:** Deletes `x` in $O(1)$ amortized time, but executes as a no-op if `x` is absent (never raises `KeyError`).

```python
tech_stack: set[str] = {"Python", "C++", "SQL"}

tech_stack.remove("C++")     # Removes element
# tech_stack.remove("Rust")  # Raises KeyError: 'Rust'

tech_stack.discard("Rust")    # Safe removal: does nothing, no error raised
print(tech_stack)            # Output: {'Python', 'SQL'}
```

---

### Deduplication Patterns

Converting a sequence to a `set` and back to a `list` strips duplicates in **$O(N)$ Time** and **$O(N)$ Space**.

```python
def deduplicate_preserve_order_agnostic(nums: list[int]) -> list[int]:
    # Destroys original sequence ordering
    return list(set(nums))

print(deduplicate_preserve_order_agnostic([1, 2, 3, 4, 5, 5, 3, 4, 5])) 
# Output: [1, 2, 3, 4, 5]
```

> **Optimization Note:** `list(set(seq))` loses initial index ordering. To deduplicate while **preserving insertion order** in $O(N)$, leverage `dict.fromkeys()` (guaranteed insertion order since Python 3.7):
> ```python
> ordered_unique = list(dict.fromkeys([1, 2, 3, 2, 1]))  # Output: [1, 2, 3]
> ```

---

### High-Yield LeetCode Patterns: Duplicate Detection

#### 1. Global Set Comparison (Batch Evaluation)
Determining whether any duplicate exists by evaluating cardinalities:

$$\text{Contains Duplicates} \iff |S| \neq |L|$$

```python
def contains_duplicate_batch(words: list[str]) -> bool:
    # O(N) Time, O(N) Space: Allocates entire set upfront
    return len(words) != len(set(words))

print(contains_duplicate_batch(["hello", "world", "hello"]))  # Output: True
print(contains_duplicate_batch(["python", "algorithms"]))      # Output: False
```

#### 2. Early-Exit Streaming Hash Set (Optimal Online Check)
The batch approach processes the entire array even if duplicates exist at indices `0` and `1`. An early-return pattern terminates in **$O(1)$ Best-Case Time**:

```python
def contains_duplicate_early_stop(words: list[str]) -> bool:
    seen: set[str] = set()
    for word in words:
        if word in seen:  # O(1) amortized hash lookup
            return True
        seen.add(word)    # O(1) amortized insertion
    return False

print(contains_duplicate_early_stop(["apple", "banana", "apple", "grape"]))  # Output: True
```

#### 3. Counting Unique Elements
Using `len(set(...))` computes distinct element counts in $O(N)$ linear time:

```python
def count_unique_words(words: list[str]) -> int:
    return len(set(words))

print(count_unique_words(["hello", "world", "hello", "goodbye"]))  # Output: 3
print(count_unique_words([]))                                      # Output: 0
```

---

## Dictionaries (Hash Maps)

A dictionary (`dict`) is an **associative mapping of unique, hashable keys to arbitrary value objects**. In CPython, dictionaries are implemented as **compact, ordered hash tables** consisting of a sparse index array and a dense entries array (`PyDictObject`), guaranteeing **$O(1)$ amortized average-time complexity** for insertions, lookups, and deletions while preserving insertion order.

---

### Core Mechanics and Hash Table Architecture

* **Key Constraints:** Keys must implement `__hash__()` and `__eq__()` consistently. Mutable containers (`list`, `set`, `dict`) cannot serve as dictionary keys (`TypeError: unhashable type`).
* **Value Space:** Values can be any arbitrary object (primitives, nested lists, callables, or nested dictionaries).
* **Insertion Order:** Since Python 3.7 (CPython 3.6 implementation detail), dictionaries preserve insertion order deterministically by appending pairs to an internal dense array while routing lookups through a sparse index hash array.
* **Empty Instantiation:** Curly braces `{}` evaluate to an empty `dict`, not a `set`.

```python
# Literal dictionary definition
user_record: dict[str, int] = {
    "Alice": 25,
    "Bob": 30,
    "Charlie": 35
}

# Dynamic construction and key assignment
user_map: dict[str, int] = {}
user_map["Alice"] = 25
user_map["Bob"] = 30
user_map["Charlie"] = 35

print(user_map["Alice"])  # Output: 25 (O(1) amortized hash lookup)
print(len(user_map))       # Output: 3  (O(1) ob_size field lookup)
```

```python
# Modern type hinting (PEP 585): use native lowercase `dict[K, V]`
def create_dict(name: str, age: int) -> dict[str, int]:
    return {name: age}

def list_to_dict(words: list[str]) -> dict[str, int]:
    # Enumerate index mapping in O(N) Time
    return {word: index for index, word in enumerate(words)}

print(create_dict("Alice", 25))
# Output: {'Alice': 25}

print(list_to_dict(["Alice", "Jane", "Joe"]))
# Output: {'Alice': 0, 'Jane': 1, 'Joe': 2}
```

---

### Key Overwrites, Nested Maps, and Lookups

* **Key Uniqueness:** Assigning to an existing key updates the value pointer in place without shifting buckets or creating duplicate keys.
* **Missing Key Access:** Indexing a non-existent key directly (`d[key]`) raises a `KeyError`.
* **Membership Check:** The `in` operator checks key existence across buckets in **$O(1)$ amortized time** (unlike $O(N)$ linear scans on lists).

```python
grades: dict[str, int | list[int] | dict[str, int]] = {
    "math": 90,
    "scores": [95, 88, 92],
    "sub_module": {"algebra": 100}
}

# Overwriting existing key
grades["math"] = 98
print(grades["math"])  # Output: 98

# O(1) Amortized membership validation
print("math" in grades)     # Output: True
print("history" in grades)  # Output: False

# Safe retrieval avoiding KeyError:
# print(grades["history"])          # Raises KeyError: 'history'
print(grades.get("history", 0))     # Output: 0 (Returns default fallback)
```

---

### Dictionary View Iteration Protocols

Python dictionaries expose three zero-copy dynamic **view objects** (`dict_keys`, `dict_values`, `dict_items`). These views maintain a dynamic window directly into the hash table's internal array without allocating duplicate data buffers.

| View Method | Yielded Element | Type Signature |
| :--- | :--- | :--- |
| `dict.keys()` (default) | Keys only | `dict_keys[K, V]` |
| `dict.values()` | Values only | `dict_values[K, V]` |
| `dict.items()` | Key-Value pairs | `dict_items[K, V]` as `tuple[K, V]` |

```python
student_ages: dict[str, int] = {"Alice": 25, "Bob": 30, "Jane": 22}

# 1. Default iteration: traverses keys
def get_dict_keys(age_dict: dict[str, int]) -> list[str]:
    return list(age_dict.keys())  # Or list(age_dict) directly

# 2. Iterating values directly
def get_dict_values(age_dict: dict[str, int]) -> list[int]:
    return list(age_dict.values())

# 3. Tuple unpacking over items: O(N) Time
for name, age in student_ages.items():
    print(f"{name} -> {age}")

print(get_dict_keys(student_ages))    # Output: ['Alice', 'Bob', 'Jane']
print(get_dict_values(student_ages))  # Output: [25, 30, 22]
```

---

### Deletion and Key Removal Mechanics

* **`.pop(key[, default])`:** Deletes the key and returns its bound value in **$O(1)$ amortized time**. If `key` is not found, it returns `default`. If no default is provided, it raises a `KeyError`.
* **`del d[key]`:** Removes the key-value mapping directly via statement syntax. Raises a `KeyError` if absent.

```python
cache: dict[str, int] = {"a": 1, "b": 2, "c": 3}

# O(1) Deletion via pop
val = cache.pop("a")        # val = 1; cache is now {"b": 2, "c": 3}
safe_val = cache.pop("z", 0) # Key not found -> returns default fallback 0

# Deletion via del statement
del cache["b"]               # cache is now {"c": 3}

# Batch removal pattern with safe fallback
def remove_keys(my_dict: dict[str, int], keys_to_remove: list[str]) -> dict[str, int]:
    for key in keys_to_remove:
        my_dict.pop(key, None)  # Idempotent removal: avoids KeyError branch checks
    return my_dict

print(remove_keys({"a": 1, "b": 2, "c": 3}, ["a", "c", "missing"]))
# Output: {'b': 2}
```

---

### Algorithmic Patterns: Frequency Map (Hash Table Accumulation)

Frequency counting is an essential algorithm pattern for array, string, and hash table interview problems (e.g., LeetCode 242: Valid Anagram, LeetCode 1: Two Sum).

#### Standard Branching Counter ($O(N)$ Time, $O(K)$ Space)
```python
def count_characters(word: str) -> dict[str, int]:
    frequencies: dict[str, int] = {}
    for char in word:
        if char in frequencies:
            frequencies[char] += 1
        else:
            frequencies[char] = 1
    return frequencies

print(count_characters("hello world"))
# Output: {'h': 1, 'e': 1, 'l': 3, 'o': 2, ' ': 1, 'w': 1, 'r': 1, 'd': 1}
```

#### Production Optimizations: `.get()`, `defaultdict`, and `Counter`
* **Idiomatic `.get()`:** Eliminates verbose `if/else` checks:
  ```python
  frequencies[char] = frequencies.get(char, 0) + 1
  ```
* **`collections.defaultdict`:** Supplies a callable factory (e.g., `int`) to automatically initialize absent keys on access:
  ```python
  from collections import defaultdict
  freq = defaultdict(int)
  for char in word:
      freq[char] += 1
  ```
* **`collections.Counter`:** C-level optimized hash bag implementation executing in single-pass $O(N)$ runtime:
  ```python
  from collections import Counter
  freq = Counter("hello world")
  ```

---

## Reading Standard Input (stdin) and Parsing

In production systems, competitive programming, and automated assessment platforms (e.g., Codeforces, LeetCode command-line runners), input is streamed through the OS file descriptor `0` (**Standard Input / `sys.stdin`**). Python abstracts this stream via the built-in `input()` function and the low-level `sys.stdin` file object.

---

### Core Mechanics of `input()`

The `input([prompt])` function reads a line from the input stream until it encounters an EOF (End-Of-File) or a newline character (`\n`).

* **Type Invariant:** `input()` **strictly returns a string (`str`)**.
* **Trailing Delimiter Stripping:** Unlike low-level reads, `input()` automatically strips the trailing newline character (`\n` / `\r\n`) from the returned string.
* **Flushing Prompts:** When passing a string to `prompt`, Python writes it to `sys.stdout` without an automatic trailing newline, keeping the cursor on the same line for interactive terminal input. In non-interactive judges (OJ platforms), prompts should be omitted (`input()`) to avoid polluting the output stream.

```python
def read_and_print_input() -> None:
    # Captures stream input into a dynamic string reference
    user_data: str = input("Reading one line of text into a string: ")
    print(user_data)
# Simulating multiple sequential reads across lines
# read_and_print_input()
# read_and_print_input()
```

---

### Explicit Type Casting on Stream Data

Because standard input is delivered as serialized text, reading numerical primitives requires explicit parsing via type constructors (`int()`, `float()`).

* **Exceptions:** If the stream payload contains non-convertible characters (e.g., whitespace, letters), constructors raise a `ValueError`.
* **Whitespace Safety:** Leading and trailing whitespaces are automatically ignored by `int()` and `float()` (e.g., `int(" 42 \n")` correctly evaluates to `42`).

```python
def read_integer() -> int:
    # O(K) where K is the number of digits parsed
    return int(input())

def read_float() -> float:
    # Parses 64-bit IEEE 754 double precision float
    return float(input())
```

---

### String Tokenization and Delimiter Parsing

When inputs arrive in batch format on a single line (e.g., comma-separated or space-separated values), the raw text buffer must be split into discrete tokens.

* **`str.split(sep=None, maxsplit=-1)`:** Splits the string by a specified delimiter substring and returns a dynamic `list[str]`.
* **Memory & Complexity:** Splitting takes **$O(N)$ Time** and allocates **$O(N)$ Space**, where $N$ is the byte length of the input line.

```python
# 1. Parsing comma-separated values into integer lists
def read_integers() -> list[int]:
    line: str = input()
    tokens: list[str] = line.split(",")  # Splits into substring tokens
    
    # List comprehension: idiomatic, optimized in CPython bytecode
    return [int(token) for token in tokens]

# 2. Arithmetic reduction from delimited stream
def add_two_numbers() -> int:
    line: str = input()
    num1_str, num2_str = line.split(",")  # Direct tuple unpacking
    return int(num1_str) + int(num2_str)
```

---

### Production & Competitive Programming Optimization: `sys.stdin` vs `input()`

In technical assessments processing large-scale data ($N \ge 10^5$ lines), `input()` becomes an **I/O bottleneck** because it executes extra logic per line (stripping whitespace, handling prompts, raising EOF exceptions). 

For Big Tech interviews and high-throughput data pipelines, use `sys.stdin.readline` to achieve **$2\times$ to $5\times$ faster I/O speeds**:

```python
import sys

# Fast I/O Single Line Reader (keeps trailing '\n', requires .rstrip())
def fast_read_line() -> str:
    return sys.stdin.readline().rstrip()

# Fast Multi-Variable Unpacking via map()
# Input format: "10 20 30" (space-separated)
def read_coordinates() -> tuple[int, ...]:
    return tuple(map(int, sys.stdin.readline().split()))

# High-Performance Batch Stream Iterator (Processes entire input in linear time)
def process_full_stream() -> list[int]:
    # sys.stdin reads lazy file chunks without loading entire datasets into memory at once
    return [int(line.strip()) for line in sys.stdin if line.strip()]
```
