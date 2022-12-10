#include <stdarg.h>
#include <stdio.h>

typedef struct point{
    double x;
    double y;
}point;

typedef struct line{
    double x;
    double y;
}line;

int isOpenFigure(int n, ...) {
    va_list coords;
    va_start(coords, n);
    point* points = (point*)malloc(sizeof(point)*n);
    int key = 0, index = 0;
    if (!points) {
        fprintf(stderr, "Memory error");
        return 0;
    }
    for (int i = 0; i < n*2; i++)
    {
        if (key == 0) {
            points[index].x = va_arg(coords, double);
            key = 1;
        } else {
            points[index].y = va_arg(coords, double);
            key = 0;
            index++;
        }
    }
    va_end(coords);
    line* lines = (line*)(malloc(sizeof(line)*n));
    if (!lines) {
        fprintf(stderr, "Memory error");
        return 0;
    }
    for (int i = 0; i < n-1; i++)
    {
        lines[i].x = points[i+1].x - points[i].x;
        lines[i].y = points[i+1].y - points[i].y;
    }
    lines[n-1].x = points[0].x - points[n-1].x;
    lines[n-1].y = points[0].x - points[n-1].y;
    int naprav = 0, temp;
    for (int i = 0; i < n-1; i++)
    {
        temp = lines[i].x * lines[i+1].y - lines[i+1].x * lines[i].y;
        if (naprav == 0) {
            if (temp > 0) {
                naprav = 1;
            } else if (temp < 0) {
                naprav = -1;
            }
        } else {
            if (temp > 0 && naprav == -1) {
                return 0;
            } else if (temp < 0 && naprav == 1) {
                return 0;
            }
        }
    }
    {
        temp = lines[n-1].x * lines[0].y - lines[0].x * lines[n-1].y;
        if (naprav == 0) {
            if (temp > 0) {
                naprav = 1;
            } else if (temp < 0) {
                naprav = -1;
            }
        } else {
            if (temp > 0 && naprav == -1) {
                return 0;
            } else if (temp < 0 && naprav == 1) {
                return 0;
            }
        }
    }
    if (naprav == 0) {
        return 0;
    }
    return 1;
}

double valueOfPolinom(double value, double degree, ...) {
    va_list koef;
    va_start(koef, degree);
    double result = 0;
    for (int i = 0; i < degree+1; i++)
    {
        result = result * value + va_arg(koef, double);
    }
    va_end(koef);
    return result;
}