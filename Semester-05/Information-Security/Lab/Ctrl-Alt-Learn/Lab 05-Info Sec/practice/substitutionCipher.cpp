// Custom Monoalphabetic Substitution Cipher

#include<iostream>
#include <string>
#include<cctype>
using namespace std;

bool validateKey(string &key){

    if (key.length() != 26)
    {
        cout << "Invalid key! Key must contain 26 characters.";
        return 0;
    }

    // Check duplicate characters
    bool seen[26] = {false};

    for (int i = 0 ; i < 26 ; i++){
        
        key[i] = toupper(key[i]);
        
        if (key[i] < 'A' || key[i] > 'Z')
        {
            cout << "Invalid key! Use English alphabets only.";
            return 0;

        }

        int index = key[i] - 'A';

        if (seen[index])
        {
            cout << "Invalid key! Duplicate characters found.";
            return 0;
        }

        seen[index] = true;   
    }

    return true;
    
}

string encryption(string plainText,string key){

    string encryptedText;

   for(char ch : plainText){
    if (ch >= 'A' && ch <= 'Z')
    {
        encryptedText += key[ch - 'A'];
    }else if (ch >= 'a' && ch <= 'z')
    {
        encryptedText += key[ch - 'a'] + 32;
    }else{
        encryptedText += ch;
    }
    
    
   }
    
    return encryptedText;
}

string decryption(string encryptedText,string key){

    string decryptedText;

    for(char ch : encryptedText){
        if(ch >= 'A' && ch <= 'Z'){
           for (int j = 0; j < 26; j++)
           {
            if(key[j] == ch){
                decryptedText += 'A' + j;
                break;
            }
           }
           
        }else if(ch >= 'a' && ch <= 'z'){

            for (int i = 0; i < 26; i++)
            {
             if (key[i] + 32 == ch)
             {
                decryptedText += 'a' + i;
                break;
             } 
            }
            
            
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

    bool isValidKey = validateKey(key);
    if(!isValidKey){
        return 0;
    }

    // Encryption
    string encryptedText = encryption(plainText, key);

    cout << "Encrypted Text: " << encryptedText << endl;

    // Decryption
    // Decryption
    string decryptedText = decryption(encryptedText, key);

    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}