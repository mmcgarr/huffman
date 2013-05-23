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
