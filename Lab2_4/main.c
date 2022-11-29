#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

double getMediumGeometry(int n, ...) {
    if (n == 0) {
        return 0;
    }
    double result = 0;
    va_list values;
    va_start(values, n);
    for(int i = 0; i < n; i++) {
        result *= va_arg(values, double);
    }
    va_end(values);
    return pow(result, 1/n);
}

int getRecursivePow(double value, int pok, double* sum) {
    if (sum == NULL) {
        sum = malloc(sizeof(double));
        if (sum == NULL) {
            return -1;
        }
    }
    *sum = 1;
    if (pok == 0) {
        *sum = 1.0;
        return 0;
    }
    if (pok > 1) {
        *sum *= value;
        getRecursivePow(value, pok - 1, sum);
    } else if (pok == 1) {
        *sum *= value;
    } else if (pok < -1) {
        *sum /= value;
        getRecursivePow(value, pok + 1, sum);
    } else if (pok == -1) {
        *sum /= value;
    }
    return 0;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
