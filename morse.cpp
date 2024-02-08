#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

// Morse code mapping
map<char, string> morseCodeMap;

// Function to initialize the Morse code mapping
void initializeMorseCodeMap()
{
    morseCodeMap.insert(make_pair('A', ".-"));
    morseCodeMap.insert(make_pair('B', "-..."));
    morseCodeMap.insert(make_pair('C', "-.-."));
    morseCodeMap.insert(make_pair('D', "-.."));
    morseCodeMap.insert(make_pair('E', "."));
    morseCodeMap.insert(make_pair('F', "..-."));
    morseCodeMap.insert(make_pair('G', "--."));
    morseCodeMap.insert(make_pair('H', "...."));
    morseCodeMap.insert(make_pair('I', ".."));
    morseCodeMap.insert(make_pair('J', ".---"));
    morseCodeMap.insert(make_pair('K', "-.-"));
    morseCodeMap.insert(make_pair('L', ".-.."));
    morseCodeMap.insert(make_pair('M', "--"));
    morseCodeMap.insert(make_pair('N', "-."));
    morseCodeMap.insert(make_pair('O', "---"));
    morseCodeMap.insert(make_pair('P', ".--."));
    morseCodeMap.insert(make_pair('Q', "--.-"));
    morseCodeMap.insert(make_pair('R', ".-."));
    morseCodeMap.insert(make_pair('S', "..."));
    morseCodeMap.insert(make_pair('T', "-"));
    morseCodeMap.insert(make_pair('U', "..-"));
    morseCodeMap.insert(make_pair('V', "...-"));
    morseCodeMap.insert(make_pair('W', ".--"));
    morseCodeMap.insert(make_pair('X', "-..-"));
    morseCodeMap.insert(make_pair('Y', "-.--"));
    morseCodeMap.insert(make_pair('Z', "--.."));
    morseCodeMap.insert(make_pair('0', "-----"));
    morseCodeMap.insert(make_pair('1', ".----"));
    morseCodeMap.insert(make_pair('2', "..---"));
    morseCodeMap.insert(make_pair('3', "...--"));
    morseCodeMap.insert(make_pair('4', "....-"));
    morseCodeMap.insert(make_pair('5', "....."));
    morseCodeMap.insert(make_pair('6', "-...."));
    morseCodeMap.insert(make_pair('7', "--..."));
    morseCodeMap.insert(make_pair('8', "---.."));
    morseCodeMap.insert(make_pair('9', "----."));
    morseCodeMap.insert(make_pair(' ', "/"));
    morseCodeMap.insert(make_pair('.', ".-.-.-"));
    morseCodeMap.insert(make_pair(',', "--..--"));
    morseCodeMap.insert(make_pair('?', "..--.."));
    morseCodeMap.insert(make_pair('!', "-.-.--"));
    morseCodeMap.insert(make_pair('/', "-..-."));
    morseCodeMap.insert(make_pair('(', "-.--."));
    morseCodeMap.insert(make_pair(')', "-.--.-"));
    morseCodeMap.insert(make_pair('&', ".-..."));
    morseCodeMap.insert(make_pair(':', "---..."));
    morseCodeMap.insert(make_pair(';', "-.-.-."));
    morseCodeMap.insert(make_pair('=', "-...-"));
    morseCodeMap.insert(make_pair('+', ".-.-."));
    morseCodeMap.insert(make_pair('-', "-....-"));
    morseCodeMap.insert(make_pair('_', "..--.-"));
    morseCodeMap.insert(make_pair('"', ".-..-."));
    morseCodeMap.insert(make_pair('$', "...-..-"));
    morseCodeMap.insert(make_pair('@', ".--.-."));    
}

void runPythonScript()
{
    const char *command = "python speechtotext.py"; // Replace with your Python script filename

    std::cout << "Speak to record..." << std::endl;

    FILE *pipe = popen(command, "r");
    if (!pipe)
    {
        std::cout << "Error executing Python script." << std::endl;
        return;
    }

    char buffer[128];
    while (fgets(buffer, 128, pipe))
    {
        std::cout << buffer;
    }

    pclose(pipe);
}

// Function to encrypt a message to Morse code
string encrypt(string message)
{
    string encryptedMessage = "";
    for (size_t i = 0; i < message.length(); ++i)
    {
        char c = message[i];
        if (morseCodeMap.find(toupper(c)) != morseCodeMap.end())
        {
            encryptedMessage += morseCodeMap[toupper(c)] + " ";
        }
    }
    return encryptedMessage;
}

