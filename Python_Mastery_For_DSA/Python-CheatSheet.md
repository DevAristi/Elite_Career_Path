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

# Floor Division (//): Divides and rounds down to the nearest integer
print(x // y)  # Output: 3

# Modulus (%): Returns the remainder of division
print(x % y)   # Output: 1

# Exponentiation (**): Raises base to the power of exponent
print(x ** y)  # Output: 49 (7^2)
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

Logical operators evaluate Boolean expressions and return `True` or `False`.

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
