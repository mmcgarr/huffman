// Class from which both ComplexNode and SimpleNode inherit.
// Through superclassing we can say that any ComplexNode in the tree points to a 'Node'
// This can be either a Simple or Complex node. 
#pragma once

class Node{
	protected:
		Node(){};
	private:
	public:
		bool Simple;
		int frequency;
		bool isSimple();
};

bool Node::isSimple(){
	return Simple;
}
