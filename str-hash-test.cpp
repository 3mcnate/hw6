#include "hash.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2){
        cout << "Please provide a string to hash" << endl;
        return 1;
    }

    // use debug r values so we get repeated results
    MyStringHash h1(true);

    // key to hash
    string k(argv[1]);
    size_t hk = h1(k);
    // Test the hash
    cout << "h(" << k << ")=" << hk << endl;
    
    HASH_INDEX_T testletters[6] = {
        h1.letterDigitToNumber('a'),
        h1.letterDigitToNumber('b'),
        h1.letterDigitToNumber('c'),
        h1.letterDigitToNumber('d'),
        h1.letterDigitToNumber('e'),
        h1.letterDigitToNumber('f')
    };
    
    cout << "abcdef = ";
    for (int i = 0; i < 6; i++) {
        cout << testletters[i] << " ";
    }
    cout << endl;
    cout << "converted to decimal: " << h1.convertBase(testletters, 0) << endl;
    
    return 0;
}