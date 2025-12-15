<h1> Pseudocode for Program</h1> 

```
START
Display menu options
1. Encrypt File
2. Decrypt File

Read user choice

IF choice is Encrypt
    Ask user for input file path
    Ask user for output file path
    Ask user for password
    Read text file
    Encrypt file content using AES
    Save encrypted data to output file
    Display success message

ELSE IF choice is Decrypt
    Ask user for input file path
    Ask user for output file path
    Ask user for password
    Read encrypted file
    Decrypt content using AES
    Save decrypted data to output file
    Display success message

ELSE
    Display invalid choice message

END

```