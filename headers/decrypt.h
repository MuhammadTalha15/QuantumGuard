#ifndef DECRYPT_H
#define DECRYPT_H

#include <string>

bool decryptFile(const std::string &inputPath,
                 const std::string &outputPath,
                 const std::string &password);

#endif
