#include<iostream>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;




class Node {
private:
	friend class Stack;
	string value;
	int type;

	Node* dlink;
	Node* next;
	
public:
	
	Node(string title, int inputType) {
		dlink = NULL;
		next = NULL;
		value = title;
		type = inputType;
	}
	Node(string inputTitle, int inputType, Node* inputDlink, Node* inputNext) {
		value = inputTitle;
		type = inputType;
		dlink = inputDlink;
		next = inputNext;
	}
	void setNext(Node* node) { this->next = node; }
	bool isAnyDLink() { 
		if (dlink == NULL) return false;
		else
			return true;
		
	}
	Node* getDLink() { return this -> dlink; }
	Node* getNext() { return this -> next; }
	void setDLink(Node* node) { this->dlink = node; }

};

class Stack {
private:
	int size;
	Node* top;
	Node* firstNode; // fisrt varible is for having access to first node in stack after adding more head nodes in stack !
public:
	//constructor --> every thing will be null at start of creating an instanse 
	Stack() {
		this->size = 0;
		this->top = NULL;
		this->firstNode = NULL;
	};
	int getSize() { return size; }
	//Add methods --> each node type have thier own add method 
	void _addHeadToStack(Node* head) {
		if (size == 0) {
			this->top = head;
			this->firstNode = head;
			this->size++;
		}
		else
		{
			top->setNext(head);
			this->top = head;
			this->size++;
		}

	}

	void _addPropertyToStack(Node* prop) {
		// if this is the first property 
		if (!this->top->dlink == NULL) {
			this->top->setDLink(prop);
		}
		else // if this node is not the first property for this head node
		{
			prop->setNext(top->getDLink());
			top->setDLink(prop);
		}


	}

	void _addDataToStack(Node* data) {
		if(this->top->dlink->dlink == NULL )
		{
			this->top->dlink->dlink = data; 
		}
		else
		{
			data->next = this->top->dlink->dlink;
			this->top->dlink->dlink = data;
		}
	
	}
};


// global list var here
Stack GlobalList = Stack();
string FilePath = "C:\\code\\cpp\\project_DS_1st\\ex.txt";

//tools functions --------------------------------------------------------------------------
int actionDetectorFUNC(string line) {
	//action detector finction -- > detect type of node in given sentece by file 
	string dash; 
	string actionType; 
	istringstream iss;
	iss.str(line);
	iss >> dash;
	iss >> actionType;
	if (actionType == "contact") { return 0; }
	else if(actionType == "property"){ return 1; }
	else if(actionType == "data"){ return 2; }

}

string titleDetectorFUNC(string line) {
	size_t pos = line.find(":");
	if (pos == std::string::npos) { return ""; }
	return line.substr(pos + 2);
}

void filller() {
	// filler function --> fill the global list with  data in file 

	// open file 

	//access to line 

	// store aaction  // store value >> himed reza rohi 

	// switch on action 

	ifstream _File;
	_File.open(FilePath);
	string _currentLine; 
	
	while (getline(_File, _currentLine)) {
		int lineAction = actionDetectorFUNC(_currentLine);
		string lineTitle = titleDetectorFUNC(_currentLine);
		Node* instance =  new Node(lineTitle , lineAction);
		switch (lineAction)
		{
			case 0:
				GlobalList._addHeadToStack(instance); break;
			
			case 1: GlobalList._addPropertyToStack(instance); break;

			case 2:GlobalList._addDataToStack(instance); break;
		}
		
	}
		












	
}
//

int main() {

	

	
}