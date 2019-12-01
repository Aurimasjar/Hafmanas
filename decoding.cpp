#include "decoding.h"


 Decoding::Decoding(string fileRec, string fileWrite)
 {
    stream = new Streamer(fileRec, fileWrite);


 }

