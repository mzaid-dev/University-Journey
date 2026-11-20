#include<iostream>
#include<string>
using namespace std;

// Encryption function
string encryption(string text,int key){

    string encryptedText = "";

    for(char ch : text){
        if (ch >= 'A' && ch <= 'Z'){

            // ch - 'A' : Converts uppercase character into position (0-25)
            // + key    : Shifts the letter forward
            // % 26     : Keeps the position within 0-25
            // + 'A'    : Converts the position back into uppercase letter
            encryptedText += ( ch - 'A' + key ) % 26 + 'A';

        }else if(ch >= 'a' && ch <= 'z'){
            encryptedText += ( ch - 'a' + key ) % 26 + 'a';
        }else{
            encryptedText += ch;
        }
    }

    return encryptedText;
    
}

// Decryption function
string decryption(string chiperText,int key){

    string decryptedText = "";

    for(char ch : chiperText){
        if (ch >= 'A' && ch <= 'Z'){

            // ch - 'A' : Converts uppercase character into position (0-25)
            // - key    : Shifts the letter backward
            // + 26     : Prevents a negative value before modulo
            // % 26     : Keeps the position within 0-25
            // + 'A'    : Converts the position back into uppercase letter
            decryptedText += ( ch - 'A' - key + 26) % 26 + 'A';

        }else if(ch >= 'a' && ch <= 'z'){
            decryptedText += ( ch - 'a' - key + 26) % 26 + 'a';
        }else{
            decryptedText += ch;
        }
    }

    return decryptedText;
    
}
 
int main(){

    string plainText;
    cout << "enter text : ";
    getline(cin,plainText);

    int key = 3;

    // Normalize key
    // key % 26	Gets the remainder after dividing by 26
    // + 26	Makes a negative remainder non-negative
    // % 26	Ensures the final result is between 0 and 25
    key = ((key % 26) + 26) % 26;

    string encryptedText = encryption(plainText, key);

    cout << "Encrypted text: " << encryptedText << endl;

    string decryptedText = decryption(encryptedText, key);

    cout << "Decrypted text: " << decryptedText << endl;

    return 0;

    
}