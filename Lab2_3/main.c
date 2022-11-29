#include <stdio.h>
#include <limits.h>
#include <math.h>

double roundF(double value, int l) {
    double s = 1.0;
    int t = 1;
    for (int i = 0; i < l; ++i) {
        s /= 10.0;
        t *= 10;
    }
    return ((double)(int)(value / s))/((double)t);
    //Бля, лишь бы работало
}

double stepen(double a, int b) {

}

double findEByLim(int l) {
    unsigned long long n = 100000000;
    double value = 1.0 + (1.0 / (double)n), lastResult = value, result = value;
    for (unsigned int saveIterator = 0; saveIterator < n; ++saveIterator) {
        result *= value;

        lastResult = result;
    }
    return roundF(result, l);
}

double findEBySum(int l) {
    double result = 1.0, lastResult = result, semiValue = 1.0;
    for(unsigned long long n = 1; n < ULONG_LONG_MAX; ++n) {
        semiValue /= (double) n;
        result += semiValue;
        if (roundF(result - lastResult, l) == 0) {
            break;
        }
        lastResult = result;
    }
    return roundF(result, l);
}

double findEByEquation(int l) {
    return roundF(exp(1.0), l);
}

double findPiByLim(int l) {
    unsigned long long n = 15000000;//Больше не надо
    double result = 4; //(2^1*1!)^4 / 1((2)!)^2
    for (unsigned long long i = 2; i <= n; ++i) {
        result *= (double)(4*i*(i-1)) /(double)((2 * i - 1) * (2 * i - 1));
    }
    return roundF(result, l);
}

double findPiBySum(int l) {
    unsigned long long count = 650000;
    double result = 0;
    double iter = 1;
    for (int i = 1; i < count; ++i) {
        result += 4*iter/(2*i - 1);
        iter *= -1;
    }
    return roundF(result, l);
}

double findPiByEquation(int l) {
    return roundF(acos(-1), l);
}

double findSqrtByLim(int l) {
    double result = -0.5;
    unsigned long long n = 650000;
    for (int i = 0; i < n; ++i) {
        result = result - ((result*result) / 2) + 1;
    }
    return roundF(result, l);
}

double findSqrtBySum(int l) {
    double result = 1.0;
    unsigned long long n = 650000;
    for (int i = 2; i < n; ++i) {
        result *= pow(2, pow(2, -1*i)); //TODO: Сделать возведение в степень через свою функцию
    }
    return roundF(result, l);
}

double findSqrtByEquation(int l) {
    return roundF(sqrt(2), l);
}

double findYByLim(int l) {
    unsigned long long n = 6500000;
    double result = 0;
    unsigned long long sochet = n;
    int del = -1;
    unsigned long long fact = 1;
    for (int i = 1; i < n; ++i) {
        result += ((double)sochet*del*log((double)fact))/i;
        sochet *= (n-i-1) / (i+1);
        del *= -1;
        fact *=(i+1);
    }
    return roundF(result, l);
}
//TODO: узнать способ создания функции для 2 последних фактов

int main() {
    printf("%f", log(findEByLim(7)));
    return 0;
}
