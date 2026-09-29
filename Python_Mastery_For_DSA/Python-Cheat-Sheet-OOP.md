# Python OOP Cheat Sheet

---

## Classes, Objects, and the `self` Binding Mechanism

Python implements **Object-Oriented Programming (OOP)** by treating classes as runtime blueprints that instantiate stateful objects. In CPython, an instance is fundamentally a heap-allocated structure wrapping an internal attribute namespace dictionary (`__dict__`), where methods operate via explicit instance binding passed through the `self` parameter.

---

### Class Declaration and the `__init__` Constructor

A class acts as an extensible blueprint defining instance state (attributes) and behavior (methods).

* **Naming Convention:** Class identifiers follow `PascalCase` according to PEP 8 specifications.
* **The `__init__` Hook:** The constructor method `__init__` runs automatically upon instance instantiation. It does **not** allocate memory (memory allocation is handled earlier by `__new__`); rather, it initializes attribute bindings on the newly created instance.
* **Namespace Isolation (`name` vs `self.name`):** Parameters inside `__init__` reside strictly within the method's local stack frame. Prefixing with `self.` explicitly binds the reference to the instance's persistent heap memory dictionary (`instance.__dict__`).

```python
class Pet:
    # Explicit type hints document the attribute initialization contract
    def __init__(self, name: str, species: str, hunger: int = 5, energy: int = 10) -> None:
        self.name: str = name          # Bound to instance namespace
        self.species: str = species    # Bound to instance namespace
        self.hunger: int = hunger      # Default parameter value supported
        self.energy: int = energy

# Instantiation allocates a new heap instance and passes it implicitly as 'self'
my_pet = Pet(name="Fluffy", species="cat", hunger=6, energy=8)
print(f"My pet is a {my_pet.species} named {my_pet.name}")
# Output: My pet is a cat named Fluffy
```

---

### Object Instantiation and Parameter Ordering

Instantiating an object invokes the class callable (`Class(*args, **kwargs)`).

* **Positional Argument Coupling:** Positional arguments map directly to the parameters of `__init__` from left to right. Passing values out of order results in mismatched state bindings without triggering runtime errors if types overlap.

```python
class SuperHero:
    def __init__(self, name: str, power: str, health: int, speed: int) -> None:
        self.name: str = name
        self.power: str = power
        self.health: int = health
        self.speed: int = speed

# Correct positional mapping
iron_man = SuperHero("Iron Man", "repulsor beams", 100, 80)
spider_man = SuperHero("Spider-Man", "web-slinging", 90, 95)

# Instantiating concrete stateful instances
whiskers = Pet("Whiskers", "cat", hunger=6, energy=8)
print(f"{whiskers.name} ({whiskers.species}) - Hunger: {whiskers.hunger}, Energy: {whiskers.energy}")
# Output: Whiskers (cat) - Hunger: 6, Energy: 8
```

---

### Attribute Access, In-Place Mutation, and Dynamic Typing Risks

Instance attributes are accessed and updated via **dot notation** (`object.attribute`).

* **In-Place Mutation:** Numeric and collection attributes can be mutated directly via in-place arithmetic operators (`+=`, `-=`).
* **Dynamic Type Mutation Pitfall:** Python allows rebinding an attribute to a completely different data type at runtime (e.g., changing `whiskers.hunger` from `int` to `str`). While syntactically legal, this breaks class type contracts and is considered a critical anti-pattern in production code.

```python
whiskers = Pet("Whiskers", "cat", hunger=6, energy=8)

# Reading attributes via dot notation
print(f"Initial: {whiskers.name} ({whiskers.species}) - Hunger: {whiskers.hunger}, Energy: {whiskers.energy}")
# Output: Initial: Whiskers (cat) - Hunger: 6, Energy: 8

# Modifying attributes directly in memory
whiskers.hunger -= 3  # Decrement hunger
whiskers.energy += 2  # Increment energy

print(f"Modified: {whiskers.name} ({whiskers.species}) - Hunger: {whiskers.hunger}, Energy: {whiskers.energy}")
# Output: Modified: Whiskers (cat) - Hunger: 3, Energy: 10
```

---

### Instance Methods and State Encapsulation

Methods are functions declared inside the body of a class that encapsulate logic operating on the instance's internal state.

* **Method vs. Function:** A function exists independently in a module namespace, whereas a method is bounded to a class and receives an instance as its first positional parameter.
* **Encapsulated Mutation:** Methods directly read and alter `self` attributes across successive invocation frames.

```python
class PetAction:
    def __init__(self, name: str) -> None:
        self.name: str = name
        self.hunger: int = 5

    # Instance method mutating internal state
    def feed(self) -> None:
        self.hunger -= 1
        print(f"{self.name} has been fed.")
        print(f"{self.name}'s hunger level: {self.hunger}")

fluffy = PetAction("Fluffy")
fluffy.feed()  # hunger becomes 4
fluffy.feed()  # hunger becomes 3
fluffy.feed()  # hunger becomes 2
# Output:
# Fluffy has been fed.
# Fluffy's hunger level: 4
# Fluffy has been fed.
# Fluffy's hunger level: 3
# Fluffy has been fed.
# Fluffy's hunger level: 2
```

---

### The `self` Mechanism and Method Dispatch Mechanics

In Python, `self` is not a reserved language keyword (unlike `this` in C++ or Java); it is an explicit syntactic convention.

* **Descriptor Binding Protocol:** When invoking `instance.method(arg)`, Python's descriptor protocol automatically rewrites the call behind the scenes:

$$\text{ironman.power\_boost}(15) \iff \text{SuperHero.power\_boost}(\text{ironman}, 15)$$

* **The Missing `self` Error:** Omitting `self` in a method definition triggers an argument mismatch error upon invocation:
  `TypeError: method() takes 1 positional argument but 2 were given`
  This occurs because the runtime passes the calling instance as the first argument automatically.

```python
class HeroCombat:
    def __init__(self, name: str, power: str, strength: int) -> None:
        self.name: str = name
        self.power: str = power
        self.strength: int = strength

    # 'self' receives the caller instance; additional parameters follow positionally
    def power_boost(self, strength_increase: int) -> None:
        self.strength += strength_increase
        print(f"{self.name}'s strength increased to {self.strength}!")

ironman = HeroCombat("Iron Man", "Repulsor Beams", 85)

# Dot notation method dispatch
ironman.power_boost(15)
# Output: Iron Man's strength increased to 100!

# Identical direct class dispatch exposing the underlying mechanism:
HeroCombat.power_boost(ironman, 15)
# Output: Iron Man's strength increased to 115!
```

---

### Low-Level Memory Inspection: `__dict__` vs. `__slots__`

By default, every Python class instance maintains an internal dictionary `__dict__` that stores its dynamically bound attributes:

```python
hero = HeroCombat("Spider-Man", "Web", 90)
print(hero.__dict__)
# Output: {'name': 'Spider-Man', 'power': 'Web', 'strength': 90}
```

