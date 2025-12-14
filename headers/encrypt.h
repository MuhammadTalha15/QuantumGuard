#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <string>

using namespace std;

bool encryptFile(const string &inputPath,
                 const string &outputPath,
                 const string &password);

#endif
