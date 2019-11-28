#include "hufftree.h"

Hufftree::Hufftree(string filename, int k)
{
	quantity = pow(2, k);
	freq.resize(quantity);
	stream = new Streamer(filename);
	get_frequency_table(k);
}

Hufftree::~Hufftree() 
{
	delete stream;
}

void Hufftree::get_frequency_table(int k)
{
	//get word from k bits an add it to frequency table
	while(stream->get_k_bits(k) != 0)
	{
		//cout << (char)stream.w;
		freq[stream->w]++;
	}//cout << (char)stream.w << endl;
}

void Hufftree::print_frequency_table()
{
	for(int i = 0; i < quantity; i++)
	{
		if(freq[i] != 0)
			cout << "(" << (char)i << ") " << i << ": " << freq[i] << endl;
	}cout << endl;
}

void Hufftree::clean_stream() 
{
	delete stream;
}
