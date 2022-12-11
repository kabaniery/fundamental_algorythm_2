#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int strCopy(char ishodStr[], char itogStr[], int len, int startIndex, int endIndex) {
    for (int i = 0; i < len; ++i) {
        itogStr[i+endIndex] = ishodStr[i+startIndex];
    }
    return 0;
}
char* fileToStr(FILE *f) {
    char* result = (char*)malloc(sizeof(char)*2), *strTemp;
    if (!result) {
        fprintf(stderr, "Can't alloc memory");\
        return NULL;
    }
    result[1] = '\0';
    char c;
    int i = 0;
    while ((c = fgetc(f)) != EOF && c != '\0')
    {
        if (f == stdin && c == '\n') {
            break;
        }
        if (result[i] == '\0') {
            strTemp = realloc(result, sizeof(char)*(i+1)*2);
            if (!strTemp) {
                fprintf(stderr, "Can't alloc memory");
                free(result);
                return NULL;
            }
            result = strTemp;
            result[i*2+1] = '\0';
        }
        result[i] = c;
        i++;
    }
    if (result[i] != '\0') {
        result = realloc(result, sizeof(char)*(i+1));
        result[i] = '\0';
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid count of arguments\n");
        return -3;
    }
    if (strcmp(argv[2], "-l") == 0) {
        //Подсчёт длины строки
        int i = 0;
        while(argv[1][i] != '\0') {
            i++;
        }
        printf("%d\n", i);
    } else if (strcmp(argv[2], "-r") == 0) {
        //реверс строки
        int i = 0, i2 = 0, len = 2;
        char *str = (char*)malloc(sizeof(char) * len), *strTemp;
        str[1] = '\0';
        if (strlen(argv[1]) == 1) {
            return 0; //ну мало ли, впихнули пустую строку как-то
        }
        while (argv[1][i] != '\0') {
            if (i2 < 0) {
                strTemp = (char*)malloc(sizeof(char)*len*2);
                strCopy(str, strTemp, len, 0, len);
                len *= 2;
                free(str);
                str = strTemp;
                i2 = len/2-1;
            }
            str[i2] = argv[1][i];
            i2--;
            i++;
        }
        strTemp = (char*)(malloc(sizeof(char)*(i+1)));
        strCopy(str, strTemp, 5, i2+1, 0);
        printf("%s\n", strTemp);
    } else if (strcmp(argv[2], "-u") == 0) {
        //элемент нечетной позиции в верхний регистр
        char* str = (char*)malloc(sizeof(char) * (strlen(argv[1] + 1)));
        if (!str) {
            fprintf(stderr, "Can't create file");
            return -1;
        }
        for (int i = 0; argv[1][i] != '\0'; ++i) {
            if (i%2 == 0 && argv[1][i] >= 'a' && argv[1][i] <= 'z') {
                str[i] = argv[1][i] - 32;
            } else {
                str[i] = argv[1][i];
            }
        }
    } else if (strcmp(argv[2], "-n") == 0) {
        //вначале цифры, затем буквы, затем прочее
        char* digits = (char*)malloc(sizeof(char) * 2), *letters = (char*)malloc(sizeof(char) * 2), *other = (char*)malloc(sizeof(char) * 2), *strTemp;
        int i1 = 0, i2 = 0, i3 = 0;
        char c;
        if (!digits || !letters || !other) {
            fprintf(stderr, "Can't alloc memory");
            return -1;
        }
        digits[1] = '\0';
        letters[1] = '\0';
        other[1] = '\0';
        for (int i = 0; (c = argv[1][i]) != '\0'; i++)
        {
            if (c >= '0' && c <= '9') {
                if (digits[i1] == '\0') {
                    strTemp = realloc(digits, sizeof(char)*(i1+1)*2);
                    if (!strTemp) {
                        fprintf(stderr, "Can't alloc memory");
                        free(digits);
                        free(letters);
                        free(other);
                        return -1;
                    }
                    digits = strTemp;
                    digits[i1*2+1] = '\0';
                }
                digits[i1] = c;
                i1++;
                } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    if (letters[i2] == '\0') {
                        strTemp = realloc(letters, sizeof(char)*(i2+1)*2);
                        if (!strTemp) {
                            fprintf(stderr, "Can't alloc memory");
                            free(digits);
                            free(letters);
                            free(other);
                            return -1;
                        }
                        letters = strTemp;
                        letters[i2*2+1] = '\0';
                    }
                    letters[i2] = c;
                    i2++;
                } else {
                    if (other[i3] == '\0') {
                        strTemp = realloc(other, sizeof(char)*(i3+1)*2);
                        if (!strTemp) {
                            fprintf(stderr, "Can't alloc memory");
                            free(digits);
                            free(letters);
                            free(other);
                            return -1;
                        }
                        other = strTemp;
                        other[i2*2+1] = '\0';
                    }
                    other[i3] = c;
                    i3++;
                }
            }
        char* newStr = malloc(sizeof(char)*(i1+i2+i3+1));
        if (!newStr) {
            fprintf(stderr, "Can't alloc memory");
            free(digits);
            free(letters);
            free(other);
            return -1;
        }
        strCopy(digits, newStr, i1, 0, 0);
        strCopy(letters, newStr, i2, 0, i1);
        strCopy(other, newStr, i3, 0, i1+i2);
        printf("%s\n", newStr);
        free(digits);
        free(letters);
        free(other);
        free(newStr);
        
    } else if (strcmp(argv[2], "-c") == 0) {
        //склеить строки в третьем аргументе
        char* newString = fileToStr(stdin);
        if (!newString) {
            return -1;
        }
        char* result = malloc(sizeof(char)*(strlen(argv[1])+strlen(newString)+1));
        strCopy(argv[1], result, strlen(result), 0, 0);
        strCopy(newString, result, strlen(newString), 0, strlen(result));
        printf("%s", result);
        free(newString);
        free(result);
    } else {
        printf("Invalid flag\n");
        return -2;
    }

    return 0;
}
