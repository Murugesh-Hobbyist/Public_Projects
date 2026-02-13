/*
  SafeString utf8index() and utf8nextIndex()
  Examples of SafeString utf8 functions

  by Matthew Ford
  Copyright(c)2025 Forward Computing and Control Pty. Ltd.
  This example code is in the public domain.

  www.forward.com.au/pfod/ArduinoProgramming/SafeString/index.html
*/

#include "SafeString.h"
createSafeString(sfUTF8, 12, "-℃+℉*%.");
//createSafeString(sfUTF8, 12, "-\342\204\203+\342\204\211*%.");

void printHex(SafeString &sf) {
    for (size_t i=0;i<sf.length(); i++) {
    Serial.print(" 0x");
    Serial.print((uint8_t)sf.charAt(i),HEX);
  }
  Serial.println();
}

void printUTF8(SafeString &sf) {
  cSF(sfUTF8char, 4); // max utf8 char size
  size_t idx = 0;
  size_t nextIdx = 0;
  size_t count = 0;
  while (idx < sf.length()) {
    nextIdx = sf.utf8nextIndex(idx);
    sf.substring(sfUTF8char, idx,nextIdx);
    Serial.print("utf8 char:"); Serial.print(count); Serial.print(" "); Serial.print(sfUTF8char);
    Serial.print(" idx:"); Serial.print(idx);
    Serial.print(" len:"); Serial.print(sfUTF8char.length());
    Serial.println();
    idx = nextIdx;
    count++;
  }  
}
void setup() {
  // Open serial communications and wait a few seconds
  Serial.begin(9600);
  for (int i = 10; i > 0; i--) {
    Serial.print(' '); Serial.print(i);
    delay(500);
  }
  Serial.println();

  Serial.println(F("SafeString utf8index() and utf8nextIndex() usage"));
  Serial.println(F("SafeString::setOutput(Serial); // verbose == true"));
  // see the SafeString_ConstructorAndDebugging example for debugging settings
  SafeString::setOutput(Serial); // enable full debugging error msgs
  Serial.println();

  sfUTF8.debug();
  Serial.println();
  Serial.println(F(" Print the bytes in sfUTF8 as hex."));
  printHex(sfUTF8);
  Serial.println();

  Serial.println(F(" Count the number of utf8 chars in sfUTF8 safestring using utf8nextIndex()."));
  Serial.println(F(" This assumes sfUTF8 holds valid utf8 code points."));
  size_t idx = 0;
  size_t count = 0;
  while (idx < sfUTF8.length()) {
    count++;
    idx = sfUTF8.utf8nextIndex(idx);
  }
  Serial.print(F(" The number of uft8 chars in sfUTF8 is ")); Serial.println(count);
  Serial.println();
  
  Serial.println(F(" Print the utf8 chars in order using utf8nextIndex()"));
  printUTF8(sfUTF8);
  Serial.println();
  
  cSF(sfSubstr,12); 
  Serial.println(F(" Take a substring from 0 to idx 7"));
  sfUTF8.substring(sfSubstr, 0,7);
  Serial.print(F(" The substring is "));
  sfSubstr.debug();
  Serial.println();
  printUTF8(sfSubstr);
  Serial.println();
  
  Serial.println(F(" Use uft8index to find the idx <= 7 that does not break a valid uft8 code point"));
  Serial.print(F(" sfUTF8.utf8index(7) returns ")); Serial.println(sfUTF8.utf8index(7));
  Serial.println(F(" sfUTF8.substring(sfSubstr, 0,sfUTF8.utf8index(7))"));
  sfUTF8.substring(sfSubstr, 0,sfUTF8.utf8index(7));
  Serial.print(F(" The substring is "));
  sfSubstr.debug();
  Serial.println();
  printUTF8(sfSubstr);
  Serial.println();

  Serial.println(F(" Use uft8index and utf8nextIndex to extract the utf8 code point that char idx:6"));
  Serial.println(F(" The whole SafeString is does NOT need to scanned."));
  Serial.println(F(" sfUTF8.substring(sfSubstr, sfUTF8.utf8index(6),sfUTF8.utf8nextIndex(6))"));
  sfUTF8.substring(sfSubstr, sfUTF8.utf8index(6),sfUTF8.utf8nextIndex(6));
  Serial.print(F(" The utf8 code point around this idx is "));
  sfSubstr.debug();
  Serial.println();
  printUTF8(sfSubstr);
  Serial.println();

  Serial.println(F(" ================================================"));
  Serial.println(F(" Tests with invalid utf8 byte sequencies"));
  Serial.println(F(" Replace sfUTF8 char at idx 8 with 0x84 a uft8 tail byte."));
  Serial.println(F(" and the sfUTF8 char at idx 9 with 0x89 a uft8 tail byte."));
  sfUTF8.setCharAt(8,0x84);
  sfUTF8.setCharAt(9,0x89);
  printHex(sfUTF8);
  printUTF8(sfUTF8);
  Serial.println();

  Serial.println(F(" Use uft8index to find the idx <= 8 that does not break a valid uft8 code point"));
  Serial.print(F(" sfUTF8.utf8index(8) returns ")); Serial.println(sfUTF8.utf8index(8));
  Serial.println(F(" sfUTF8.substring(sfSubstr, 0,sfUTF8.utf8index(8))"));
  sfUTF8.substring(sfSubstr, 0,sfUTF8.utf8index(8));
  Serial.print(F(" The substring is "));
  sfSubstr.debug();
  printUTF8(sfSubstr);
  Serial.println();
  
  Serial.println(F(" The remaining substring is "));
  Serial.println(F(" sfUTF8.substring(sfSubstr, sfUTF8.utf8index(8))"));
  sfUTF8.substring(sfSubstr, sfUTF8.utf8index(8));
  sfSubstr.debug();
  printUTF8(sfSubstr);
  Serial.println();
  Serial.println();

  Serial.println(F(" Replace sfUTF8 char at idx 7 with 0xE2 a uft8 start byte."));
  sfUTF8.setCharAt(7,0xE2);
  printHex(sfUTF8);
  printUTF8(sfUTF8);
  Serial.println();

  Serial.println(F(" Use uft8index to find the idx <= 6 that does not break a valid uft8 code point"));
  Serial.print(F(" sfUTF8.utf8index(6) returns ")); Serial.println(sfUTF8.utf8index(6));
  Serial.println(F(" sfUTF8.substring(sfSubstr, 0,sfUTF8.utf8index(6))"));
  sfUTF8.substring(sfSubstr, 0,sfUTF8.utf8index(6));
  Serial.print(F(" The substring is "));
  sfSubstr.debug();
  Serial.println();
  printUTF8(sfSubstr);
  Serial.println(F(" The endIdx:5 is not included in the substring."));
  Serial.println();

  Serial.println(F(" The remaining substring is "));
  Serial.println(F(" sfUTF8.substring(sfSubstr, sfUTF8.utf8index(6))"));
  sfUTF8.substring(sfSubstr, sfUTF8.utf8index(6));
  sfSubstr.debug();
  printUTF8(sfSubstr);
  Serial.println();
     
}

void loop() {
}
