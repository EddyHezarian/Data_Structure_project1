#include<iostream>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;
//! Data structures---------------------------------
class Node {
private:
	friend class Stack;
	string value;
	int type;
	Node* dlink;
	Node* next;

public:
	//*Constructores------
	Node(string title, int inputType) {
		this->dlink = NULL;
		this->next = NULL;
		this->value = title;
		this->type = inputType;
	}
	Node(string inputTitle, int inputType, Node* inputDlink, Node* inputNext) {
		this->value = inputTitle;
		this->type = inputType;
		this->dlink = inputDlink;
		this->next = inputNext;
	}
	//*GETER functions------
	int getType() { return this->type; }
	string getValue() { return this->value; }
	Node* getDLink() { return this->dlink; }
	Node* getNext() { return this->next; }
	//*SETER functions------
	void setLastNext(Node* currentNode, Node* addedNode){
		Node* inc =  addedNode ;
		Node* tmp = currentNode->next;
		if (tmp) {
			setLastNext(tmp, addedNode);
		}
		else
			this->next = inc;
	}
	void setNext(Node* node) { this->next = node; }
	void setDLink(Node* node) { this->dlink = node; }
	void setLastDLink(Node* node, string val, int typ) {
		Node* inc = new Node(val, typ);
		Node* tmp = node->dlink;
		if (tmp) {
			setLastDLink(tmp, val, typ);
		}
		else
			this->dlink = inc;
	}
	//*general methods------
	bool isAnyDLink() {
		if (dlink == NULL) return false;
		else
			return true;

	}
	void showLayer() {
		Node* inc = this->dlink;
		while (inc != NULL) {
			cout << "\n\t" << inc->value << endl; 
			inc = inc->next;
		}
	}
	Node* getNextLayer(Node* current , string name) {
		Node* inc = current;
		bool flag = false;
		while (!flag) {
			if (inc->value == name) return inc->dlink;
			else inc = inc->next;
		} 
	}
};
class Stack {
private:
	int size;
	Node* top;
	Node* topDLink ;
	Node* firstNode; //?fisrt varible is for having access to first node in stack after adding more head nodes in stack !
public:
	//*constructor --> every thing will be null at start of creating an instanse 
	Stack() {
		this->size = 0;
		this->top = NULL;
		this->topDLink = NULL; 
		this->firstNode = NULL;
	};
	//*GETER functions -------
	int getSize() { return size; }
	Node* getFirst() { return firstNode; }
	//*SETER methods ----------
	void deleteList() {
		this->firstNode = NULL;
	}
	//*Add methods --> each node type have thier own add method 
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
		if (this->top->dlink == NULL) {
			this->top->setDLink(prop);
			this->topDLink = this->top->dlink;
		}/
		else // if this node is not the first property for this head node
		{
			prop->setNext(top->getDLink());
			top->setLastDLink(top, prop->value , 1);
		}
	}
	void _addDataToStack(Node* data) {
		if (this->top->dlink->dlink == NULL)
		{
			this->top->dlink->dlink = data;
		}
		else
		{
			data->next = this->top->dlink->dlink;
			this->top->dlink->dlink = data;
		}

	}

	//*layer methods ---> for add property feature ! 
	void _PushLayerToStack(Node* layer){
		if (size == 0) {
			this->top = layer;
			this->firstNode = layer;
			this->size++;
		}
		else
		{
			top->setDLink(layer);
			this->top = layer;
			this->size++;
		}
	}
	void _addPropToLayer(Node* layer) {
		this->top->setLastNext(this->top, layer);
	}
};
//! global list var here-----------------------------
Stack GlobalList = Stack();
string FilePath = "C:\\code\\cpp\\project_DS_1st\\ex.txt";
//!tools functions ----------------------------------
int actionDetectorFUNC(string line) {
	//!action detector finction -- > detect type of node in given sentece by file 
	string dash;
	string actionType;
	istringstream iss;
	iss.str(line);
	iss >> dash;
	iss >> actionType;
	if (actionType == "contact") { return 0; }
	else if (actionType == "property") { return 1; }
	else if (actionType == "data") { return 2; }
}
void updateGlobalList(Node* list, Node* dl, string name) {
	if (list != NULL) {
		if (list->getValue() != name) { updateGlobalList(list->getNext(), dl, name); }
		else
			list->setDLink(dl);
	}
}
string titleDetectorFUNC(string line) {
	size_t pos = line.find(":");
	if (pos == std::string::npos) { return ""; }
	return line.substr(pos + 2);
}
void addMethodMenu() {
	cout << "\n\t\tchoose add option  \n\n\n\t1-add New property\n\n\t2-add to Existing Property\n";

}
//!Features------------------------------------------
void _filler() {
	// filler function --> fill the global list with  data in file 
	ifstream _File;
	_File.open(FilePath);
	string _currentLine;

	while (getline(_File, _currentLine)) {
		int lineAction = actionDetectorFUNC(_currentLine);
		string lineTitle = titleDetectorFUNC(_currentLine);
		Node* instance = new Node(lineTitle, lineAction);
		switch (lineAction)
		{
		case 0:
			GlobalList._addHeadToStack(instance); break;

		case 1: GlobalList._addPropertyToStack(instance); break;

		case 2:GlobalList._addDataToStack(instance); break;
		}

	}
}

