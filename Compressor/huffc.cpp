#include <cstdlib>
#include "hufftree.h"

using namespace std;


int main(int argc, char *argv[]) {
	string filename = argv[1];
	int k = atoi(argv[2]);
	
	Hufftree h(filename, k);
	h.find_bijection(k);
	h.print_bijection();
}

