#include <stdio.h>
long my_factorial(int n) {
    if (n > 1) {
        return n * my_factorial(n - 1);
    } else {
        return 1;
    }
}

int main() {
    int target = 10;
    long result = my_factorial(target);
    printf("Recursive Result (%d!): %ld\n", target, result);

    return 0;
}