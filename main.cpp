#include <cstdlib>
#include "hufftree.h"
#include "decoding.h"

using namespace std;


int main(int argc, char *argv[]) {

	string originalFile, decodedFile;
	int k = 8;
	int choice = 0;
	string endcodedFile = "encodedFile.huff";
	while(true){
		cout << "Encode = 1" << endl << "Decode = 2" << endl << "Exit = 0" << endl << ">";
		cin >> choice;
		switch(choice){
			case 0:{
				exit(1);
			}
			case 1:{
				cout << "Enter original file: ";
				cin >> originalFile;
				cout << "Enter k: ";
				cin >> k;
				Hufftree h(originalFile, endcodedFile, k);
				h.find_bijection(k);
				h.print_bijection();

				h.GenerateHeader(k);
				h.Encode(k);

				cout << "File " << originalFile << " encoded to file " << endcodedFile << endl; 
				break;
			}
			case 2:{
				cout << "Decoded file name: ";
				cin >> decodedFile;
				Decoding d(endcodedFile, decodedFile);
				cout << "File " << endcodedFile << " decoded to file " << decodedFile << endl; 
				break;
			}
			default:{
				cout << "Please enter your choice again." << endl;
			}
		}
	}
	//cin.get();
}

