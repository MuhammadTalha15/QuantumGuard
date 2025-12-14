#include "../headers/decrypt.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <fstream>
#include <vector>
#include <iostream>

bool decryptFile(const std::string &inputPath,
                 const std::string &outputPath,
                 const std::string &password)
{
    std::ifstream in(inputPath, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Error: Cannot open encrypted file\n";
        return false;
    }

    char header[8];
    in.read(header, 8);
    if (std::string(header, 8) != "Salted__") {
        std::cerr << "Invalid encrypted file format\n";
        return false;
    }

    unsigned char salt[16];
    unsigned char iv[16];
    in.read(reinterpret_cast<char*>(salt), 16);
    in.read(reinterpret_cast<char*>(iv), 16);

    std::vector<unsigned char> ciphertext(
        (std::istreambuf_iterator<char>(in)),
         std::istreambuf_iterator<char>()
    );
    in.close();

    unsigned char key[32];
    PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                      salt, sizeof(salt), 50000,
                      EVP_sha256(), 32, key);

    std::vector<unsigned char> plaintext(ciphertext.size());
    int len, plaintextLen;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    EVP_DecryptUpdate(ctx, plaintext.data(), &len,
                      ciphertext.data(), ciphertext.size());
    plaintextLen = len;

    if (!EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len)) {
        std::cerr << "Wrong password or corrupted file\n";
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    plaintextLen += len;
    EVP_CIPHER_CTX_free(ctx);

    std::ofstream out(outputPath, std::ios::binary);
    out.write(reinterpret_cast<char*>(plaintext.data()), plaintextLen);
    out.close();

    return true;
}
