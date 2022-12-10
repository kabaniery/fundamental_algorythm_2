#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int searchInFile(char* subStr, FILE *f) {
    char c;
    int index = 0;
    while((c = fgetc(f)) != EOF) {
        if (subStr[index] == '\0') {
            return 1;
        }
        if (subStr[index] == c) {
            index++;
        } else {
            index = 0;
        }
    }
    return 0;
}

int searchInFiles(char* subStr, int count, ...) {
    va_list paths;
    FILE *f;
    va_start(paths, count);
    for (int i = 0; i < count; i++)
    {
        if (f = fopen(va_arg(paths, char*), "r") == NULL) {
            fprintf(stderr, "Can't open file\n");
            va_end(paths);
            return 0;
        }
        if (searchInFile(subStr, f) == 1) {
            va_end(paths);
            fclose(f);
            return 1;
        }
        va_end(paths);
        fclose(f);
    }
    return 0;
}
