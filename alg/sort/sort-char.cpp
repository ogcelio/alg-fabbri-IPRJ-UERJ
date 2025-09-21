// Ricardo Fabbri
// 2024-09-12

#include "sort-char.h"
#include <iostream>
#include <cstring>

void sort_char(char *v) {
    int n = strlen(v);
    if (n <= 1) return;

    int count[256] = {0};

    for (int i = 0; i < n; i++) {
        count[(unsigned char)v[i]]++;
    }

    int index = 0;
    for (int i = 0; i < 256; i++) {
        if (count[i] > 0) {
            memset(v + index, i, count[i]);
            index += count[i];
        }
    }
}
