#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
   string passCode;

   bool containsUppercase;
   getline(cin, passCode);

   for (int i = 0; i < passCode.length(); i++) {
      if (isalpha(passCode[i])) {
         if (passCode[i] == toupper(passCode[i])) {
            containsUppercase = true;
         }
      }

      else {
         containsUppercase = false;
         break;
      }
   }

   if (containsUppercase) {
      cout << "Valid passcode" << endl;
   }
   else {
      cout << "Invalid passcode" << endl;
   }

   return 0;
}