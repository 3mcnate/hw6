#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <stdexcept>
#include <sstream>

typedef size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T w[5] = { /* filled with 0's */ };

        // create array to convert chars to base-36 values
        HASH_INDEX_T* letters = new HASH_INDEX_T[k.size()];
        for (size_t i = 0; i < k.size(); i++) {
            letters[i] = letterDigitToNumber(k[i]);
        }

        int spos = (int)k.size() - 1; // position in the letters array. decrements every iteration
        int i = 4; // index of w array. decrements when a resets
        while (spos >= 0) {
            // convert from base 36 to base 10 for each 6-digit chunk
            w[i] = convertBase(letters, spos-5); // -5 because this takes care of spos as well
            spos -= 6;
            i--;
        }

        #ifdef DEBUG
            for (int i = 0; i < 5; i++) {
                std::cout << "w[" << i << "] = " << w[i] << std::endl;
            }
        #endif

        HASH_INDEX_T hash = 0;
        for (int i = 0; i < 5; i++) {
            hash += rValues[i] * w[i];
        }
        return hash;

    }

    // HASH_INDEX_T convertBase(HASH_INDEX_T* letters, int spos, int a) const
    // {
    //     if (spos == -1) return 0;
    //     if (a == 1) return letters[spos];   
    //     return letters[a] + 36*convertBase(letters, spos-1, a-1);
    // }

    HASH_INDEX_T convertBase(HASH_INDEX_T* a, int pos) const 
    {
        int r = 36;
        HASH_INDEX_T x = 0;
        for (int i = 0; i < 6; i++) {
            if (pos < 0) {
                pos++;
                continue;
            }
            x += a[pos];
            x *= r;
            pos++;
        }
        return x / r;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if ('0' <= letter && letter <= '9') {
            return letter - 22;
        }
        if ('A' <= letter && letter <= 'Z') {
            return letter - 65;
        }
        if ('a' <= letter && letter <= 'z') {
            return letter - 97;
        }

        std::stringstream ss;
        ss << "char " << letter << " is not an alphanumeric character";
        throw std::invalid_argument(ss.str());
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
