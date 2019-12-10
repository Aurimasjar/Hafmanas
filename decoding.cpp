#include "decoding.h"


Decoding::Decoding(string fileRec, string fileWrite)
{
    stream = new Streamer(fileRec, fileWrite, 1);
    stream->get_k_bits(4);
    k = stream->w + 1;
	stream->get_k_bits(5);
	fLen = stream->w + 1;
    hufftree = new Hufftree(stream, k);
    //cout << "k = " << k << endl;
    stream->get_k_bits(k);
    wordCount = stream->w + 1;
    //cout << "wordCount = " << wordCount << endl;
    //cout << "ignore = " << ignore << endl;
    //cout << "Atempting to make table." << endl;
    ReadTable();
    //cout << "Attempting to build a tree." << endl;
    //hufftree->find_bijection(k); //o gal build tree?
	root = hufftree->BuildTree(k);
    //hufftree->print_bijection();
    Decode();
}

void Decoding::ReadTable()
{
    int ascii, asciiCount;
    for (int i = 0; i < wordCount; i++)
    {
        if(stream->get_k_bits(k) == 1) // all bits were succesfuly read
            ascii = stream->w;
        //cout << "ascii: " << ascii << endl;
        if(stream->get_k_bits(fLen) == 1) // all bits were succesfuly read
            asciiCount = stream->w+1;
        //cout << "asciiCount: " << asciiCount << endl;
        hufftree->set_frequency_table(ascii, asciiCount);
    }
    stream->get_k_bits(4);
    ignore = stream->w;
    //cout << "ignore = " << ignore << endl;
    stream->get_k_bits(k);
    tailBits = k - stream->w;
    tB = stream->w;
    //cout << "Tail bits:" << tailBits << endl;
    stream->get_k_bits(ignore);
}


void Decoding::Decode()
{
    HuffCodeMap codes;
    codes = hufftree->getCodes();
    //cout<<"Decoded:"<<endl;
	int k_word;
    vector<bool> temp;

    //hufftree->GenLBitSet();
    bool flag = true;
    while(flag)
    {
        k_word = get_code_from_tree(root);
        if(end)
        {
            if(k_word == -1) {break;} //returns first element of the map
            temp = hufftree->GenLBitSet(k, k_word);
            for(int i = 0; i < tailBits; i++)
                temp.pop_back();
            stream->put_bits_in_to_bitset(temp);
        }
        else 
        {
            if(k_word == -1) {break;} //returns first element of the map
            stream->put_bits_in_to_bitset(hufftree->GenLBitSet(k, k_word));
        }
    }




    //stream->ofBuffSize-1;

    if(stream->lastConverted == false)
    {
        stream->bitset_to_bytes();
        //stream->write_to_file();
    }

}


int Decoding::get_code_from_tree(INode *node)
{
	if(const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
	{
		//cout << lf->c << " ";
		return lf->c;
	}
    else if(!end){
        if( const InternalNode* in = dynamic_cast<const InternalNode*>(node))
        {
            if(stream->get_k_bits(1) == 0) { end = true; }
            if(stream->w == 0)
            {
                //cout << "left" << endl;
                return get_code_from_tree(in->left);
            }
            else
            {
                //cout << "right" << endl;
                return get_code_from_tree(in->right);
            }
        }
    }
	return -1; //bet reiktu kazkokiu budu grazinti paskutinius nuskaitytus bitus
}


Decoding::~Decoding()
{
    //delete hufftree;
    delete stream;
}
