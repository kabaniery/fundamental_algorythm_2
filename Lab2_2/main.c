#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int strCpy(char ishodStr[], char itogStr[], int len) {
    for (int i = 0; i < len/2; ++i) {
        printf("%c\n", ishodStr[i]);
        itogStr[len/2+i] = ishodStr[i];
    }
    return 0;
}

int strCopy(char ishodStr[], char itogStr[], int len, int startIndex, int endIndex) {
    for (int i = 0; i < len; ++i) {
        itogStr[i+endIndex] = ishodStr[i+startIndex];
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {//доделать кол-во аргументов
        printf("Invalid count of arguments\n");
        return -1;
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

    } else if (strcmp(argv[2], "-n") == 0) {
        //вначале цифры, затем буквы, затем прочее
    } else if (strcmp(argv[2], "-c") == 0) {
        //склеить строки в третьем аргументе
    } else {
        printf("Invalid flag\n");
        return -1;
    }

    return 0;
}
