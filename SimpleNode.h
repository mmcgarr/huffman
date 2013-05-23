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
