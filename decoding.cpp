#include "decoding.h"


Decoding::Decoding(string fileRec, string fileWrite)
{
    stream = new Streamer(fileRec, fileWrite);
    stream->read_from_file();
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
    cout << "Attempting to print" << endl;
    hufftree->print_bijection();
}

void Decoding::ReadTable()
{
    int ascii, asciiCount;
    for (int i = 0; i < wordCount; i++)
    {
        if(stream->get_k_bits(k) == 1) // all bits were succesfuly read
            ascii = stream->w;
        cout << "ascii: " << ascii << endl;
        if(stream->get_k_bits(32) == 1) // all bits were succesfuly read
            asciiCount = stream->w;
        cout << "asciiCount: " << asciiCount << endl;
        hufftree->set_frequency_table(ascii, asciiCount);
    }
}



Decoding::~Decoding()
{
    delete hufftree;
    delete stream;
}
