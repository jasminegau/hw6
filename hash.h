#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;
typedef unsigned long long ULL;

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
        HASH_INDEX_T sum = 0;
        size_t size = k.length(); // size of the string
        size_t left = size%6; // how many char will be in the last w
        size_t track = 29; // last index of the string
        std::string temp;
        for(size_t t=0; t<(30-size); t++){
            temp+='a';
        }
        temp+=k;
        unsigned long long w[5];
        for(int i=4; i>=0; i--){ // loop complete w
            w[i] = (((((letterDigitToNumber(temp[track-5])*36
            +letterDigitToNumber(temp[track-4]))*36
            +letterDigitToNumber(temp[track-3]))*36
            +letterDigitToNumber(temp[track-2]))*36
            +letterDigitToNumber(temp[track-1]))*36
            +letterDigitToNumber(temp[track]));
            track -= 6;
        }
        for(int i=4; i>=0; i--){
            std::cout << w[i] << std::endl;
            sum+=rValues[i]*w[i];
        }

        return sum;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T t;
        letter = std::tolower(letter);
        if((letter>=97) && (letter<=122)){ // characters a-z
            t = letter - 97;
        } 
        else if ((letter >= 48) && (letter <= 57)){
            t = letter - 48 + 26;
        }
        return t;
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