> **Systems Optimization (`__slots__`):** 
> Because `__dict__` is a resizable hash table, each instance introduces substantial memory overhead (~150+ bytes per object). In high-throughput architectures (such as processing millions of records in Data/ML pipelines or game entities), define `__slots__` to replace `__dict__` with a static C-style array of pointers, reducing instance memory consumption by up to **60%**:
>
> ```python
> class OptimizedHero:
>     __slots__ = ("name", "power", "strength")  # Allocates fixed array of pointers
>     def __init__(self, name: str, power: str, strength: int) -> None:
>         self.name = name
>         self.power = power
>         self.strength = strength
> ```

---

## Object Lifecycle, Docstrings, and Domain Modeling

Object-Oriented Design in Python encompasses the complete lifecycle of an instance: allocation, initialization, encapsulation, self-documentation, and runtime behavior mutation.

---

### Low-Level Object Construction: `__new__` vs `__init__`

In Python, the terminology "constructor" is commonly applied to `__init__`, but at the CPython runtime level, instantiation is split into two distinct lifecycle phases:

1. **Allocation (`__new__`):** The true constructor static method (`__new__(cls, *args, **kwargs)`). It allocates raw heap memory for the new instance, returning a fresh, uninitialized object reference.
2. **Initialization (`__init__`):** The instance initializer hook (`__init__(self, *args, **kwargs)`). It receives the allocated instance reference via `self` and populates attributes within the instance namespace dictionary (`self.__dict__`). It must return `None` (returning any value raises a `TypeError`).

$$\text{Pet}(\text{"Fluffy"}, \dots) \implies \text{instance} = \text{Pet}.\_\_new\_\_(\text{Pet}); \quad \text{Pet}.\_\_init\_\_(\text{instance}, \text{"Fluffy"}, \dots)$$

```python
class Pet:
    """A class representing a domesticated animal entity."""

    def __init__(self, name: str, species: str, age: int) -> None:
        """Initialize attribute bindings on the newly allocated instance namespace."""
        self.name: str = name
        self.species: str = species
        self.age: int = age

# Instantiation delegates arguments directly through to __init__
fluffy = Pet("Fluffy", "cat", 3)
buddy = Pet("Buddy", "dog", 2)

print(f"{fluffy.name} is a {fluffy.age} year old {fluffy.species}.")
# Output: Fluffy is a 3 year old cat.

print(f"{buddy.name} is a {buddy.age} year old {buddy.species}.")
# Output: Buddy is a 2 year old dog.
```

> **Missing `__init__` Parameter Fallback:** If a class omits `__init__`, it inherits `object.__init__`, which accepts zero arguments. Passing instantiation arguments without an explicit signature raises `TypeError: Pet() takes no arguments`.

---

### Production Self-Documentation: Docstrings (PEP 257)

Docstrings (`"""..."""`) are string literals placed as the first statement in classes, methods, or functions. Unlike regular comments (`#`), the CPython compiler binds them directly to the object's `__doc__` metadata attribute at runtime, enabling inspection tools (`help()`, Sphinx, OpenAPI generators).

#### Standard Production Format (Google Style / Sphinx)
* **Class Docstring:** Outlines class purpose and public instance attributes.
* **Method Docstring:** Outlines action, arguments (`Args:`), return value (`Returns:`), and exceptions (`Raises:`).

```python
class DocumentedPet:
    """A class to represent a pet.

    Attributes:
        name (str): The pet's name.
        animal_type (str): The pet's biological taxonomy or category.
    """

    def __init__(self, name: str, animal_type: str) -> None:
        """Initialize a new Pet instance."""
        self.name: str = name
        self.animal_type: str = animal_type

    def make_sound(self) -> str:
        """Return the sound the pet makes based on its type."""
        if self.animal_type == "dog":
            return "Woof!"
        elif self.animal_type == "cat":
            return "Meow!"
        return "Unknown sound"

# Accessing runtime metadata directly via dunder attributes
print(DocumentedPet.__doc__)
print(DocumentedPet.__init__.__doc__)
print(DocumentedPet.make_sound.__doc__)
```

---

### Domain Modeling: State Encapsulation and Method Mutation

In Low-Level Design (LLD) interviews, entities must encapsulate state and expose mutations strictly through public method interfaces to uphold invariants (Object-Oriented Encapsulation).

```python
class SuperHero:
    """A class to represent a superhero entity in a game engine.

    Attributes:
        name (str): The superhero's alias.
        power (str): The primary active ability.
        health (int): Current structural hit points.
    """

    def __init__(self, name: str, power: str, health: int) -> None:
        self.name: str = name
        self.power: str = power
        self.health: int = health

    def attack(self) -> None:
        """Execute offensive action utilizing the entity's core power."""
        print(f"{self.name} attacks with {self.power}!")

    def heal(self, amount: int = 10) -> None:
        """Restore instance health points by a specified scalar delta."""
        self.health += amount
        print(f"{self.name} heals {amount} points. New health: {self.health}.")

# Multi-instance instantiation
batman = SuperHero("Batman", "Intelligence", 100)
superman = SuperHero("Superman", "Strength", 150)
catwoman = SuperHero("Catwoman", "Agility", 120)

# Method invocation: runtime binds instance implicitly to 'self'
catwoman.attack()
# Output: Catwoman attacks with Agility!

catwoman.heal(10)
# Output: Catwoman heals 10 points. New health: 130.
```

---

### Low-Level Class Structure: Class Attributes vs Instance Attributes

* **Instance Attributes (`self.attr`):** Bound to the distinct `instance.__dict__` heap dictionary; isolated per instance.
* **Class Attributes (defined in class body outside methods):** Bound to `Class.__dict__`; shared by **all** instances of the class.
* **Mutation Pitfall:** Mutating a mutable class attribute (such as a `list`) via an instance reference modifies the shared structure across every instance. To maintain instance isolation, always initialize mutable data structures inside `__init__`.

```python
class CombatArena:
    # Class attribute: shared globally across all CombatArena instances
    total_arenas_created: int = 0

    def __init__(self, arena_name: str) -> None:
        # Instance attribute: unique to each instance
        self.arena_name: str = arena_name
        CombatArena.total_arenas_created += 1

arena1 = CombatArena("Gotham")
arena2 = CombatArena("Metropolis")
print(CombatArena.total_arenas_created)  # Output: 2 (Global class state tracked)
```

---

## Encapsulation, Access Modifiers, and Descriptors (`@property`)

Encapsulation bundles internal state and operational behavior within a single logical entity while restricting unauthorized or unvalidated state transitions from external scopes. Unlike languages like C++ or Java that enforce compile-time visibility keywords (`public`, `protected`, `private`), **CPython does not enforce hardware or compiler-level access security**. Instead, access control is governed through naming conventions, runtime name mangling, and the first-class descriptor protocol.

---

### Public Attributes and Methods

By default, every attribute and method declared inside a Python class is public.

* **Memory Representation:** Public variables map directly to string keys in the instance's hash table (`instance.__dict__`).
* **Direct Access & Mutation:** External scopes can inspect or reassign these variables at runtime using standard dot notation (`obj.attr = val`).
* **Recommended Use Case:** Plain data holders and configuration classes where values require no runtime constraints or invariant validations.

