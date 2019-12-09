#ifndef HUFFTREE_H
#define HUFFTREE_H

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "streamer.h"

#include <queue>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

//for storing Hufmann code
typedef std::vector<bool> HuffCode;

//for creating map between old value and Hufmann code
typedef std::map<int, HuffCode> HuffCodeMap;

//node class
class INode
{
	public:
		const int f;

		virtual ~INode() {}

		protected:
		INode(int f) : f(f) {}
};

//non-leaf node class
class InternalNode : public INode
{
	public:
		INode *const left;
		INode *const right;

		InternalNode(INode* c0, INode* c1) : INode(c0->f + c1->f), left(c0), right(c1) {}
		~InternalNode()
		{
			delete left;
			delete right;
		}
};

//leaf node class
class LeafNode : public INode
{
	public:
		const int c;
		LeafNode(int f, int c) : INode(f), c(c) {}
};

//for sorting nodes by their values
struct NodeCmp
{
	//returns true if left node value is bigger than right
	bool operator()(const INode* lhs, const INode* rhs) const { return lhs->f > rhs->f; }
};

class Hufftree
{
	public:
		Streamer *stream;
		vector<int> freq;
		int quantity;
		HuffCodeMap codes;
		int lastBitamm;
		int biggest_freq;
		int bits_for_biggest_freq;

		int headerLastBitAm;
		//vector<int> encodedBuff;

		Hufftree(string filename, string compfilename, int k);
		Hufftree(Streamer *str, int k);
		~Hufftree();

		void clean_stream();
		void get_frequency_table(int k);
		void find_bijection(int k);
		void print_bijection();
		void set_frequency_table(int word, int frequency);
		int set_bits_to_write_a_number(int number);

		INode* BuildTree(int k);
		void GenerateCodes(const INode* node, const HuffCode &prefix, HuffCodeMap &outCodes);
		void GenerateHeader(int k);

		int FindMaxCodeLen(vector<int> keys);

		int getCodeValue(HuffCode v);
		HuffCodeMap getCodes();

		vector<bool> GenLBitSet(int l, int Dec);

		void Encode(int k);
};


#endif
