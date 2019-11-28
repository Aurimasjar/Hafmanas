#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "hufftree.h"

#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>

using namespace std;


int main(int argc, char *argv[]) {
	string filename = argv[1];
	int k = atoi(argv[2]);
	
	Hufftree h(filename, k);
	h.find_bijection(k);
	h.print_bijection();
}