```python
class StoreItem:
    def __init__(self, name: str, price: float) -> None:
        self.name: str = name        # Public instance attribute
        self.price: float = price    # Public instance attribute

chips = StoreItem("Chips", 1.99)

# Direct external read and write in O(1) time
print(chips.name)   # Output: Chips
print(chips.price)  # Output: 1.99

chips.price = 2.49  # In-place unvalidated update
```

---

### Protected Attributes (Single Underscore Convention: `_attr`)

An identifier prefixed with a single leading underscore (`_protected`) signals to developers, linters, and static type checkers that **the attribute is internal to the class and its derived subclasses**.

* **CPython Behavior:** The runtime imposes no access restrictions. The variable remains accessible via `self.__dict__['_attr']`.
* **Philosophical Design:** Grounded in Python's *"We are all consenting adults here"* principle: the language provides visibility guidelines rather than enforcing restrictive boundaries.

```python
class Account:
    def __init__(self, title: str, balance: int) -> None:
        self.title: str = title          # Public
        self._balance: int = balance     # Protected by convention

    def display_balance(self) -> None:
        """Internal access to protected member."""
        print(f"Balance: ${self._balance}")

    def get_balance(self) -> int:
        return self._balance

account = Account("John", 1000)
account.display_balance()  # Output: Balance: $1000

# Direct access is syntactically legal but strongly discouraged in production:
# print(account._balance)  # Violates interface encapsulation boundaries
```

---

### Private Attributes and Name Mangling (`__attr`)

Prefixing an identifier with two leading underscores (without trailing underscores) invokes CPython's **Name Mangling** mechanism to avoid namespace collisions across inheritance hierarchies.

* **Lexical Transformation:** The compiler dynamically rewrites the identifier within the bytecode by prefixing `_ClassName`:
  $$\text{\_\_password} \implies \text{\_PasswordManager\_\_password}$$

* **Encapsulation Effect:** Accessing `obj.__password` externally raises an error: `AttributeError: 'PasswordManager' object has no attribute '__password'`.

```python
class PasswordManager:
    def __init__(self, password: str) -> None:
        # Mangled into _PasswordManager__password internally
        self.__password: str = password

    def verify_password(self, input_password: str) -> bool:
        # Access within class scope automatically resolves the mangled name
        return self.__password == input_password

vault = PasswordManager("secret123")

print(vault.verify_password("secret123"))  # Output: True
print(vault.verify_password("wrong"))      # Output: False

# vault.__password  # Raises AttributeError: 'PasswordManager' object has no attribute '__password'

# Low-level memory inspection confirming lexical rewrite:
print(vault.__dict__)
# Output: {'_PasswordManager__password': 'secret123'}
```

---

### Classic Accessors: Getters and Setters

In classic object-oriented designs, internal state is shielded behind explicit accessor methods (`get_<attr>()` and `set_<attr>()`) to enforce domain invariant checks.

```python
class BankAccountClassic:
    def __init__(self, balance: int) -> None:
        self.__balance: int = balance

    def get_balance(self) -> int:
        """Traditional getter returning encapsulated state."""
        return self.__balance

    def set_balance(self, new_balance: int) -> None:
        """Traditional setter enforcing business invariant validation."""
        if new_balance >= 0:
            self.__balance = new_balance
        else:
            print("Cannot set negative balance!")

account = BankAccountClassic(1000)
account.set_balance(-100)  # Output: Cannot set negative balance!
account.set_balance(500)   # Valid mutation
print(account.get_balance())  # Output: 500
```

---

### Pythonic Property Descriptors: `@property` and `@setter`

Relying on custom `get_*` and `set_*` methods produces unidiomatic Python APIs and forces breaking refactors when an existing public attribute requires validation down the line. Python solves this via the built-in `@property` decorator.

#### Internal Descriptor Mechanics
The `property` type implements the **Python Data Descriptor Protocol** (`__get__`, `__set__`, `__delete__`):

$$\text{account.balance} \iff \text{BankAccount.\_\_dict\_\_['balance'].\_\_get\_\_(account, BankAccount)}$$
$$\text{account.balance = val} \iff \text{BankAccount.\_\_dict\_\_['balance'].\_\_set\_\_(account, val)}$$

* Enables clean attribute-style reads and assignments (`obj.balance = 100`) while routing operations through validation logic under the hood.
* **Naming Constraint:** The underlying storage attribute must use a distinct identifier (such as `_balance` or `__balance`). Reusing the exact property name inside the setter causes an immediate **infinite recursion crash** (`RecursionError: maximum recursion depth exceeded`).

```python
class BankAccount:
    def __init__(self, balance: int) -> None:
        # Private backing store holding physical value in heap memory
        self._balance: int = balance

    # Getter descriptor exposing attribute-like read interface
    @property
    def balance(self) -> int:
        return self._balance

    # Setter descriptor intercepting mutations for validation
    @balance.setter
    def balance(self, value: int) -> None:
        if value >= 0:
            self._balance = value
        else:
            print("Balance cannot be negative!")

account = BankAccount(1000)

# Attribute-style read delegates internally to @property.getter
print(account.balance)  # Output: 1000

# Attribute-style assignment delegates internally to @balance.setter
account.balance = -100  # Output: Balance cannot be negative!
print(account.balance)  # Output: 1000 (State invariant safely preserved)

account.balance = 2500  # Valid update
print(account.balance)  # Output: 2500
```

---

### Visibility Matrix and Trade-Offs

| Visibility Level | Syntax Pattern | External Direct Access | CPython Runtime Behavior | Primary Production Use Case |
| :--- | :--- | :---: | :--- | :--- |
| **Public** | `self.attr` | Yes (`obj.attr`) | Standard lookup via `self.__dict__['attr']`. | General state without validation requirements. |
| **Protected** | `self._attr` | Yes (Discouraged) | Untransformed storage; communicates internal contract | Internal attributes shared with subclasses. |
| **Private** | `self.__attr` | No (Raises `AttributeError`) | Name mangling alters identifier to `_ClassName__attr`. | Avoiding subclass namespace collisions. |
| **Managed Property** | `@property` / `@attr.setter` | Yes (Transparent) | Executes descriptor methods bound to `Class.__dict__`. | Validation, caching, and computed attributes. |

---

### Advanced Encapsulation: Domain Invariants and Descriptor Refactoring

In production systems and low-level software architecture, encapsulation serves a higher purpose than syntactic information hiding: it protects **domain invariants and business constraints** before allowing any internal state transition.

Below is the comparative breakdown between traditional accessor methods (`get_*` / `set_*`) and Python's descriptor protocol using `@property` and `@<attribute>.setter`.

---

### Traditional Accessors: Explicit Getters and Setters

In classic object-oriented designs (mirroring Java or C++ paradigms), fields are kept strictly private (`__attribute`), and state transitions are routed through dedicated accessor methods to enforce validation boundaries.

* **Private Backing Fields (`__health`, `__power_level`):** CPython applies dynamic *Name Mangling* at compile time (rewriting them internally to `_SuperHero__health` and `_SuperHero__power_level`), preventing unintentional direct writes from external scopes.
* **Domain Interval Validation:**
  * Health interval: $[0, 100]$ inclusive.
  * Power Level interval: $[1, 10]$ inclusive.
* **Interface Contract:** Requires consumer code to interact exclusively through method invocation syntax (`hero.get_health()`, `hero.set_health(val)`).

