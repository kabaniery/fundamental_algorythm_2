#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
void qsort (int mass[], int l, int r) {
    //Осознать алгоритм, иначе Ирбитский трахнет
    int left = l, right = r, piv = mass[(left+right)/2]; //от слова пиво
    while (left <= right) {
        while (mass[left] < piv) { left++;}
        while (mass[right] > piv) {right--;}
        if (l <= r) {
            int temp = left;
            left = right;
            right = temp;
        }
    }
    if (l < right) { qsort(mass, l, right); }
    if (r > left) { qsort(mass, left, r); }
}
*/

int generateRandomMass(int mass[], int count, int minimumValue, int maximumValue, int seedPlus) {
    //Пусть и простая, но зато своя цаца https://foxford.ru/wiki/informatika/generatsiya-psevdosluchaynyh-chisel
    unsigned long long seed;
    time(&seed);
    seed += seedPlus;
    for (int i = 0; i < count; ++i) {
        seed = 69069LU*seed + 5LU;
        mass[i] = (int)(seed%(maximumValue-minimumValue)) + minimumValue;
    }
    return 0;
}

int getStrToInt(char str[]) {
    if (strlen(str) == 0) {
        fprintf(stderr, "String is empty, how do you do this?\n");
        return 0;
    }
    int result = 0, isNegative = 0;
    if (str[0] == '-') {
        isNegative = 1;
    }
    for (int i = 0 + isNegative; i < strlen(str); ++i) {
        if (str[i] >= 48 && str[i] <= 57) {
            result = result * 10 + str[i] - '0';
        } else {
            fprintf(stderr, "String isn't a whole number\n");
            return 0;
        }
    }
    if (isNegative) {
        result = result * -1;
    }
    return result;
}

int abs(int i) {
    if (i < 0) {
        return -1*i;
    } else {
        return i;
    }
}


int* nearPlusToMass(int massA[], int lenA, int massB[], int lenB) {
    int *massC = malloc(sizeof(int)*lenA);
    //Ситуативно закинуть массив b на сортировку
    //P.s нафиг не нужно, ибо сложность выше по итогу
    int minimumDiff;
    if (lenA <= 0 || lenB <= 0) {
        return NULL;
    }
    for (int i = 0; i < lenA; ++i) {
        minimumDiff = massA[i] - massB[0];
        for (int j = 1; j < lenB; ++j) {
            if (abs(massA[i] - massB[j]) < abs(minimumDiff)) {
                minimumDiff = massA[i] - massB[j];
            }
        }
        massC[i] = 2 * massA[i] + minimumDiff;
    }
    return massC;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid count of arguments\n");
        return -1;
    }
    int len1 = getStrToInt(argv[1]), len2 = getStrToInt(argv[2]);
    int *mass1 = malloc(sizeof(int) * len1);
    int *mass2 = malloc(sizeof(int) * len2);
    generateRandomMass(mass1, len1, -1000, 1000, 0);
    generateRandomMass(mass2, len2, -1000, 1000, 0);
    int *mass3 = nearPlusToMass(mass1, len1, mass2, len2);
    return 0;
}
