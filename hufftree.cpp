#include "hufftree.h"

Hufftree::Hufftree(string filename,string compfilename, int k)
{
	quantity = pow(2, k);
	freq.resize(quantity);
	stream = new Streamer(filename, compfilename);
	get_frequency_table(k);
}

Hufftree::~Hufftree()
{
    clean_stream();
}

void Hufftree::get_frequency_table(int k)
{
	//get word from k bits an add it to frequency table
	while(1)
    {
        if(stream->get_k_bits(k) == 0)
        {
            //cout << stream->w;
            freq[stream->w]++;
            break;
        }

        freq[stream->w]++;
	}
	//cout << stream->w << endl;
	//clean_stream();
}

void Hufftree::clean_stream()
{
	delete stream;
}


//constructs Hufmann tree
INode* Hufftree::BuildTree(int k)
{
	priority_queue<INode*, vector<INode*>, NodeCmp> trees;

	for (int i = 0; i < quantity; ++i)
	{
		if(freq[i] != 0)
		{
			//word with frequency >0 found: addding to queue (it automatically resorts it)
			trees.push(new LeafNode(freq[i], i));
		}
	}
	while (trees.size() > 1)
	{
		//two values with smallest frequencies are assigned to nodes, their sum becomes the value of their parent, parent is added to tree
		INode* childR = trees.top();
		trees.pop();

		INode* childL = trees.top();
		trees.pop();

		INode* parent = new InternalNode(childR, childL);
		trees.push(parent);
	}
	return trees.top();
}

//generates Hufmann codes with DFS from Huffman tree
void Hufftree::GenerateCodes(const INode* node, const HuffCode &prefix, HuffCodeMap &outCodes)
{
	//if leaf is reached, stop and save Hufmann code, else go further
	if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
	{
		outCodes[lf->c] = prefix;
	}
	else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
	{
		HuffCode leftPrefix = prefix;
		//add 0 to the left node
		leftPrefix.push_back(false);
		GenerateCodes(in->left, leftPrefix, outCodes);

		HuffCode rightPrefix = prefix;
		//add 1 to the right node
		rightPrefix.push_back(true);
		GenerateCodes(in->right, rightPrefix, outCodes);
	}
}

//finds bijection form word of k bits to Huffman code
void Hufftree::find_bijection(int k)
{
	INode* root = BuildTree(k);

	GenerateCodes(root, HuffCode(), codes);
	delete root;
}

//prints frequency of word, the word itself in decimal format and mapping to Hufmann code
void Hufftree::print_bijection()
{
	for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); it++)
	{
		cout << freq[it->first] << " | " << it->first << "d ";
		copy(it->second.begin(), it->second.end(), ostream_iterator<bool>(cout));
		cout << endl;
	}
}

void Hufftree::Encode(int k)
{
    stream->return_myFile_to_begining();
    stream->read_from_file();
    //encodedBuff.resize(100);

    int atas = 0;
    while(1)
    {
        if(stream->get_k_bits(k) == 0)
        {
            //atas++;
           // cout<<stream->w<<" ";
            stream->put_bits_in_to_bitset(codes[stream->w]);
            break;

        }
       // atas++;
      // cout<<stream->w<<" ";
       stream->put_bits_in_to_bitset(codes[stream->w]);

    }



   // cout<<endl;

   // cout<<atas<<endl;

    if(stream->lastConverted == false)
    {
        stream->bitset_to_bytes();
        //stream->write_to_file();
    }

    //cout<<stream->ofB.to_string()<<endl;

    //stream->bitset_to_bytes();

    /*for(int i = 0; i < freq.size(); i++){
        cout<<freq[i]<<" ";
    }

    cout<<endl;*/

}
