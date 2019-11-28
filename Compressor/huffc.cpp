#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "hufftree.h"

using namespace std;


int main(int argc, char *argv[]) {
	string filename = argv[1];
	int k = atoi(argv[2]);
	
	Hufftree h(filename, k);
	h.print_frequency_table();
}
