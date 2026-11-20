// Monoalphabetic Cipher (Caesar Cipher)

#include<iostream>
#include<string>
using namespace std;

int keyNormalize(int key){

    // Normalize key
    // key % 26	Gets the remainder after dividing by 26
    // + 26	Makes a negative remainder non-negative
    // % 26	Ensures the final result is between 0 and 25
    return ((key % 26) + 26) % 26;

}

string encryption(string plainText,int key){

    string encryptedText;

    for(char ch : plainText){
        if(ch >= 'A' && ch <= 'Z'){
            encryptedText += (ch - 'A' + key ) % 26 + 'A';
        }else if(ch >= 'a' && ch <= 'z'){
            encryptedText += (ch - 'a' + key ) % 26 + 'a';
        }else{ 
            encryptedText += ch;
        }
    }
    
    return encryptedText;
}

string decryption(string encryptedText,int key){

    string decryptedText;

    for(char ch : encryptedText){
        if(ch >= 'A' && ch <= 'Z'){
            decryptedText += (ch - 'A' - key + 26) % 26 + 'A';
        }else if(ch >= 'a' && ch <= 'z'){
            decryptedText += (ch - 'a' - key + 26) % 26 + 'a';
        }else{ 
            decryptedText += ch;
        }
    }
    
    return decryptedText;
}


int main() {

    string plainText;
    int key;

    cout << "Enter message: ";
    getline(cin, plainText);

    cout << "Enter key: ";
    cin >> key;

    // Normalize key
    key = keyNormalize(key);

    // Encryption
    string encryptedText = encryption(plainText, key);

    cout << "Encrypted Text: " << encryptedText << endl;

    // Decryption
    string decryptedText = decryption(encryptedText, key);

    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}