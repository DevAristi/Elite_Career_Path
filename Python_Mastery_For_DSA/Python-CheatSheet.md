# Python Cheat Sheet for Beginners

### Comments

Use `#` for single-line comments.

Shortcut in most code editors (VS Code):
* **Windows / Linux:** `Ctrl + /`
* **macOS:** `Cmd + /`

---

### Variables and Assignment

In Python, a variable is not a memory container; it is a **name reference (pointer)** bound to an object in memory.

```python
message = "this string is stored in a variable"
print(message)
```

---

### Reassignment and Dynamic Typing
Python is dynamically and strongly typed. You do not declare types explicitly, and a variable can reference different data types over its lifecycle:

```py
x = 10         # bound to an int object
x = "Hello"    # rebound to a str object
x = [1, 2, 3]  # rebound to a list object
```

Contrast with Static Typing (e.g., Java / C++): Variable types are bound at compile-time and cannot reference a different type.

---

### Multiple Assignment and Unpacking
Assign multiple variables in a single line using comma separation in both sides:

```py
msg1, msg2 = "Hello", "World"
```

---

### Core Data Types

```py
age = 25             # int (arbitrary precision integer)
temperature = 98.6   # float (double-precision 64-bit IEEE 754)
is_active = True     # bool (True / False, subclass of int)
name = "Alice"       # str (immutable Unicode sequence)
items = [1, 2, 3]    # list (mutable dynamic array)
```

To inspect an object's type at runtime, use type():

```py
print(type(10))  # Output: <class 'int'>
```

---

### Explicit Type Casting

Convert objects explicitly using built-in constructors. Note that int() on a float truncates decimals towards zero without rounding:

```py
raw_value = 10.9
parsed_value = int(raw_value)

print(parsed_value)  # Output: 10
```
