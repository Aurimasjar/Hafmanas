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

class Decoding
{
    public:

        Streamer *stream;
        Decoding(string fileRec, string fileWrite);
        int k;

};

#endif