```python
class SuperHeroExplicit:
    """Classic encapsulation using explicit getter and setter methods."""

    def __init__(self, name: str, health: int, power_level: int) -> None:
        self.name: str = name  # Public attribute
        # Private attributes mangled by CPython runtime
        self.__health: int = health
        self.__power_level: int = power_level

    # --- Health Accessors ---
    def get_health(self) -> int:
        """Returns the current health state."""
        return self.__health

    def set_health(self, value: int) -> None:
        """Enforces interval invariant [0, 100] for health."""
        if value > 100:
            print("You can't set the health to more than 100")
        elif value < 0:
            print("You can't set the health to less than 0")
        else:
            self.__health = value

    # --- Power Level Accessors ---
    def get_power_level(self) -> int:
        """Returns the current power level state."""
        return self.__power_level

    def set_power_level(self, value: int) -> None:
        """Enforces interval invariant [1, 10] for power level."""
        if value > 10:
            print("You can't set the power level to more than 10")
        elif value < 1:
            print("You can't set the power level to less than 1")
        else:
            self.__power_level = value


# Instantiation and boundary validation execution
batman_classic = SuperHeroExplicit("Batman", 80, 9)

print(batman_classic.get_health())  # Output: 80
batman_classic.set_health(110)      # Output: You can't set the health to more than 100
batman_classic.set_health(-10)      # Output: You can't set the health to less than 0
batman_classic.set_health(70)       # Valid mutation

print(batman_classic.get_power_level())  # Output: 9
batman_classic.set_power_level(11)       # Output: You can't set the power level to more than 10
batman_classic.set_power_level(0)        # Output: You can't set the power level to less than 1
batman_classic.set_power_level(7)        # Valid mutation

# Formatted output relying purely on accessor methods
print(
    f"{batman_classic.name} has {batman_classic.get_health()} health and "
    f"{batman_classic.get_power_level()} power level"
)
# Output: Batman has 70 health and 7 power level
```

---

### Pythonic Standard: Refactoring to `@property` and `@setter`

Relying on explicit accessor methods introduces boilerplate and violates the **Uniform Access Principle**. Python provides the `@property` decorator to seamlessly attach validation and side-effects to standard attribute syntax (`obj.attr = val`).

#### Architectural Advantages in Production
* **Zero Client Disruption:** Migrating from an unvalidated public attribute to a validated managed property requires zero syntax changes for existing callers.
* **Descriptor Protocol Integration:** Attribute accesses and assignments translate directly into descriptor lookups on the class dictionary (`SuperHero.__dict__['health'].__set__`).

```python
class SuperHero:
    """Idiomatic implementation utilizing data descriptors via @property."""

    def __init__(self, name: str, health: int, power_level: int) -> None:
        self.name: str = name  # Public attribute
        # Private storage references in heap memory
        self.__health: int = health
        self.__power_level: int = power_level

    # ==========================================
    # Property: Health [0, 100]
    # ==========================================
    @property
    def health(self) -> int:
        """Getter descriptor for health."""
        return self.__health

    @health.setter
    def health(self, value: int) -> None:
        """Setter descriptor enforcing [0, 100] boundary invariant."""
        if value > 100:
            print("You can't set the health to more than 100")
        elif value < 0:
            print("You can't set the health to less than 0")
        else:
            self.__health = value

    # ==========================================
    # Property: Power Level [1, 10]
    # ==========================================
    @property
    def power_level(self) -> int:
        """Getter descriptor for power level."""
        return self.__power_level

    @power_level.setter
    def power_level(self, value: int) -> None:
        """Setter descriptor enforcing [1, 10] boundary invariant."""
        if value > 10:
            print("You can't set the power level to more than 10")
        elif value < 1:
            print("You can't set the power level to less than 1")
        else:
            self.__power_level = value


# Instantiation and idiomatic attribute interaction
super_hero = SuperHero("Batman", 80, 9)

# Read & write interceptions for 'health'
print(super_hero.health)  # Output: 80 (Invokes @property getter)
super_hero.health = 110   # Output: You can't set the health to more than 100
super_hero.health = -10   # Output: You can't set the health to less than 0
super_hero.health = 80    # Valid reassignment

# Read & write interceptions for 'power_level'
print(super_hero.power_level)  # Output: 9 (Invokes @property getter)
super_hero.power_level = 100   # Output: You can't set the power level to more than 10
super_hero.power_level = 0     # Output: You can't set the power level to less than 1
super_hero.power_level = 9     # Valid reassignment

# Final output string using property evaluation
print(f"{super_hero.name} has {super_hero.health} health and {super_hero.power_level} power level")
# Output: Batman has 80 health and 9 power level
```

---

### Paradigm Comparison: Methods vs. Properties

| Dimension | Explicit Getters/Setters | Managed Descriptors (`@property`) |
| :--- | :--- | :--- |
| **Consumption Syntax** | `obj.get_val()` / `obj.set_val(x)` | `obj.val` / `obj.val = x` (Direct attribute syntax) |
| **Interface Surface** | Bloats public API with accessor helper functions. | Clean and concise; encapsulates read/write paths under one identifier. |
| **Retroactive Refactoring** | Breaking change: requires updating all external call sites. | Non-breaking: public attributes can become properties transparently. |
| **Recursion Risk** | None. | **Critical Risk:** Assigning to `self.attr` instead of `self._attr` causes `RecursionError`. |
| **Industry Adoption** | Considered an unidiomatic anti-pattern in modern Python. | **Standard design pattern** across major production libraries (Django, PyTorch, FastAPI). |

---

## Class Attributes, Class Methods (`@classmethod`), and Static Methods (`@staticmethod`)

In CPython's object model, the boundary between instance-level state and class-level state is defined by the separation of their underlying hash table dictionaries: `instance.__dict__` versus `Class.__dict__`. Understanding the attribute resolution order, descriptor binding mechanics, and method execution lifecycles is foundational for high-performance software engineering and scalable system design.

---

### Class Attributes vs. Instance Attributes

* **Class Attribute:** Defined directly within the class body outside of any method. It lives in `Class.__dict__` and is shared globally across every instance of that class.
* **Instance Attribute:** Defined inside methods using explicit assignment to `self` (`self.attr = value`). It lives inside the instance's unique heap dictionary (`instance.__dict__`).
* **Attribute Resolution Order:** Reading `instance.attr` first checks `instance.__dict__`; if absent, it traverses up to `Class.__dict__`, followed by the inheritance chain via the Method Resolution Order (MRO).

#### The Attribute Shadowing Pitfall
Assigning to an attribute via an instance pointer (`instance.class_attr = val`) **does not mutate** the shared class variable. Instead, it dynamically injects a new key into `instance.__dict__`, shadowing the class-level variable for that specific instance only. To safely mutate a shared class attribute, always access it through the explicit class reference (`ClassName.attr`) or via `cls.attr` inside a class method.

