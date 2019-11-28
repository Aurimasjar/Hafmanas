#ifndef STREAMER_H
#define STREAMER_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;


class Streamer
{
	public:
	static const size_t B = 512;
	static const size_t L = 8*B;
	char buffer[B];
	bitset<L> b;
	ifstream myFile;
	int w = 0;
	int cursor = 0;
	int n = -1;
	
	void get_bits(char s[B]);
	int get_k_bits(int k);
	void read_from_file();
	Streamer(string file);
	~Streamer();
};

#endif
