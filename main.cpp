#include <cstdlib>
#include "hufftree.h"

using namespace std;


int main(int argc, char *argv[]) {
	//string filename = argv[1];
	//int k = atoi(argv[2]);

	string filename = "picture.bmp";
	string compfilename = "picTest2.huff";
	int k = 4;

	Hufftree h(filename, compfilename, k);
	h.find_bijection(k);
	h.print_bijection();

	h.Encode(k);



	cin.get();
}

