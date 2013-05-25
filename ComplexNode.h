// Class to represent nodes in the tree which solely point to other nodes. 
// The position in the tree determines the character's encoding.
// 'Left' get an encoding of '0' and 'Right' gets '1'.
// Leaf Nodes are referred to as 'SimpleNodes' and these represent the individual characters
#include "Node.h"

class ComplexNode : public Node{
		public:
			ComplexNode(Node * n1, Node * n2);
			Node * getLeft();
			Node * getRight();
		private:
			Node *left, *right;
};

ComplexNode::ComplexNode(Node * n1, Node * n2){
		left = n1;
		right = n2;

		frequency = (n1->frequency + n2->frequency);
		Simple = false;
}

Node * ComplexNode::getLeft(){
	 	return left;
}

Node * ComplexNode::getRight(){
		return right;
}
