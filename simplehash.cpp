#include "simplehash.h"

unsigned long long SimpleHash::hash(const char* input) {
    unsigned long long hash = 0;
    int i = 0;
    while (input[i] != '\0') {
        hash = (hash * 31) + input[i];
        i++;
    }
    return hash;
}