// Function to decrypt Morse code to a message
string decrypt(string morseCode)
{
    string decryptedMessage = "";
    string currentSymbol = "";
    for (size_t i = 0; i < morseCode.length(); ++i)
    {
        char c = morseCode[i];
        if (c == ' ' && currentSymbol != "")
        {
            for (map<char, string>::iterator it = morseCodeMap.begin(); it != morseCodeMap.end(); ++it)
            {
                if (it->second == currentSymbol)
                {
                    decryptedMessage += it->first;
                    break;
                }
            }
            currentSymbol = "";
        }
        else if (c != ' ')
        {
            currentSymbol += c;
        }
    }
    return decryptedMessage;
}

void fileDecrypt(string input, string output)
{
    ifstream inFile(input);
    ofstream outFile(output);
    string line;

    while (getline(inFile, line))
    {
        string morseLetter = "";
        for (char c : line)
        {
            if (c != ' ')
            {
                morseLetter += c;
            }
            else
            {
                for (auto i : morseCodeMap)
                {
                    if (i.second == morseLetter)
                    {
                        cout << i.first;
                        outFile << i.first;
                        break;
                    }
                }
                morseLetter = "";
            }
        }
        cout << "\n";
        outFile << "\n";
    }

    inFile.close();
    outFile.close();
}

void fileEncrypt(string input, string output)
{
    ifstream inFile(input);
    ofstream outFile(output);
    string line;

    while (getline(inFile, line))
    {
        for (char c : line)
        {
            c = toupper(c);
            string morse = morseCodeMap[c];
            outFile << morse << " ";
        }
        cout << "\n";
        outFile << "\n";
    }

    inFile.close();
    outFile.close();
}

int main()
{
    while (true)
    {
        int choice;
        string message, result;

        initializeMorseCodeMap();

        cout << "Choose an option:" << endl;
        cout << "1. Encrypt a message" << endl;
        cout << "2. Decrypt a Morse code" << endl;
        cout << "3. Exit the Programme!" << endl;
        cin >> choice;
        cout << endl;

        cin.ignore(); // Ignore newline character

        switch (choice)
        {
        case 1:
            int option;
            cout << "Choose an option:" << endl;
            cout << "1. Enter a message" << endl;
            cout << "2. Enter a file name" << endl;
            cout << "3. Record a message" << endl;

            cin >> option;
            cout << endl;

            cin.ignore(); // Ignore newline character

            if (option == 3)
            {
                runPythonScript(); // Execute Python script for speech-to-text
                string fname = "speech.txt";
                fileEncrypt(fname, "recording_encrypted.txt");
                cout << "The Encrypted Message had been stored in the file: recording_encrypted.txt" << endl;
                cout << endl;
                break;
            }
            else if (option == 1)
            {
                cout << "Enter a message to encrypt: ";
                getline(cin, message);
                result = encrypt(message);
                cout << "Encrypted message: " << result << endl;
                cout << endl;
                break;
            }
            else if (option == 2)
            {
                string filename;
                cout << "Enter the name of the file to encrypt: ";
                cin >> filename;

                fileEncrypt(filename, filename + "_encrypted.txt");
                cout << "The Encrypted Message had been stored in the file: " << filename << "encrypted.txt" << endl;
                cout << endl;

                break;
            }
            else
            {
                cout << "Invalid choice!" << endl;
                break;
            }
            break;

        case 2:

            int o;
            cout << "Choose an option:" << endl;
            cout << "1. Enter a code!" << endl;
            cout << "2. Enter a file name" << endl;

            cin >> o;
            cout << endl;

            cin.ignore(); // Ignore newline character

            switch (o)
            {
            case 1:
                cout << "Enter a Morse code to decrypt (separate symbols with spaces): ";
                cout << endl;
                getline(cin, message);
                result = decrypt(message);
                cout << "Decrypted message: " << result << endl;
                cout << endl;

                break;
            case 2:
                string filename;
                cout << "Enter the name of the file to decrypt: ";
                cin >> filename;
                cout << endl;

                cout << "The Decrypted Message is: ";
                fileDecrypt(filename, filename + "_decrypted.txt");
                cout << endl;
                cout << "The Decrypted Message had been stored in the file: " << filename << "decrypted.txt" << endl;
                cout << endl;
                break;
            }
            break;

        case 3:
            cout << endl;
            cout << "Exiting the Programme..." << endl;
            return 0;

        default:
            cout << endl;
            cout << "Invalid choice!" << endl;
            break;
        }
    }
    return 0;
}
