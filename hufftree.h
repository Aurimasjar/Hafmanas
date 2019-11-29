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

	vector<int> encodedBuff;

	Hufftree(string filename, string compfilename, int k);
	~Hufftree();
	void clean_stream();
	void get_frequency_table(int k);
	void find_bijection(int k);
	void print_bijection();

	INode* BuildTree(int k);
	void GenerateCodes(const INode* node, const HuffCode &prefix, HuffCodeMap &outCodes);

	void Encode(int k);
};


#endif
