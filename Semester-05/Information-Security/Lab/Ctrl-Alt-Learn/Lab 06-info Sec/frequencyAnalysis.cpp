
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {

    string cipherText;
    int frequency[26] = {0};
    int total = 0;
    int maxCount = 0;
    char mostFrequent;

    // Take complete ciphertext input
    cout << "Enter Cipher Text: ";
    getline(cin, cipherText);

    // Count frequency of each alphabet
    for (int i = 0; i < cipherText.length(); i++) {

        char ch = cipherText[i];

        // Check whether character is an alphabet
        if (isalpha(ch)) {

            // Convert lowercase into uppercase
            ch = toupper(ch);

            // Calculate index and increase frequency
            frequency[ch - 'A']++;

            // Count total alphabetic characters
            total++;
        }
    }

    // Display total alphabetic characters
    cout << "\nTotal Alphabetic Characters: " << total << endl;

    // Check if no alphabetic character exists
    if (total == 0) {
        cout << "No alphabetic characters found." << endl;
        return 0;
    }

    // Display frequency table
    cout << "\nLetter\tCount\tPercentage" << endl;

    for (int i = 0; i < 26; i++) {

        if (frequency[i] > 0) {

            double percentage = (frequency[i] * 100.0) / total;

            cout << char(i + 'A') << "\t"
                 << frequency[i] << "\t"
                 << percentage << "%" << endl;
        }

        // Find the most frequent letter
        if (frequency[i] > maxCount) {
            maxCount = frequency[i];
            mostFrequent = char(i + 'A');
        }
    }

    // Display most frequent letter
    cout << "\nMost Frequent Letter: " << mostFrequent << endl;
    cout << "Frequency: " << maxCount << endl;

    return 0;
}
