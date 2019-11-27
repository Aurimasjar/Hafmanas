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


int main(int argc, char *argv[]) {
	string filename = argv[1];
	int k = atoi(argv[2]);
	int quantity = pow(2, k);
	
	vector<int> freq(quantity);

	Streamer stream(filename);

	/*for(int i = 0; i < stream.L; i++)
	{
		if(i % 8 == 0) cout << " ";
		cout << stream.b[i];
	}cout << endl;*/


	//get word from k bits an add to frequency table
	while(stream.get_k_bits(k) != 0)
	{
		//cout << (char)stream.w;
		freq[stream.w]++;
	}//cout << (char)stream.w << endl;


	//printing frequency table
	for(int i = 0; i < quantity; i++)
	{
		if(freq[i] != 0)
			cout << "(" << (char)i << ") " << i << ": " << freq[i] << endl;
	}cout << endl;

}