```python
class SmartDevice:
    # Class attributes: shared global counters
    total_devices: int = 0
    active_devices: int = 0

    def __init__(self, name: str) -> None:
        self.name: str = name  # Isolated instance attribute
        # Direct class-level mutation increments global state
        SmartDevice.total_devices += 1

    def turn_on(self) -> None:
        """Increment the global active device counter."""
        SmartDevice.active_devices += 1

    def turn_off(self) -> None:
        """Decrement the global active device counter."""
        SmartDevice.active_devices -= 1


# Multi-instance tracking validation
tv = SmartDevice("TV")
lights = SmartDevice("Lights")

tv.turn_on()
lights.turn_on()
tv.turn_off()

print(f"Total Devices: {SmartDevice.total_devices}")    # Output: Total Devices: 2
print(f"Active Devices: {SmartDevice.active_devices}")  # Output: Active Devices: 1
```

---

### Separation of Concerns: Aggregated State vs. Private State

In financial pipelines and ledger architectures, aggregate system-wide metrics belong to the class namespace, whereas distinct ledger balances and customer identifiers belong to individual instance namespaces.

```python
class BankAccount:
    # Global entity metrics (Class Level)
    total_accounts: int = 0
    total_balance: int = 0

    def __init__(self, name: str, balance: int) -> None:
        # Isolated account state (Instance Level)
        self.name: str = name
        self.balance: int = balance

        # Update global accounting invariants
        BankAccount.total_accounts += 1
        BankAccount.total_balance += balance


# Instantiation and verification of global aggregates
alice = BankAccount("Alice", 1000)
bob = BankAccount("Bob", 2000)

print(f"Alice's balance: ${alice.balance}")            # Output: Alice's balance: $1000
print(f"Bob's balance: ${bob.balance}")                # Output: Bob's balance: $2000
print(f"Total Accounts: {BankAccount.total_accounts}") # Output: Total Accounts: 2
print(f"Total Balance: ${BankAccount.total_balance}")  # Output: Total Balance: $3000
```

---

### Class Methods (`@classmethod`)

A method decorated with `@classmethod` binds to the class object (`type`) rather than to a specific instance.

* **Mandatory First Parameter (`cls`):** CPython automatically passes the class object as the first argument upon invocation.
* **Polymorphic Inheritance:** Using `cls.attribute` instead of hardcoding `ClassName.attribute` respects the Liskov Substitution Principle; when inherited by a subclass, `cls` correctly resolves to the derived class type.
* **Alternative Constructors:** Acts as the primary industry idiom for factory methods (e.g., `from_json`, `from_csv`, `from_config`).

```python
class Library:
    # Global catalog counter
    books_available: int = 100

    @classmethod
    def lend_books(cls, number: int) -> None:
        """Mutate class-level inventory via cls reference."""
        cls.books_available -= number

    @classmethod
    def return_books(cls, number: int) -> None:
        """Restore class-level inventory via cls reference."""
        cls.books_available += number


print(f"Initial status: {Library.books_available} books available")  # Output: 100
Library.lend_books(30)
print(f"After lending: {Library.books_available} books available")    # Output: 70
Library.return_books(10)
print(f"After return: {Library.books_available} books available")     # Output: 80
```

---

### Static Methods (`@staticmethod`)

A method decorated with `@staticmethod` is a pure function scoped inside a class's namespace for cohesion and code organization.

* **No Automatic Binding:** Receives neither an instance reference (`self`) nor a class pointer (`cls`).
* **Isolation Contract:** Cannot alter or access object-specific state. Accessing class attributes requires an explicit class name reference.
* **Optimal Use Cases:** Pure mathematical transformations, utility helpers, and decoupled input validators.

```python
class CurrencyConverter:
    # Exchange rate conversion map relative to USD
    rates: dict[str, float] = {
        'EUR': 1.20,
        'JPY': 0.01
    }

    @staticmethod
    def to_usd(amount: float, currency: str) -> float:
        """Pure conversion utility evaluating the CurrencyConverter rates map."""
        exchange_rate = CurrencyConverter.rates[currency]
        return amount * exchange_rate


print(f"100 EUR = {CurrencyConverter.to_usd(100, 'EUR')} USD")  # Output: 100 EUR = 120.0 USD
print(f"100 JPY = {CurrencyConverter.to_usd(100, 'JPY')} USD")  # Output: 100 JPY = 1.0 USD
```

---

### Calculation Engines and Algorithm Decoupling

Decoupling mathematical evaluations into static methods isolates core computational formulas from memory-bound object state, enabling clean unit testing and eliminating side-effects.

$$\text{Effective Power} = \text{base\_power} \times \left(1 + \frac{\sum \text{attributes}}{\vert{}\text{attributes}\vert{}}\right)$$


```python
class Hero:
    def __init__(self, name: str, base_power: int, attributes: dict[str, int]) -> None:
        self.name: str = name
        self.base_power: int = base_power
        self.attributes: dict[str, int] = attributes

    @staticmethod
    def calculate_effective_power(base_power: int, attributes: dict[str, int]) -> float:
        """Computes weighted average power in linear O(K) time."""
        if not attributes:
            return float(base_power)

        # O(K) aggregation where K = len(attributes)
        attribute_bonus = sum(attributes.values()) / len(attributes)
        effective_power = base_power * (1 + attribute_bonus)
        return round(effective_power, 1)


hero_attributes = {'strength': 7, 'speed': 6, 'intelligence': 8}
effective = Hero.calculate_effective_power(8, hero_attributes)
print(f"Effective Power: {effective}")  # Output: Effective Power: 64.0
```

---

### Method Dispatch Matrix

| Method Category | Decorator | First Injected Parameter | Runtime Binding Target | Primary Engineering Purpose |
| :--- | :--- | :---: | :--- | :--- |
| **Instance Method** | *(None)* | `self` | Dynamic heap instance | Modifying and reading object-specific private state. |
| **Class Method** | `@classmethod` | `cls` | Metaclass / Class `type` object | Alternative factory constructors and global class state updates. |
| **Static Method** | `@staticmethod` | *(None)* | Unbound pure function | Independent math engines, serializers, and pure utility logic. |

---

## Inheritance, Method Overriding (`super()`), and Method Resolution Order (MRO)

Inheritance enables a derived class (subclass) to inherit attributes and methods from an existing base class (superclass), supporting modular code reuse and behavioral specialization. Understanding how CPython resolves method dispatches, chains initializers via `super()`, and computes linearization across multiple inheritance hierarchies via the C3 algorithm is critical for clean object-oriented architecture.

---

### Single Inheritance and Code Reuse

When a class inherits from another (`class SubClass(BaseClass):`), the subclass inherits the state and interface declarations of its parent.

* **Default Constructor Behavior:** If the child class omits an `__init__` constructor, Python automatically calls the parent's `__init__` method upon instantiation.
* **Attribute Lookup Path:** Accessing an attribute on an instance first queries `instance.__dict__`. If absent, lookup traverses to the child class's `__dict__`, then continues upward through the parent class hierarchy.

```python
class SmartDevice:
    """Base superclass representing hardware device state."""
    def __init__(self, name: str) -> None:
        self.name: str = name


class SmartLight(SmartDevice):
    """Subclass inheriting identity attributes from SmartDevice."""
    def turn_on(self) -> None:
        print(f"{self.name} is turned on")
    def turn_off(self) -> None:
        print(f"{self.name} is turned off")


# Instantiation executes SmartDevice.__init__ implicitly
device = SmartLight("Smart Light")
device.turn_on()   # Output: Smart Light is turned on
device.turn_off()  # Output: Smart Light is turned off
```

