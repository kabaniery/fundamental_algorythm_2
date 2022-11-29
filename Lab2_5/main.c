#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int generateRandomMass(int mass[], int count, int minimumValue, int maximumValue, int seedPlus) {
    //Пусть и простая, но зато своя цаца https://foxford.ru/wiki/informatika/generatsiya-psevdosluchaynyh-chisel
    long long seed;
    time(&seed);
    seed += seedPlus;
    for (int i = 0; i < count; ++i) {
        seed = 69069LU*seed + 5LU;
        mass[i] = (int)(seed%(maximumValue-minimumValue)) + minimumValue;
    }
    return 0;
}

int strToInt(char str[]) {
    int isNegative = 0, i = 0;
    if (str[0] == '-') {
        isNegative = 1;
        i++;
    }
    int result = 0;
    for (; i < strlen(str); i++) {
        if ((int)str[i] >= 48 && (int)str[i] <= 57) {
            result = result * 10 + (str[i] - 48);
        } else {
            fprintf(stderr, "Invalid number\n");
            return -1;
        }
    }
    if (isNegative == 1) {
        result *= -1;
    }
    return result;
}

int replaceMinMax(int *min, int *max) {
    int temp = *min;
    *min = *max;
    *max = temp;
    return 0;
}

int search(int elem, long* mass, int len) {
    for (int i = 0; i < len; ++i) {
        if (elem == mass[i]) {
            return i;
        }
    }
    return -1;
}

int printMassLong(long mass[], int len)
{
    for (int i = 0; i < len; ++i) {
        printf("%ld ", mass[i]);
    }
    printf("\n");
    return 0;
}

int printMassive(int mass[], int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d ", mass[i]);
    }
    printf("\n");
    return 0;
}

int main(int argc, char* argv[]) {
    int count = strToInt(argv[3]);
    if (count < 1) {
        fprintf(stderr, "Invalid len of mass\n");
        return 0;
    }
    int *mass = malloc(sizeof(int)*count);
    generateRandomMass(mass, count, strToInt(argv[1]), strToInt(argv[2]), 0);
    printf("What do you want?: 1)Replace min and max element in massive; 2)Get new massive with unique elements of old massive\n");
    char c = fgetc(stdin);
    if (c == '1') {
        int minElem = mass[0], minIndex = 0, maxElem = mass[0], maxIndex = 0;
        for (int i = 1; i < count; ++i) {
            if (mass[i] < minElem) {
                minElem = mass[i];
                minIndex = i;
            }
            if (mass[i] > maxElem) {
                maxElem = mass[i];
                maxIndex = i;
            }
        }
        replaceMinMax(&mass[minIndex], &mass[maxIndex]);
        printMassive(mass, count);
    } else if (c == '2') {
        long *mass2 = malloc(sizeof(long)*count);
        for (int i = 0; i < count; ++i) {
            mass2[i] = strToInt(argv[1]) - 1;
        }
        int index = 0;
        for (int i = 0; i < count; ++i) {
            if (search(mass[i], mass2, count) == -1) {
                mass2[index] = mass[i];
                index++;
            }
        }
        mass2 = realloc(mass2, sizeof(long) * (index+1));
        printMassLong(mass2, index+1);
        free(mass2);
    } else {
        printf("Invalid command\n");
    }
    free(mass);
    return 0;
}
