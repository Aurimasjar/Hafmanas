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
        Hufftree *hufftree;
        int k;
        int wordCount;
        int ignore;
        //hufftree.freq = 0;
		int fLen;
        int tailBits;
        int tB = 0;
        bool end = false;

		INode *root;		

        Decoding(string fileRec, string fileWrite);
        ~Decoding();

        void ReadTable();
        void Decode();
		int get_code_from_tree(INode *node);

};

#endif
