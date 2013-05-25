// Class representing a leaf node in the Huffman tree. 
// This points to no other nodes. 
// Only has a character and it's frequency. 
// For simplicity it uses the isSimple attribute of the parent to identify itself as simple. Not very elegant. 

#include "Node.h"

class SimpleNode: public Node{
	public:
		unsigned int c;
		SimpleNode(unsigned int, int);
		int getC();
};

SimpleNode::SimpleNode(unsigned int ch, int freq){ 
	c = ch;
	frequency = freq;
	Simple = true;
}

int SimpleNode::getC(){
	return c;
}
