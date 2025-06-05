#include "rsa_encryption.h"

int RsaEncryption::encrypt(int message, int e, int n) {
    return modExp(message, e, n);
}

int RsaEncryption::decrypt(int cipherText, int d, int n) {
    return modExp(cipherText, d, n);
}

int RsaEncryption::modExp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
