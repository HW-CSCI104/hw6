#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    /*void convert(int n, 36, int res[]) {
      int sum = 0;
      for (int k = 0; n != 0; k++) {
        sum += n % b;
        n /= b;
      }
      return sum;
    }*/

    HASH_INDEX_T operator()(const std::string& k) const
    {
      unsigned long long w[5] {0, 0, 0, 0, 0};
      size_t wIndex = 4;
      int kIndex = k.size()-1;
      while (kIndex >= 0) {
        size_t num = 0;
        for (int i = 0; i <= 5; i++) {
          if (kIndex-i < 0) {
            break;
          }
          char temp = k[kIndex-i];
          HASH_INDEX_T ch = letterDigitToNumber(temp);
          num += pow(36, i) * ch;
        }
        w[wIndex] = num;
        wIndex--;
        kIndex -= 6;
      }
      HASH_INDEX_T sum = 0;

      for (size_t j = 0; j <= 4; j++) {
        //std::cout << "w[" << j << "] = " << w[j] << std::endl;
        sum += rValues[j] * w[j];
      }

      return sum;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if (letter >= 'A' && letter <= 'Z') {
            return letter - 'A';
          } else if (letter >= 'a' && letter <= 'z') {
            return letter - 'a';
          } else if (letter >= '0' && letter <= '9') {
            return letter - '0' + 26;
          }
          return -1;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
