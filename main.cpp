#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <openssl/evp.h>
#include <string>
#include "./headers/encrypt.h"
#include "./headers/decrypt.h"

#include <limits> //New Library

using namespace std;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main()
{

    system("cls");

    setColor(11); // Light Cyan
    cout << "   /$$$$$$                                  /$$                              /$$$$$$                                      /$$" << endl;
    cout << "  /$$__  $$                                | $$                             /$$__  $$                                    | $$" << endl;
    cout << " | $$  \\ $$ /$$   /$$  /$$$$$$  /$$$$$$$  /$$$$$$   /$$   /$$ /$$$$$$/$$$$ | $$  \\__/ /$$   /$$  /$$$$$$   /$$$$$$   /$$$$$$$" << endl;
    cout << " | $$  | $$| $$  | $$ |____  $$| $$__  $$|_  $$_/  | $$  | $$| $$_  $$_  $$| $$ /$$$$| $$  | $$ |____  $$ /$$__  $$ /$$__  $$" << endl;
    cout << " | $$  | $$| $$  | $$  /$$$$$$$| $$  \\ $$  | $$    | $$  | $$| $$ \\ $$ \\ $$| $$|_  $$| $$  | $$  /$$$$$$$| $$  \\__/| $$  | $$" << endl;
    cout << " | $$/$$ $$| $$  | $$ /$$__  $$| $$  | $$  | $$ /$$| $$  | $$| $$ | $$ | $$| $$  \\ $$| $$  | $$ /$$__  $$| $$      | $$  | $$" << endl;
    cout << " |  $$$$$$/|  $$$$$$/|  $$$$$$$| $$  | $$  |  $$$$/|  $$$$$$/| $$ | $$ | $$|  $$$$$$/|  $$$$$$/|  $$$$$$$| $$      |  $$$$$$$" << endl;
    cout << "  \\____ $$$ \\______/  \\_______/|__//  |__/   \\___/   \\______/ |__/ |__/ |__/ \\______/  \\______/  \\_______/|__/       \\_______/" << endl;
    cout << "       \\__/                                                                                                                  " << endl;

    cout << " [---]-------------------------------------------------------------------------------------------------------------------[---]" << endl;
    
    setColor(3); // Light Cyan
    cout << setw(70) << "[ QuantumGuard ]" << endl;
    setColor(11); // Light Cyan
    cout << setw(50) << "Created By: ";
    
    setColor(14); // Yellow
    cout << "Muhammad Talha, Bilal Khan, Wasi Shah" << endl;
    setColor(11); // Light Cyan
    
    cout << setw(64) << "Version: ";
    setColor(4); // Light Cyan
    cout << "1.0.0: " << endl;
    
    setColor(11); // Light Cyan
    cout << setw(60) << "Codename: ";
    setColor(14); // Light Cyan
    cout << "Genesis";
    setColor(15); // Light Cyan
    cout << "Guard" << endl;
    
    setColor(2); // Light Cyan
    setColor(2); // Light Cyan
    cout << setw(100) << "Welcome to QuantumGuard! Your system's File security is our top priority." << endl;
    cout << setw(85) << "The one stop shop for all your File Encryption" << endl;
    
    setColor(15); // Light Cyan
    cout<<"Select from Menu\n"<<endl;
    cout<<"[1] Encrypt File"<<endl;
    cout<<"[2] Decrypt File"<<endl;
    cout<<"[3] View Logs"<<endl;
    cout<<"[4] Credits"<<endl;

    cout<<"\n[9] Exit Application"<<endl;

    int choice;
    cout<<"\nEnter your choice: ";
    cin>>choice;

    switch (choice)
    {
        case 1:{

            string inputPath;
            string outputPath;
            string password;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout<<"Enter the File Path (File Exists in ./testFile directory): "<<endl;
            getline(cin, inputPath);
            // cin.ignore();

            cout<<"Enter Output Path: "<<endl;
            getline(cin, outputPath);
            // cin.ignore();

            cout<<"Enter Password"<<endl;

            char pass;
            int passMaxLen = 15;
            
            for(int i = 0; i < passMaxLen; i++){

                pass = getch();

                if (pass == '\r'){
                    break;
                }
                if (pass == '\b'){
                    if (i > 0){
                        i--;
                        password.pop_back();
                        cout << "\b \b";
                    }
                }
                else{
                    password += pass;
                    cout << '*'; // hiding characters
                }
            }

            cout<<endl;
            // cin.ignore();

            bool ok = encryptFile(inputPath, outputPath, password);

            if (ok){
                cout<<"Encrypted Successfully";
            }
            else
            {
                cout<<"Not Encrypted";
            }
            
            
            break;
        }
        case 2:{

            string inputPath;
            string outputPath;
            string password;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout<<"Enter the File to Decrypt (File Exists in ./EncryptedFiles directory): "<<endl;
            getline(cin, inputPath);
            // cin.ignore();

            cout<<"Enter Output Path: "<<endl;
            getline(cin, outputPath);
            // cin.ignore();

            cout<<"Enter Password"<<endl;

            char pass;
            int passMaxLen = 15;
            
            for(int i = 0; i < passMaxLen; i++){

                pass = getch();

                if (pass == '\r'){
                    break;
                }
                if (pass == '\b'){
                    if (i > 0){
                        i--;
                        password.pop_back();
                        cout << "\b \b";
                    }
                }
                else{
                    password += pass;
                    cout << '*'; // hiding characters
                }
            }

            cout<<endl;
            // cin.ignore();

            bool ok = decryptFile(inputPath, outputPath, password);

            if (ok){
                cout<<"Decrypted Successfully";
            }
            else
            {
                cout<<"Not Encrypted";
            }

            break;
        }
        case 3:
            system("viewlogs.exe");
            break;

        case 9:
            exit(0);
        default:
            cout << "Invalid option. Please try again." << endl;
    }
    
    getchar();

    return 0;
}