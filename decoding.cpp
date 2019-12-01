#include "decoding.h"


Decoding::Decoding(string fileRec, string fileWrite)
{
    stream = new Streamer(fileRec, fileWrite);
    stream->read_from_file();
    stream->get_k_bits(4);
    k=stream->w;
}



Decoding::~Decoding()
{

}