---

### Method Overriding and Polymorphic Dispatch

Method overriding occurs when a subclass defines a method with the exact same name as a method in its superclass, replacing or specializing its runtime execution.

* **Namespace Shadowing:** Defining a method in the subclass binds that name inside the subclass dictionary, intercepting calls before lookup reaches the base class.
* **Polymorphism:** Allows different subclasses sharing an abstract interface to execute type-specific behavior dynamically.

```python
class Animal:
    def __init__(self, name: str) -> None:
        self.name: str = name

    def make_sound(self) -> None:
        print("Animal makes a sound")


class Dog(Animal):
    def make_sound(self) -> None:
        # Overrides Animal.make_sound for Dog entities
        print(f"{self.name} is barking")


class Cat(Animal):
    def make_sound(self) -> None:
        # Overrides Animal.make_sound for Cat entities
        print(f"{self.name} is meowing")


cow = Animal("Cow")
dog = Dog("Max")
cat = Cat("Luna")

cow.make_sound()  # Output: Animal makes a sound
dog.make_sound()  # Output: Max is barking
cat.make_sound()  # Output: Luna is meowing
```

---

### Cooperative Initialization with `super()`

If a subclass defines its own `__init__`, Python **does not** automatically execute the parent's `__init__`. To preserve and extend parent state without duplicating code, use `super()`.

* **Zero-Argument `super()` Syntax:** Resolves the current enclosing class and caller instance (`self`) dynamically at runtime.
* **Behavior Extension:** Allows child methods to execute base implementations and chain additional attributes or validation steps.

$$\text{Child}.\_\_init\_\_ \implies \text{super}().\_\_init\_\_(\dots) \to \text{Parent}.\_\_init\_\_$$


```python
class SuperHero:
    def __init__(self, name: str, power: str) -> None:
        self.name: str = name
        self.power: str = power

    def attack(self) -> None:
        print(f"{self.name} is attacking with {self.power}")


class Avenger(SuperHero):
    def __init__(self, name: str, power: str, team: str) -> None:
        # Delegates base initialization to SuperHero.__init__
        super().__init__(name, power)
        self.team: str = team

    def attack(self) -> None:
        # Executes base attack logic prior to any extended subclass actions
        super().attack()


hero = Avenger("Iron Man", "repulsor beams", "Avengers")
print(hero.name)    # Output: Iron Man
print(hero.power)   # Output: repulsor beams
print(hero.team)    # Output: Avengers
hero.attack()       # Output: Iron Man is attacking with repulsor beams
```

---

### Multiple Inheritance

Python allows a class to inherit from multiple parent classes simultaneously (`class Child(Parent1, Parent2):`).

* **Interface Composition:** Enables mixing decoupled functionalities (such as Mixins) into a single entity without deep vertical hierarchies.
* **Precedence Order:** Methods and attributes are searched following the exact order in which base classes are declared.

```python
class ElectronicDevice:
    def __init__(self, brand: str, model: str) -> None:
        self.brand: str = brand
        self.model: str = model

    def turn_on(self) -> None:
        print("Device is turning on")

    def turn_off(self) -> None:
        print("Device is turning off")


class HealthDevice:
    def __init__(self, brand: str, model: str) -> None:
        self.brand: str = brand
        self.model: str = model

    def measure_heart_rate(self) -> None:
        print("Measuring heart rate")


# Multiple inheritance inherits capabilities from both interfaces
class SmartWatch(ElectronicDevice, HealthDevice):
    pass


watch = SmartWatch("Apple", "Watch Series 6")
watch.turn_on()             # Output: Device is turning on
watch.measure_heart_rate()  # Output: Measuring heart rate
watch.turn_off()            # Output: Device is turning off
```

---

### The Diamond Problem and C3 Linearization (MRO)

When two intermediate classes inherit from the same root class and a subclass subsequently inherits from both, a **Diamond Hierarchy** is formed:

```
      A
     / \
    B   C
     \ /
      D
```

To resolve method calls deterministically without infinite loops or duplicate visits, CPython computes a **Method Resolution Order (MRO)** using the **C3 Linearization Algorithm**.

#### Rules of C3 MRO:
1. Subclasses are checked **before** their parent classes.
2. Multiple parents are evaluated strictly in **left-to-right order** of definition (`class D(B, C):` searches `B` before `C`).
3. Common base classes are visited only after all descendant branches are evaluated.
4. The exact resolution sequence is inspectable via the class attribute `__mro__` or the method `.mro()`.

```python
class A:
    def print_method(self) -> None:
        print("A")


class B(A):
    def print_method(self) -> None:
        print("B")


class C(A):
    def print_method(self) -> None:
        print("C")


# Order 1: class D(B, C) -> MRO: [D, B, C, A, object] -> Resolves to B
class D_B_First(B, C):
    pass


# Order 2: class D(C, B) -> MRO: [D, C, B, A, object] -> Resolves to C
class D_C_First(C, B):
    pass


d = D_B_First()
d.print_method()  # Output: B

# Inspecting the exact linearization array
print([cls.__name__ for cls in D_B_First.__mro__])
# Output: ['D_B_First', 'B', 'C', 'A', 'object']
```

---

### Architectural Design Matrix: Single vs. Multiple vs. Composition

| Architecture Pattern | Relationship | Lookup Complexity | Coupling Level | Primary Production Use Case |
| :--- | :--- | :---: | :---: | :--- |
| **Single Inheritance** | Is-a | $O(D)$ linear depth | Tight | Specialized domain hierarchies (e.g., AST nodes, ORM models). |
| **Multiple Inheritance** | Is-many | $O(N)$ via C3 MRO | Very Tight | Stateless Mixins, protocol integrations, framework extensions. |
| **Composition** | Has-a | $O(1)$ direct call | Loose | **Preferred standard** in Low-Level Design (LLD); minimizes state collision. |

---

## Polymorphism, Method Overloading Emulation, and Duck Typing

Polymorphism ("many forms") is an object-oriented paradigm allowing distinct objects to respond to the same interface or method call with class-specific behaviors. In statically typed languages (C++, Java), polymorphism splits strictly between **compile-time polymorphism** (static method overloading and templates) and **runtime polymorphism** (virtual table dynamic dispatch via inheritance). In Python's dynamic runtime, polymorphism is achieved through **Runtime Method Overriding**, **Argument-based Overloading Emulation**, and **Duck Typing**.

---

### Runtime Polymorphism via Inheritance and Method Overriding

Runtime polymorphism occurs when subclasses provide custom implementations of an inherited method signature defined on a shared base class.

* **Unified Call Interface:** A polymorphic dispatcher function accepts any instance sharing the base class interface and invokes the target method dynamically at runtime without explicit `isinstance()` checks.
* **Dynamic Resolution:** At call time, CPython checks the instance's concrete class type and executes its overridden version from the class dictionary.

