#include <iostream>
#include <fstream>

#include "SimpleNode.h"
#include "ComplexNode.h"

#include <string>

using namespace std;

class Huffman{
	private:
	public:
		Huffman();
		void calcFreqs(char * filename, int * table);
		void freqsToNodes(int * table, Node ** nodes);
		Node * BuildTree(Node **nodes);
		void calcEncodings(Node* root, string s);
		void Compress(string filename);
		void Decode(string filename);
}; 

void SortNodes(Node **, int);

string encodings[256];

Huffman::Huffman(){

}

// This method reads in from the file given in argv[2]
// and records the frequencies of each character
void Huffman::calcFreqs(char * filename, int * table){

	ifstream file;
	file.open(filename);
	unsigned char c;

	// Intitialise table to all zeros.
	for (int i = 0; i < 256; i++){
		table[i] = 0;
	}

	// Read each character and add to table.
	while(!file.eof()){
		c = file.get();
		table[c]++;	
	}
	for (int i = 0; i < 256; i++){
		if (table[i] == 0){
			table[i] = 1;
		}
	}
	file.close();
}	

void Huffman::freqsToNodes(int * table, Node ** nodes){
	for (int i = 0; i < 256; i++){
		// Construct nodes using character i, and it's frequency.
		nodes[i] = new SimpleNode(i, table[i]);
	}
}

void SortNodes(Node ** nodes, int NodesInArray = 256){
	Node *min;
	Node *temp;
	int mIndex;

	for (int j = 0; j < 256; j++){
		min = nodes[j];
		mIndex = j;
		//Find the smallest element in this segment of the array. 
		for (int i = j+1; i < NodesInArray; i++){
			if (nodes[i]->frequency < min->frequency){
				min = nodes[i];
				mIndex = i;
			}
		}

		//Swap the smallest element with the element at the start of this segment of the array. 
		if (mIndex != j){
			temp = nodes[j];
			nodes[j] = min;
			nodes[mIndex] = temp;
		}
	}
}

Node * Huffman::BuildTree(Node **nodes){
	for (int i = 0; i < 255; i++){
		SortNodes(&nodes[i], 256-i);
		nodes[i+1] = new ComplexNode(nodes[i], nodes[i+1]);
	}	
	return nodes[255];
}

void Huffman::calcEncodings(Node * root, string s = ""){

	if (!root->isSimple()){
		calcEncodings(((ComplexNode*)root)->getLeft(), s+"0");
		calcEncodings(((ComplexNode*)root)->getRight(), s+"1");
	}else{
		encodings[((SimpleNode*)root)->c] = s;
	}
}

void Huffman::Compress(string filename){
	unsigned char writeBuffer;
	writeBuffer = 0;
	string enc;
	int encLength;
	int index;
	encLength = 0;
	int BufLen;
	BufLen = 0;
	int i = 0;

	ifstream inFile (filename.c_str());
	ofstream outFile ((filename+".mar").c_str());

	// Go to end of file to find the length of the file. 
	inFile.seekg(0, ios_base::end);

	long pos = inFile.tellg();

	cout << "Length of input file: " << pos << endl;

	// Now start from the beginning of the file. 
	inFile.seekg(0, ios_base::beg);


	for (int i = 0; i < 256; i++){
		outFile << encodings[i] << '\0';
	}

	// While not yet at end of file. 
	while(i != pos){
		enc = encodings[inFile.get()];
		encLength = enc.length();
		index = 0;
		i++;

		while(index < encLength){
			writeBuffer = writeBuffer << 1;
			// Logically OR the buffer with 1 or 0, depending on encoding. 
			writeBuffer = writeBuffer | (enc[index] - 48);
			index++;
			BufLen++;

			if (BufLen == 8){
				outFile << writeBuffer;
				writeBuffer = 0;
				BufLen = 0;
			}
		}
	}
	if (BufLen != 0){
		outFile << writeBuffer;
	}

	inFile.close();
	outFile.close();
}

void Huffman::Decode(string filename){
	ifstream inFile(filename.c_str());
	filename = filename.substr( 0 , filename.find_last_of('.')) + ".dec";
	cout << "Output file: " << filename << endl;
	ofstream outFile(filename.c_str());

	inFile.seekg(0, ios_base::end);
	long length = inFile.tellg();
	inFile.seekg(0, ios_base::beg);

	// Get the character encodings from the encoded file. 
	unsigned char c;
	for (int i = 0; i < 256; i++){
		encodings[i] = "";
		c = inFile.get();

		while (c != '\0'){
			encodings[i] += c;
			c = inFile.get();
		}
		cout << "Decoding " << i << ": " << encodings[i] << endl;
	}

	// Now start getting the information from the file. 

	c = inFile.get();

	long pos = inFile.tellg();
	cout << "*************                Pos : " << pos << endl; 
	string currenc = "";
	int timesShifted = 0;
	while(pos <= length){
		if (c % 2 == 0){
			currenc += '0';
		}else{
			currenc += '1';
		}
		c = c << 1;
		timesShifted++;

		if (timesShifted == 8){
//			cout << "Length: " << length << "   Pos: " << pos << endl;
			c = inFile.get();
			pos++;
			timesShifted = 0;
		}

		for (int i = 0; i < 256; i++){
			if (currenc.compare(encodings[i]) == 0){
				outFile << (char)i;
				currenc = "";
				break;
			}
		}
	}




	inFile.close();
	outFile.close();
}


int main(int argc, char ** argv){

	if (argc != 3){
		cout << "Not enough args!" << endl;
		cout << "Argc: " << argc << endl;
		return -1;
	}

	int table[256];
	Huffman *huff = new Huffman();

	string option = argv[1];
	cout << "Option: " << option << endl;

	if (option.compare("-e") == 0){

		Node * nodes[256];

		//Calculate the frequencies of each possible character. 
		huff->calcFreqs(argv[2], table);

		//Convert this table to nodes representing each character and it's frequency. 
		huff->freqsToNodes(table, nodes);

		SortNodes(nodes);

		huff->BuildTree(nodes);

		huff->calcEncodings(nodes[255]);
		/*
			 for (int i = 0; i < 256; i++){
			 cout << i << ": " << encodings[i] << endl;
			 }		
			 */
		huff->Compress(argv[2]);
		for (int i = 0; i < 256; i++){
			cout << i << ": " << encodings[i] << endl;
		}

	}else if (option.compare("-d") == 0){
		string filename = argv[2];
		filename += ".mar";
		cout << filename << endl;
		huff->Decode(filename);
	}
}
