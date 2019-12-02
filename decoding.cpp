#include "decoding.h"


Decoding::Decoding(string fileRec, string fileWrite)
{
    stream = new Streamer(fileRec, fileWrite);
    stream->get_k_bits(4);
    k = stream->w + 1;
    hufftree = new Hufftree(stream, k);
    cout << "k = " << k << endl;
    stream->get_k_bits(16);
    wordCount = stream->w;
    cout << "wordCount = " << wordCount << endl;
    cout << "Atempting to make table." << endl;
    ReadTable();
    cout << "Attempting to build a tree." << endl;
    hufftree->find_bijection(k);
    //hufftree->print_bijection();
    Decode();
}

void Decoding::ReadTable()
{
    int ascii, asciiCount;
    for (int i = 0; i < wordCount; i++)
    {
        if(stream->get_k_bits(k) == 1) // all bits were succesfuly read
            ascii = stream->w;
        //cout << "ascii: " << ascii << endl;
        if(stream->get_k_bits(32) == 1) // all bits were succesfuly read
            asciiCount = stream->w;
        //cout << "asciiCount: " << asciiCount << endl;
        hufftree->set_frequency_table(ascii, asciiCount);
    }
}

void Decoding::Decode()
{
    HuffCodeMap codes;
    codes = hufftree->getCodes();
    cout<<"Decoded:"<<endl;
    vector <bool> tmp;
    for(int i = 0; i < 1000; i++)
    {
        stream->get_k_bits(1);
        tmp.push_back(stream->w);
        for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); it++)
        {
            if(tmp == it->second) {
                cout<<(char)it->first;
                tmp.clear();
                break;                    
            }
        }
    }
}


Decoding::~Decoding()
{
    delete hufftree;
    delete stream;
}