```python
class Animal:
    def __init__(self, name: str) -> None:
        self.name: str = name

    def make_sound(self) -> None:
        print("Animal is making a sound")


class Dog(Animal):
    def make_sound(self) -> None:
        print(f"{self.name} says: Woof!")


class Cat(Animal):
    def make_sound(self) -> None:
        print(f"{self.name} says: Meow!")


# Polymorphic dispatcher: receives any Animal subtype and dispatches dynamically
def make_animal_sound(animal: Animal) -> None:
    animal.make_sound()


# Dynamic method dispatch execution
make_animal_sound(Animal("Rabbit"))   # Output: Animal is making a sound
make_animal_sound(Dog("Buddy"))       # Output: Buddy says: Woof!
make_animal_sound(Cat("Whiskers"))    # Output: Whiskers says: Meow!
```

---

### Method Overloading in Python: The CPython Limitation and Workarounds

In C++ or Java, method overloading allows defining multiple methods with the exact same name as long as their parameter signatures differ. 

* **The Python Trap:** Python **does not support native method overloading** by signature. In CPython, defining a method with the same name multiple times simply rebinds the class dictionary key to the newest function pointer, completely overwriting earlier declarations.
* **The Idiomatic Solution:** Emulate overloading using **default arguments (`None`)**, **variable-length argument lists (`*args`, `**kwargs`)**, or the standard library's `@functools.singledispatch` decorator.

#### Pattern 1: Default Parameters (`None` Sentinel)
```python
class TextProcessor:
    def format_text(self, text1: str, text2: str | None = None) -> str:
        """Emulates overloading: transforms to uppercase if 1 arg, concatenates if 2 args."""
        if text2 is None:
            return text1.upper()
        return text1 + text2


processor = TextProcessor()
print(processor.format_text("hello"))           # Output: HELLO
print(processor.format_text("hello", "world"))  # Output: helloworld
```

#### Pattern 2: Mathematical Overloading via Branching Arity
A single calculation method can branch logic depending on the presence of optional dimension parameters (e.g., distinguishing circle area vs. rectangle area):

$$\text{Circle Area} = \pi \cdot r^2, \quad \text{Rectangle Area} = \text{length} \cdot \text{width}$$


```python
import math

class AreaCalc:
    def calculate(self, length: float, width: float | None = None) -> float:
        """Calculates circle area if 1 arg passed (radius); rectangle area if 2 args passed."""
        if width is None:
            radius = length
            area = math.pi * (radius ** 2)
            return round(area, 2)
        return length * width


calc = AreaCalc()
print(calc.calculate(5))     # Output: 78.54 (Circle radius calculation)
print(calc.calculate(4, 6))  # Output: 24    (Rectangle dimensions)
```

---

### Duck Typing: Behavioral Polymorphism

Duck Typing originates from the phrase: *"If it walks like a duck and quacks like a duck, it's a duck"*. 

* **Behavior over Type Identity:** In Python, a function does not care about an object's inheritance tree or nominal class name; it strictly checks whether the object provides the **required methods or attributes at runtime**.
* **Loose Coupling:** Eliminates rigid subclassing requirements, allowing completely unrelated classes to be passed interchangeably to consumers as long as they satisfy the behavioral contract.

```python
class SpiderMan:
    def attack(self) -> str:
        return "Web Shooter!"

    def defend(self) -> str:
        return "Spider Sense!"


class BlackWidow:
    def attack(self) -> str:
        return "Widow's Bite!"

    def defend(self) -> str:
        return "Acrobatic Dodge!"


# Duck-typed consumer: depends strictly on .attack() and .defend() methods
def battle_sequence(hero: object) -> None:
    print(hero.attack())
    print(hero.defend())


battle_sequence(SpiderMan())
# Output:
# Web Shooter!
# Spider Sense!

battle_sequence(BlackWidow())
# Output:
# Widow's Bite!
# Acrobatic Dodge!
```

> **Interview Trade-Off:** Duck typing maximizes architectural flexibility and speeds up prototyping, but missing attributes are only caught at runtime (`AttributeError: 'X' object has no attribute 'y'`). In large-scale enterprise systems, enforce static interfaces using Python's `typing.Protocol` (PEP 544) to get duck typing benefits alongside static type-checker verification.

---

### Polymorphic Domain Modeling: Battle Entity System

Combining inheritance hierarchies, cooperative `super()` initialization, and polymorphic method overrides provides structured domain encapsulation for game engines and business rule processors.

```python
class Hero:
    def __init__(self, name: str, power: int) -> None:
        self.name: str = name
        self.health: int = 100
        self.power: int = power

    def attack(self) -> int:
        return self.power


class Warrior(Hero):
    def attack(self) -> int:
        # Specialized combat modifier for Warrior
        return self.power + 10


class Mage(Hero):
    def __init__(self, name: str, power: int) -> None:
        super().__init__(name, power)
        self.health = 80  # Mages trade base survivability for higher burst damage

    def attack(self) -> int:
        # Specialized combat modifier for Mage
        return self.power + 20


def show_attack(hero: Hero) -> None:
    """Polymorphically extracts damage output across disparate hero classes."""
    print(f"{hero.name} attacks with {hero.attack()} damage!")


warrior = Warrior("Bob", 20)
mage = Mage("Alice", 15)

show_attack(warrior)  # Output: Bob attacks with 30 damage!
show_attack(mage)     # Output: Alice attacks with 35 damage!
```

---

### Architectural Comparison: Polymorphic Strategies in Python

| Strategy | Mechanism | Coupling Level | Static Safety | Primary Use Case |
| :--- | :--- | :---: | :---: | :--- |
| **Inheritance Overriding** | Subclass redefines parent method; dispatched via MRO. | Tight (Tied to base class) | High (Enforced via abstract base classes/type hints) | Domain models with shared fundamental state (e.g., UI widgets, DB models). |
| **Overloading Emulation** | Default arguments (`None`), `*args`, or `@singledispatch`. | Self-contained within single class | High (Signature documented via overloads) | Multi-format parsers, flexible math constructors, coordinate parsers. |
| **Duck Typing** | Direct invocation relying strictly on runtime attribute presence. | Loose (Zero nominal coupling) | Low (Runtime `AttributeError` risk without `Protocol`) | File-like streams, serializers, decoupled plug-in extensions. |

---

## Abstraction, Abstract Base Classes (`abc.ABC`), and Interfaces in Python

**Abstraction** is an object-oriented design pillar focused on hiding internal implementation complexity while exposing only essential interfaces to callers. While **encapsulation** operates at the implementation level by grouping and shielding internal state via access conventions and descriptors, abstraction operates at the architecture level by establishing **what** an entity does rather than **how** it is built.

---

### Data and Behavioral Abstraction

* **Data Abstraction:** Conceals underlying data representations (private state or complex buffers) so consumers avoid coupling to internal details.
* **Behavioral Abstraction:** Hides branching algorithms and state manipulation behind high-level method invocations.

```python
class Superhero:
    """Behavioral abstraction: callers invoke fly() without managing internal power metrics."""

    def __init__(self, name: str) -> None:
        self.name: str = name
        self._power_level: int = 40  # Encapsulated state

    def fly(self) -> str:
        """Evaluates and deducts energy thresholds internally without exposing state mechanics."""
        if self._power_level >= 20:
            self._power_level -= 20
            return "Up up and away!"
        return "Too tired to fly..."


hero = Superhero("Superman")
print(hero.fly())  # Output: Up up and away!
print(hero.fly())  # Output: Up up and away!
print(hero.fly())  # Output: Too tired to fly...
```

