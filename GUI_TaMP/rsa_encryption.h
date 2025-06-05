#ifndef RSA_ENCRYPTION_H
#define RSA_ENCRYPTION_H

class RsaEncryption {
public:
    static int encrypt(int message, int e, int n);
    static int decrypt(int cipherText, int d, int n);

private:
    static int modExp(int base, int exp, int mod);
};

#endif



