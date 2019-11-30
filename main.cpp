#include <cstdlib>
#include "hufftree.h"

using namespace std;


int main(int argc, char *argv[]) {
	//string filename = argv[1];
	//int k = atoi(argv[2]);

	string filename = "testingB.txt";
	string compfilename = "testBf";
	compfilename+=".huff";
	int k = 8;

	Hufftree h(filename, compfilename, k);
	h.find_bijection(k);
	h.print_bijection();

	h.GenerateHeader(k);

	h.Encode(k);

	//bitset<4> test(k);
	//cout<<test.to_string()<<endl;


	cin.get();
}