int _printerAll(Node* list) {
	if (list == NULL)
	{
		cout << "\nEnd of list ...\n ";
		return 0; 
	}
	//priter function --> print all the elements in global list with specefic form . 
	Node* inc = list;
	string value = inc->getValue();
	if (inc != NULL) {
		if (inc->getType() == 0) {
			cout << " - contact : " << value << endl;
			_printerAll(inc->getDLink());
		}
		else if (inc->getType() == 1) {
			cout << " - property : " << value << endl;
			_printerAll(inc->getDLink());
		}
		else if (inc->getType() == 2) {
			cout << " - data : " << value << endl;
		}
	}
	if (inc->getNext()) {
		_printerAll(inc->getNext());
	}

}

void _deleteAll() {
	// deleteAll Function --> delete the whole list 
	GlobalList.deleteList();
}

void _Addcontact() {
	//addContact Function ---> creat a single contact with single property and data . 
	// warning --> user can not enter empty value for any items ...


	string Namevalue ;
	do {
		cout << "enter name for contact : ";
		getline(cin, Namevalue);
		

	} while (Namevalue == "");

	Node* newContact = new Node(Namevalue, 0, NULL, NULL);

	GlobalList._addHeadToStack(newContact);

	cout << "\ncontact create successfully ... " << Namevalue << "\n\n";


	// need  function to save list to file ... 

}

void _addPropOnly() {

	Node* instance = GlobalList.getFirst();
	string name;
	bool flag = false;
	do {
		cout << "\n enter contact name for adding property : ";
		getline(cin, name);
		if (name == "EXT")exit(1);
		while (instance)
		{
			if (instance->getValue() == name)
			{
				flag = true;
				break;

			}
			else
				instance = instance->getNext();
		}
		if (!flag) { cout << "\nname dosent exist--- try again\n type EXT for cancel adding property ....\n "; }

	} while (!flag);
	
	if (!instance->getDLink())
	{ // first property for contact 
	  //Passed^^^
		cout << "\n\t\tadding first property\n\n";
		cout << "\n\tChoose a title :  ";
		string value;
		getline(cin, value);
		Node* dl   = new Node(value,1);
		//continue to enter data :
		int methodType=1;
		while (methodType != 2) {
			cout << "\n\t\t choose an item :\n\n\t1-add property\n\t2-add data\n\n>> ";
			cin >> methodType; 
			if (methodType == 1) {
				cout << "\n adding property : enter a title : ";
				cin.ignore();
				getline(cin, value);
				dl->setLastDLink(dl, value, 1);
			}
			else
			{
				cout << "\n\tadding data \n\t: enter a title : ";
				cin.ignore();
				getline(cin, value);
				dl->setLastDLink(dl, value, 2);
			}
		}
		updateGlobalList(GlobalList.getFirst(), dl, name);
	}
	
	else {
		Stack Layers = Stack();
		Node* _currentLayer = instance;
		string method = "0";
		while (method != "1")
		{
			cout << "\n\t\t adding property \n\t\t( select an layer or Enter (1) for adding in current layer\nlayers: \n";
			_currentLayer->showLayer();
			getline(cin, method);
			if (method == "1") {

				//do somthing 
				break; 
			}

			_currentLayer = _currentLayer->getNextLayer(_currentLayer, method);
			Layers._PushLayerToStack(_currentLayer);

		}

	}

}

int _deleteFromFile() {
	//deleteFromFile Function ---> delete All data from File and get ready for updateFile Function 
	// Passed ^^^
	fstream ofs;
	ofs.open(FilePath, ios::out | ios::trunc);
	ofs.close();
	return 0;
}

int _updateFile(Node* list) {
	//ofstream openfile(FilePath, ios::app);
	//passed ^^^

	if (list == NULL)
	{
		cout << "\nEnd of list ...\n ";
		return 1;
	}
	//priter function --> print all the elements in global list with specefic form . 
	Node* inc = list;
	string value = inc->getValue();
	if (inc != NULL) {
		if (inc->getType() == 0) {
			ofstream openfile(FilePath, ios::app);
			openfile << " - contact : " << value << endl;
			openfile.close();
			_updateFile(inc->getDLink());
		}
		else if (inc->getType() == 1) {
			ofstream openfile(FilePath, ios::app);
			openfile << " - property : " << value << endl; openfile.close();
			_updateFile(inc->getDLink());
		}
		else if (inc->getType() == 2) {
			ofstream openfile(FilePath, ios::app);
			openfile << " - data : " << value << endl; openfile.close();
		}
	}
	if (inc->getNext()) {
		_updateFile(inc->getNext());
	}

}

//-------------------------------------
int main() {
	_filler();
    _printerAll(GlobalList.getFirst());
	cout << "\n-----------------------------\n";

}