---

### Abstract Base Classes and Contracts (`abc.ABC`)

By default, Python does not prevent instantiation of classes intended as incomplete parent blueprints. To enforce rigid subclass contracts at runtime, the standard library provides the `abc` (*Abstract Base Classes*) module.

* **`ABC`:** The formal base class from `abc`. Inheriting from `ABC` configures metaclass hooks (`ABCMeta`) to intercept instantiation.
* **`@abstractmethod`:** Marks a method as an enforced contract. If a subclass fails to override and implement every method decorated with `@abstractmethod`, CPython raises a `TypeError` upon instantiation.

```python
from abc import ABC, abstractmethod

class PaymentCard(ABC):
    """Abstract Base Class: cannot be instantiated directly."""

    def __init__(self, card_number: str, balance: float) -> None:
        self.card_number: str = card_number
        self.balance: float = balance

    @abstractmethod
    def process_payment(self, amount: float) -> str:
        """Mandatory abstract contract for all concrete derived classes."""
        pass


class DebitCard(PaymentCard):
    def process_payment(self, amount: float) -> str:
        # Enforces non-negative balance checks for debit transactions
        if self.balance < amount:
            return "Insufficient funds"
        self.balance -= amount
        return "Payment successful"


class CreditCard(PaymentCard):
    def process_payment(self, amount: float) -> str:
        # Allows balance to drop below zero (credit line semantics)
        self.balance -= amount
        return "Payment successful"


debit_card = DebitCard("1234", 100.0)
credit_card = CreditCard("5678", 100.0)

print(debit_card.process_payment(50.0))    # Output: Payment successful
print(debit_card.balance)                 # Output: 50.0
print(debit_card.process_payment(100.0))   # Output: Insufficient funds
print(debit_card.balance)                 # Output: 50.0

print(credit_card.process_payment(50.0))   # Output: Payment successful
print(credit_card.balance)                # Output: 50.0
print(credit_card.process_payment(100.0))  # Output: Payment successful
print(credit_card.balance)                # Output: -50.0
```

---

### Pure Interfaces vs. Abstract Base Classes

In languages such as Java or C#, an `interface` is a distinct keyword from an abstract class. In Python, a pure interface is expressed using an `ABC` subclass that contains **only methods decorated with `@abstractmethod`**, completely omitting state initialization (`__init__`).

* **Pure Interface:** Defines behavioral signatures without managing state attributes or concrete logic.
* **Hybrid Abstract Class:** Combines shared state initialization (`__init__`), concrete helper methods, and abstract hooks.

```python
class Superhero(ABC):
    """Pure interface: strict behavioral contract for superhero entities."""

    @abstractmethod
    def fly(self) -> str:
        pass

    @abstractmethod
    def use_power(self) -> str:
        pass


class Superman(Superhero):
    def fly(self) -> str:
        return "Up, up and away!"

    def use_power(self) -> str:
        return "Using heat vision"


class WonderWoman(Superhero):
    def fly(self) -> str:
        return "Soaring through the clouds!"

    def use_power(self) -> str:
        return "Using lasso of truth"


superman = Superman()
wonder_woman = WonderWoman()

# Verifying polymorphic interface conformance
print(isinstance(superman, Superhero))      # Output: True
print(isinstance(wonder_woman, Superhero))  # Output: True
```

---

### Hybrid Abstract Base Classes: Shared State with Abstract Hooks

In complex domain architectures, base classes often manage shared state attributes while delegating concrete domain actions down to specialized subclasses.

```python
class Superpower(ABC):
    """Hybrid abstract base class combining concrete state with abstract lifecycles."""

    def __init__(self, name: str, power_level: int) -> None:
        self.name: str = name
        self.power_level: int = power_level
        self.is_active: bool = False

    def get_power_level(self) -> int:
        """Concrete method inherited across all implementations."""
        return self.power_level

    @abstractmethod
    def activate(self) -> None:
        pass

    @abstractmethod
    def deactivate(self) -> None:
        pass


class LaserBeam(Superpower):
    def activate(self) -> None:
        self.is_active = True
        print(f"{self.name} activated!")

    def deactivate(self) -> None:
        self.is_active = False
        print(f"{self.name} deactivated!")


class SuperStrength(Superpower):
    def activate(self) -> None:
        self.is_active = True
        print(f"{self.name} activated!")

    def deactivate(self) -> None:
        self.is_active = False
        print(f"{self.name} deactivated!")


laser_beam = LaserBeam("Laser Beam", 10)
super_strength = SuperStrength("Super Strength", 8)

print(laser_beam.get_power_level())      # Output: 10
print(super_strength.get_power_level())  # Output: 8

laser_beam.activate()        # Output: Laser Beam activated!
super_strength.activate()    # Output: Super Strength activated!
laser_beam.deactivate()      # Output: Laser Beam deactivated!
super_strength.deactivate()  # Output: Super Strength deactivated!
```

---

### Interface Segregation Principle (ISP) with Multiple Interfaces

The **Interface Segregation Principle** (the "I" in SOLID) states that callers should never be forced to depend on methods they do not consume. Python addresses this by composing classes from multiple fine-grained abstract interfaces.

```python
class Attacker(ABC):
    @abstractmethod
    def attack(self) -> None:
        pass


class Defender(ABC):
    @abstractmethod
    def defend(self) -> None:
        pass


class Healer(ABC):
    @abstractmethod
    def heal(self) -> None:
        pass


class Knight(Attacker, Defender, Healer):
    """Concrete domain model satisfying multiple segregated interfaces."""

    def __init__(self, name: str) -> None:
        self.name: str = name

    def attack(self) -> None:
        print(f"{self.name} attacks with sword!")

    def defend(self) -> None:
        print(f"{self.name} raises shield!")

    def heal(self) -> None:
        print(f"{self.name} uses healing potion!")


hero = Knight("Sir Galahad")
hero.attack()  # Output: Sir Galahad attacks with sword!
hero.defend()  # Output: Sir Galahad raises shield!
hero.heal()    # Output: Sir Galahad uses healing potion!
```

---

### Architectural Comparison: Abstraction, Encapsulation, and Interfaces

| Dimension | Abstraction | Encapsulation | Hybrid Abstract Class | Pure Interface |
| :--- | :--- | :--- | :--- | :--- |
| **System Level** | High-level system design | Internal component implementation | Partial specialization hierarchy | Behavioral decoupling contract |
| **Python Mechanism** | Public APIs, Abstract classes (`ABC`) | Name conventions (`_`, `__`), `@property` | `class X(ABC):` mixing concrete and abstract methods | `class X(ABC):` exclusively `@abstractmethod` signatures |
| **State Handling** | Conceals complex representations | Bundles and validates attributes | Defines common `__init__` attributes |
| **Primary Goal** | Minimize caller cognitive overhead | Prevent invalid internal state transitions | Eliminate boilerplate across related subclasses | Enforce architectural consistency across disparate systemsA |