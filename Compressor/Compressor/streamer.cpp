#include "streamer.h"

Streamer::Streamer(string file)
{
	myFile.open(file, ios::in | ios::binary);
	read_from_file();
}

Streamer::~Streamer()
{
	myFile.close();
}


//reads a portion of bits from file
void Streamer::read_from_file()
{
	myFile.read(buffer, B);
	get_bits(buffer);
	if(!myFile)
	{
		n = myFile.gcount();
	}
}



//converts char array to bitset
void Streamer::get_bits(char s[B])
{
	for (int i = 0; i < B; ++i) {
	  char c = s[i];
	  for (int j = 7; j >= 0 && c; --j) {
		 if (c & 0x1) {
		   b.set(8 * i + j);
		 }
		 c >>= 1;
	  }
	}
}


//returns word from k bits
int Streamer::get_k_bits(int k)
{
	w = 0;
	for(int i = k-1; i >= 0; i--)
	{
		w += b[cursor]*pow(2, i);
		cursor++;

		if(n > 0)
		{
			if(cursor >= 8*n)
			{
				//all bits were read
				return 0;
			}
		}
		else if(cursor >= L)
		{
			//need to take new portion of data
			cursor = 0;
			b.reset();
			read_from_file();
		}
	}
	
	return 1;
}
