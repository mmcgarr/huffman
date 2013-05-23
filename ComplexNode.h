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
