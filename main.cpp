#include <cstdlib>
#include "hufftree.h"
#include "decoding.h"

using namespace std;


int main(int argc, char *argv[]) {
	//string filename = argv[1];
	//int k = atoi(argv[2]);

	string filename = "testingB.txt";
	string compfilename = "testBf";
	compfilename+=".huff";
	string endfile = "testingEnd.txt";
	int k = 8;

	//nuskaitomas failas ir surasomi dazniai
	Hufftree h(filename, compfilename, k);
	h.find_bijection(k);
	h.print_bijection();

	//sugeneruojama ir surasoma info kuri dedama i uzkoduojama faila
	h.GenerateHeader(k);
	h.Encode(k);

	//bitset<4> test(k);
	//cout<<test.to_string()<<endl;

	Decoding d(compfilename, endfile);


	cin.get();
}

