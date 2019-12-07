#include "hufftree.h"

Hufftree::Hufftree(string filename,string compfilename, int k)
{
	biggest_freq = 0;
	quantity = pow(2, k);
	freq.resize(quantity);
	stream = new Streamer(filename, compfilename);
	get_frequency_table(k);
}

Hufftree::Hufftree(Streamer *str, int k)
{
	quantity = pow(2, k);
	freq.resize(quantity);
	stream = str;
}

Hufftree::~Hufftree()
{
    clean_stream();
}

int Hufftree::set_bits_to_write_a_number(int number)
{
	int bits_count = 0;
	int ndal = number-1;
	while(true)
	{
		ndal /= 2;
		bits_count++;
		if(ndal == 0)
		{
			break;
		}
	}
	return bits_count;
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

void Hufftree::set_frequency_table(int word, int frequency)
{
    freq[word] = frequency;
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
			if(freq[i] > biggest_freq)
			{
				biggest_freq = freq[i];
			}
		}
	}
	bits_for_biggest_freq = set_bits_to_write_a_number(biggest_freq);

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
		cout << freq[it->first] << " | " << (char)it->first << " " << it->first << "d ";
		copy(it->second.begin(), it->second.end(), ostream_iterator<bool>(cout));
		cout << endl;
	}
}

HuffCodeMap Hufftree::getCodes()
{
    return codes;
}

int Hufftree::FindMaxCodeLen(vector<int> keys)
{
    int max_len = 0;

    for(int i = 0; i<keys.size(); i++)
    {
        if(codes[keys[i]].size() >= max_len)
        {
            max_len = codes[keys[i]].size();
        }
    }

    return max_len;
}

//Generates and prints number from decimal to binary
vector<bool> Hufftree::GenLBitSet(int l, int Dec)
{
    bitset<64> key_bit_set(Dec);
    vector<bool> key_bit_vector;
    key_bit_vector.resize(l);

    int j = 0;
    for(int i = l-1; i>=0; i--)
    {
        key_bit_vector[j] = key_bit_set[i];
        j++;
    }

    /*for(int i = 0; i< key_bit_vector.size(); i++)
    {
        cout<<key_bit_vector[i];
    }
    cout<<endl;*/

   return key_bit_vector;
}

void Hufftree::GenerateHeader(int k)
{
    int k_for_bin = k-1;
    bitset<4> k_bits(k_for_bin);
    vector<bool> k_bool_bits;
    k_bool_bits.resize(4);

    int j = 0;
    for(int i = 3; i>=0; i--){
        k_bool_bits[j] = k_bits[i];
        j++;
    }

    /*for(int i = 0; i < k_bool_bits.size(); i++)
    {
        cout<<k_bool_bits[i]<<" ";
    }
    cout<<endl;*/

   //cout<<k_bits.to_string()<<endl;

    stream->put_bits_in_to_bitset(k_bool_bits);



    vector<int> keys;
    for(map<int, HuffCode>::iterator it = codes.begin(); it != codes.end(); ++it) {
        keys.push_back(it->first);
       // cout << it->first << "\n";
    }

    uint64_t  codeAmm = 0;
    for(int i = 0; i<keys.size(); i++)
    {
       // cout<<freq[keys[i]]<<" "<<codes[keys[i]].size()<<" "<<keys[i]<<endl;
        codeAmm += freq[keys[i]] * codes[keys[i]].size();
    }

    lastBitamm = 8-(codeAmm%8);
    if(lastBitamm == 8){
        lastBitamm = 0;
    }

    stream->put_bits_in_to_bitset(GenLBitSet(4, lastBitamm));

    cout<<lastBitamm<<endl;



    //int nH = FindMaxCodeLen(keys);

    //GenLBitSet(8, nH);
    stream->put_bits_in_to_bitset(GenLBitSet(16,keys.size()));

    for(int i = 0; i < keys.size(); i++)
    {

       // cout<<keys[i]<<" ";
        stream->put_bits_in_to_bitset(GenLBitSet(k, keys[i]));

        //cout<<keys[i]<<" "<<freq[keys[i]]<<endl;
        //cout<<freq[97]<<endl;
        //
        stream->put_bits_in_to_bitset(GenLBitSet(32, freq[keys[i]]));

       //  stream->put_bits_in_to_bitset(codes[keys[i]]);

    }
   // cout<<endl;

    //cout<<keys.size()<<endl;


   /* if(stream->lastConverted == false)
    {
        stream->bitset_to_bytes();
        //stream->write_to_file();
    }*/

}

//get word from k bits and use it to get code from the tree
void Hufftree::Encode(int k)
{

    GenerateHeader(k);

    stream->return_myFile_to_begining();
    stream->read_from_file();


    stream->put_bits_in_to_bitset(GenLBitSet(lastBitamm, 0));

    while(1)
    {
        if(stream->get_k_bits(k) == 0)
        {
            stream->put_bits_in_to_bitset(codes[stream->w]);

            break;
        }
       stream->put_bits_in_to_bitset(codes[stream->w]);
       if (stream->w == 13)
       {
           stream->get_k_bits(k);
       }
    }

    if(stream->lastConverted == false)
    {
        stream->bitset_to_bytes();
        //stream->write_to_file();
    }
}
