#include <stdint.h>
#include <stdio.h>

// Proper macro
#define SQUARE(x)   ((x) * (x))

// Bad macro
#define BAD_SQUARE(x)   x*x

// ?
#define INCREMENT(x)   ((x) + 1)

static inline int square_fn(int x)
{
    return x * x;
}

static inline int min_fn(int a, int b)
{
    return (a < b) ? a : b;
}

int main() {
    int a = 5;
    int b = 2 + 3;
    int i = 1;
    
    printf("SQUARE(5): %d \r\n", SQUARE(a)); // ((5) * (5)) = 25
    printf("SQUARE(2+3): %d \r\n", SQUARE(b)); // ((2+3) * (2+3)) = 25

    printf("BAD_SQUARE(5): %d\r\n", SQUARE(a)); // 5 * 5 = 25
    printf("BAD_SQUARE(2+3): %d \r\n", BAD_SQUARE(b)); //2+3 * 2+3 = 11

    printf("INCREMENT(5): %d \r\n", INCREMENT(a)); // 5 + 1 = 6
    printf("INCREMENT(5++): %d \r\n", INCREMENT(a++)); // ?

    printf("square_fn(3): %d \r\n", square_fn(3));

    printf("Min using macro %d \r\n", ((a) < (b)) ? (a) : (b));
    printf("Min using function %d \r\n", min_fn(a, b));


    return 0;
}
