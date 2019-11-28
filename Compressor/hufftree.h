#ifndef HUFFTREE_H
#define HUFFTREE_H

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "streamer.h"

using namespace std;

class Hufftree
{
	public:
	Streamer *stream;
	vector<int> freq;
	int quantity;
	
	Hufftree(string filename, int k);
	~Hufftree();
	void get_frequency_table(int k);
	void print_frequency_table();
	void clean_stream();
};

#endif
