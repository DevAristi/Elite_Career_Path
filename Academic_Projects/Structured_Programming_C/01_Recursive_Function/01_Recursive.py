from math import factorial

def my_factorial(n):
    if n > 1:
        return n * my_factorial(n - 1)
    else:
        return 1

print(factorial(10))
print(my_factorial(10))