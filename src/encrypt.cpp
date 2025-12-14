#include "../headers/encrypt.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <fstream>
#include <vector>

using namespace std;

bool encryptFile(const string &inputPath, const string &outputPath, const string &password) {
    ifstream in(inputPath, ios::binary);
    if (!in.is_open()) return false;

    vector<unsigned char> plaintext(
        (istreambuf_iterator<char>(in)),
        istreambuf_iterator<char>()
    );
    in.close();

    unsigned char salt[16];
    unsigned char key[32];
    unsigned char iv[16];

    RAND_bytes(salt, sizeof(salt));

    PKCS5_PBKDF2_HMAC(
        password.c_str(), password.length(),
        salt, sizeof(salt),
        50000,
        EVP_sha256(),
        sizeof(key), key
    );

    RAND_bytes(iv, sizeof(iv));

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    vector<unsigned char> ciphertext(plaintext.size() + 32);
    int len, ciphertextLen;

    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size());
    ciphertextLen = len;

    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertextLen += len;

    EVP_CIPHER_CTX_free(ctx);

    ofstream out(outputPath, ios::binary);
    if (!out.is_open()) return false;

    out.write("Salted__", 8);
    out.write((char*)salt, 16);
    out.write((char*)iv, 16);
    out.write((char*)ciphertext.data(), ciphertextLen);
    out.close();

    return true;
}
