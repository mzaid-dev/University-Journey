// Polyalphabetic Cipher · Vigenère Cipher

#include<iostream>
#include<string>
using namespace std;

// Generate key equal to plaintext length
string generateKey(int plainTextLength,string key){
   string newKey;

    if (key.empty()) {
        return "";
    }

    // Repeat key until its length matches plaintext length
    // i % key.length()	Gets the index of the original key
    // % operator	Restarts the key from index 0
   for(int i = 0 ; i < plainTextLength ; i++){
    newKey += key[i % key.length()];
   }

   return newKey;

}

string encryption(string plainText,string key){

    string encryptedText;

    for(int i = 0 ; i < plainText.length() ; i++){
        char ch = plainText[i];
        if(ch >= 'A' && ch <= 'Z'){

            // ch - 'A'	Converts plaintext letter into a number (0-25)
            // key[i] - 'A'	Converts key letter into a number (0-25)
            // +	Adds plaintext and key values
            // % 26	Keeps the result between 0 and 25
            // + 'A'	Converts the result back into an uppercase letter
            encryptedText += (ch - 'A' + key[i] - 'A' ) % 26 + 'A';

        }else if(ch >= 'a' && ch <= 'z'){
            encryptedText += (ch - 'a' + key[i] - 'a' ) % 26 + 'a';
        }else{ 

            // Keeps spaces, numbers and special characters unchanged
            encryptedText += ch;
        }
    }
    
    return encryptedText;
}

string decryption(string encryptedText,string key){

    string decryptedText;

    for(int i = 0 ; i < encryptedText.length() ; i++){

        char ch = encryptedText[i];
        if(ch >= 'A' && ch <= 'Z'){

            // ch - 'A'	Converts ciphertext letter into a number (0-25)
            // key[i] - 'A'	Converts key letter into a number (0-25)
            // -	Subtracts key value from ciphertext value
            // + 26	Prevents a negative result
            // % 26	Keeps the result between 0 and 25
            // + 'A'	Converts the result back into an uppercase letter
            decryptedText += (ch - 'A' - (key[i] - 'A') + 26) % 26 + 'A';

        }else if(ch >= 'a' && ch <= 'z'){
            decryptedText += (ch - 'a' - (key[i] - 'a') + 26) % 26 + 'a';
        }else{ 
            decryptedText += ch;
        }
    }
    
    return decryptedText;
}


int main() {

    string plainText;
    string key;

    cout << "Enter message: ";
    getline(cin, plainText);

    cout << "Enter key: ";
    getline(cin, key);

    key = generateKey(plainText.length(),key);

    // Encryption
    string encryptedText = encryption(plainText, key);

    cout << "Encrypted Text: " << encryptedText << endl;

    // Decryption
    string decryptedText = decryption(encryptedText, key);

    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}