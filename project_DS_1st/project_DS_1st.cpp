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
	int indent;
	Node* dlink;
	Node* next;

public:
	//*Constructores------
	Node(string title, int inputType) {
		this->dlink = NULL;
		this->indent = 0;
		this->next = NULL;
		this->value = title;
		this->type = inputType;
	}
	Node(string title, int inputType, int inputindent) {
		this->dlink = NULL;
		this->indent = inputindent;
		this->next = NULL;
		this->value = title;
		this->type = inputType;
	}
	Node(string inputTitle, int inputType, Node* inputDlink, Node* inputNext, int inputindent) {
		this->value = inputTitle;
		this->indent = inputindent;
		this->type = inputType;
		this->dlink = inputDlink;
		this->next = inputNext;
	}
	//*GETER functions------
	int getType() { return this->type; }
	string getValue() { return this->value; }
	Node* getDLink() { return this->dlink; }
	Node* getNext() { return this->next; }
	int getIndent() { return this->indent; }
	//*SETER functions------
	//TODO setLastNext func
	void _addProp(Node* node, Node* prop, Node* parent) {
		Node* inc = node;
		if (inc == NULL)
		{
			node = inc;
		}
		if (inc != NULL) {
			if (inc == parent) {
				if (inc->getDLink() == NULL) {
					inc->setDLink(prop);
				}
				else
				{
					if (inc->dlink->type == 2) {
						inc->setNext(prop);
					}
					else
					{
						inc->setDLink(prop);
					}
				}
			}
			if (inc->type == 1) {
				_addProp(inc->dlink, prop, parent);
			}
			else if (inc->type == 2)
				_addProp(inc->next, prop, parent);
		}
	}
	void AddPropertyFeature(Node* node, string value, string parent)
	{
		Node* inc = node;
		if (inc == NULL)
		{
			node = inc;
		}
		if (inc != NULL)
		{
			if (inc->value == parent)
			{

				if (inc->dlink == NULL)
				{
					Node* item = new Node(value, 1, inc->indent + 1);
					inc->dlink = item;
				}
				else {
					if (inc->dlink->type == 2)
					{

						if (inc->next == NULL)
						{
							Node* item = new Node(value, 1, inc->indent);
							inc->next = item;
						}

						else
						{
							Node* item = new Node(value, 1, inc->indent);
							item->next = inc->next;
							inc->next = item;
						}
					}
					else {
						Node* item = new Node(value, 1, inc->indent + 1);
						inc->dlink = item;
					}
				}
			}
			if (inc->type == 1)
			{
				AddPropertyFeature(inc->dlink, value, parent);
			}
			else if (inc->type == 2) {
				AddPropertyFeature(inc->next, value, parent);
			}
		}
	}



	void _addData(Node* node, Node* data, Node* parent)
	{

		Node* inc = node;
		if (node == NULL)
		{
			node = inc;
		}
		if (inc)
		{
			if (inc == parent)
			{
				if (inc->dlink == NULL)
				{
					inc->dlink = data;
				}
				else
				{
					Node* tmp = inc->dlink;
					data->next = tmp;
					inc->dlink = data;

				}
			}
			if (inc->type == 1)
				if (inc->dlink->type == 2)
					_addData(inc->next, data, parent);
				else
					_addData(inc->dlink, data, parent);
			else if (inc->type == 2)
				_addData(inc->next, data, parent);
		}

	}
	void setNext(Node* node) { this->next = node; }
	void setDLink(Node* node) { this->dlink = node; }
	void setLastDLink(Node* node, string val, int typ, int indent) {
		Node* inc = new Node(val, typ, indent);
		if (node) {
			setLastDLink(node->dlink, val, typ, indent);
		}
		else
			node = inc;


	}
	void setLastNext(Node* node, Node* item) {

		Node* tmp = node->dlink;
		if (tmp) {
			setLastNext(tmp, item);
		}
		else
			this->dlink = item;
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
	Node* getNextLayer(Node* current, string name) {
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
	Node* topDLink;
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
	Node* getTop() { return this->top; }
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
	// void _addPropertyToStack(Node* prop) {
	// 	//* if this is the first property 
	// 	if (this->top->dlink == NULL) {
	// 		this->top->setDLink(prop);
	// 		this->topDLink = this->top->dlink;
	// 	}
	// 	else //? if this node is not the first property for this head node
	// 	{
	// 		prop->setNext(top->getDLink());
	// 		top->setLastDLink(top, prop->value, 1);
	// 	}
	// }
	// void _addDataToStack(Node* data) {
	// 	if (this->top->dlink->dlink == NULL)
	// 	{
	// 		this->top->dlink->dlink = data;
	// 	}
	// 	else
	// 	{
	// 		data->next = this->top->dlink->dlink;
	// 		this->top->dlink->dlink = data;
	// 	}
	// }


	//*layer methods ---> for add property feature ! 
	void _PushLayerToStack(Node* layer) {
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
string FilePath = "C:\\Users\\Eddy\\Desktop\\ex.txt";
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
void PrintContactTree(Node* contact) {
	Node* inc = contact;
	string value = inc->getValue();
	if (inc == NULL)
		cout << "end of list...\n";
	if (inc)
	{
		if (inc->getType() == 1) {
			int indent = inc->getIndent();
			for (int i = 1; i <= indent; i++)
				cout << "\t";
			cout << "property : " << value << endl;
			PrintContactTree(inc->getDLink());
		}
		else if (inc->getType() == 2) {
			int indent = inc->getIndent();
			for (int i = 1; i <= indent; i++)
				cout << "\t";
			cout << "data : " << value << endl;
		}
	}
	if (inc->getNext())
		PrintContactTree(inc->getNext());
}
string titleDetectorFUNC(string line) {
	size_t pos = line.find(":");
	if (pos == std::string::npos) { return ""; }
	return line.substr(pos + 2);
}
void addMethodMenu() {
	cout << "\n\t\tchoose add option  \n\n\n\t1-add New property\n\n\t2-add to Existing Property\n";
}
int indentCounterFUNC(string str) {
	//* indents counter Function ---> proccessing indents in file for recognizinging the realations between lines . 
	int indents = 0;
	for (int i = 0; str[i] != 32; i++)
	{
		indents++;
	}
	return indents - 1;
}
//!Features------------------------------------------
void _filler() {
	//* filler function --> fill the global list with  data in file 
	ifstream _File;
	_File.open(FilePath);
	string _currentLine;
	Node* parent = new Node(" ", 0);
	Stack DLStack = Stack();
	while (getline(_File, _currentLine)) {
		int lineAction = actionDetectorFUNC(_currentLine);
		int lineIndent = indentCounterFUNC(_currentLine);
		string lineTitle = titleDetectorFUNC(_currentLine);
		Node* instance = new Node(lineTitle, lineAction, lineIndent);
		switch (lineAction)
		{
		case 0: {
			if (GlobalList.getSize() != 0) { GlobalList.getTop()->setDLink(DLStack.getFirst()); }
			DLStack.deleteList();
			GlobalList._addHeadToStack(instance); break;
		}
		case 1: {
			if (lineIndent == 1) { DLStack._addHeadToStack(instance); }
			else {
				DLStack.getTop()->_addProp(DLStack.getTop(), instance, parent);
			}
			parent = instance;
			break;
		}
		case 2: {
			DLStack.getTop()->_addData(DLStack.getTop(), instance, parent); break;
		}
		}
	}
	GlobalList.getTop()->setDLink(DLStack.getFirst());
}
int _printerAll(Node* list) {//*priter function --> print all the elements in global list with specefic form .
	if (list == NULL)
	{
		cout << "\nEnd of list ...\n ";
		return 0;
	}
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
void _deleteAll() {//* deleteAll Function --> delete the whole list 
	GlobalList.deleteList();
}
void _showContactTree(Node* list, string name) {

	Node* inc = list;
	while (inc->getValue() != name)
		inc = inc->getNext();
	PrintContactTree(inc->getDLink());
}
void _Addcontact() {//*addContact Function ---> creat a single contact with single property and data . 
	// warning --> user can not enter empty value for any items ...
	string Namevalue;
	do {
		cout << "enter name for contact : ";
		getline(cin, Namevalue);
	} while (Namevalue == "");
	Node* newContact = new Node(Namevalue, 0, NULL, NULL, 0);
	GlobalList._addHeadToStack(newContact);
	cout << "\ncontact create successfully ... " << Namevalue << "\n\n";
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
		int indent = 1;
		getline(cin, value);
		Node* dl = new Node(value, 1, indent);
		updateGlobalList(GlobalList.getFirst(), dl, name);
	}
	else {
		//?showing the contact tree 
		_showContactTree(GlobalList.getFirst(), instance->getValue());
		//? choosing the location in tree to add property .
		cout << "\n\t\tenter the name of the parent : ";
		string loc;
		getline(cin, loc);

		//?creat new property 
		cout << "\n\t\tadding first property\n\n";
		cout << "\n\tChoose a title :  ";
		string value;
		getline(cin, value);
		//add to instance
		instance->AddPropertyFeature(instance->getDLink(), value, loc);

		updateGlobalList(GlobalList.getFirst(), instance->getDLink(), name);

	}
}
int _deleteFromFile() {	//*deleteFromFile Function ---> delete All data from File and get ready for updateFile Function 

	// Passed ^^^
	fstream ofs;
	ofs.open(FilePath, ios::out | ios::trunc);
	ofs.close();
	return 0;
}
int _updateFile(Node* list) {

	if (list == NULL)
	{
		cout << "\nEnd of list ...\n ";
		return 1;
	}
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
			int  indent = inc->getIndent();
			ofstream openfile(FilePath, ios::app);
			for (int i = 1; i <= indent; i++)
				openfile << "\t";
			openfile << "- property : " << value << endl; openfile.close();
			_updateFile(inc->getDLink());
		}
		else if (inc->getType() == 2) {
			int  indent = inc->getIndent();
			ofstream openfile(FilePath, ios::app);
			for (int i = 1; i <= indent; i++)
				openfile << "\t";
			openfile << "- data : " << value << endl; openfile.close();
		}
	}
	if (inc->getNext()) {
		_updateFile(inc->getNext());
	}

}
//-------------------------------------
int main() {
	_filler();
	_addPropOnly();
	_printerAll(GlobalList.getFirst());
}