#ifndef DECODING_H
#define DECODING_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <cmath>
#include <cstdlib>

#include "hufftree.h"

using namespace std;

typedef std::vector<bool> HuffCode;

//for creating map between old value and Hufmann code
typedef std::map<int, HuffCode> HuffCodeMap;

class Decoding
{
    public:
        Streamer *stream;
<<<<<<< HEAD
=======
        Hufftree *hufftree;
>>>>>>> 71af5d22050d291c09812b54262fd0aff335d00a
        int k;
        hufftree.freq = 0;


        Decoding(string fileRec, string fileWrite);
        

        Decoding(string fileRec, string fileWrite);
        ~Decoding();

};

#endif