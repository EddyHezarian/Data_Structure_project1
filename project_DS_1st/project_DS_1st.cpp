

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
	//Constructores------
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
	//GETER functions------
	int getType() { return this->type; }
	string getValue() { return this->value; }
	Node* getDLink() { return this->dlink; }
	Node* getNext() { return this->next; }
	//SETER functions------
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
	//general methods------
	bool isAnyDLink() {
		if (dlink == NULL) return false;
		else
			return true;

	}
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

	//GETER functions -------
	int getSize() { return size; }
	Node* getFirst() { return firstNode; }

	//SETER methods ----------
	void deleteList() {
		this->firstNode = NULL;
	}

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
		if (this->top->dlink == NULL) {
			this->top->setDLink(prop);
		}
		else // if this node is not the first property for this head node
		{
			prop->setNext(top->getDLink());
			top->setDLink(prop);
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
};
// global list var here-----------------------------
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
	else if (actionType == "property") { return 1; }
	else if (actionType == "data") { return 2; }

}
string titleDetectorFUNC(string line) {
	size_t pos = line.find(":");
	if (pos == std::string::npos) { return ""; }
	return line.substr(pos + 2);
}
void addMethodMenu() {
	cout << "\n\t\tchoose add option  \n\n\n\t1-add New property\n\n\t2-add to Existing Property\n";

}
//Features-----------------------------------------------------------
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


	string Namevalue, propertyValue, dataValue;
	do {
		cout << "enter name for contact : ";
		getline(cin, Namevalue);
		cout << "add a property title  : ";
		getline(cin, propertyValue);
		cout << "add a data for " << propertyValue << " : ";
		getline(cin, dataValue);

	} while (Namevalue == "" || propertyValue == "" || dataValue == "");
	Node* newData = new Node(dataValue, 2);
	Node* newProperty = new Node(propertyValue, 1, newData, NULL);
	Node* newContact = new Node(Namevalue, 0, newProperty, NULL);

	GlobalList._addHeadToStack(newContact);

	cout << "\ncontact create successfully ... " << Namevalue << "\n\n";


	// need  function to save list to file ... 

}

void _addPropertyOnly() {
	//addPropertyOnly Function ---> for adding property whether its data type or its property we use this function.
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
	// moving global instance to the right contact index ^ 

	int methodType; //this varable is selcecting add method  1-new property 2-add in existing property 
	addMethodMenu();
	cin >> methodType;
	switch (methodType)
	{
	case 1: {
		bool isFisrtProp = true;
		string valueOfProperty;
		int typeOfProperty = 1;
		cout << "\nadding fisrt property...\n\n ";
		do {
			string valueOfProperty;
			int typeOfProperty;

			if (!isFisrtProp) {// first option have to be a property type ! cuz its new for contact 
				cout << "\n\t1-add Property :\n\n\t2-add Data : \n";
				cin >> typeOfProperty;
			}
			isFisrtProp = false;
			cout << "\n\t title : ";
			cin >> typeOfProperty;
			//add with built in method 
			instance->setLastDLink(instance, valueOfProperty, typeOfProperty);
			cout << "\n\n_________________proccess finished_________________________\n\n";

		} while (typeOfProperty == 2);


	}; break;
	case 2: {};
	default: {
		system("color 41");
		cout << "item not found ....";
		exit(1);
	};
		   break;
	}


	// save file func


}

int _deleteFromFile() {
	fstream ofs;
	ofs.open(FilePath, ios::out | ios::trunc);
	ofs.close();
	return 0;
}

// update file 
int _updateFile(Node* list) {
	//ofstream openfile(FilePath, ios::app);

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
			ofstream openfile(FilePath, ios::app);
			cout << " - contact : " << value << endl;
			openfile.close();
			_printerAll(inc->getDLink());
		}
		else if (inc->getType() == 1) {
			ofstream openfile(FilePath, ios::app);
			openfile << " - property : " << value << endl; openfile.close();
			_printerAll(inc->getDLink());
		}
		else if (inc->getType() == 2) {
			ofstream openfile(FilePath, ios::app);
			openfile << " - data : " << value << endl; openfile.close();
		}
	}
	if (inc->getNext()) {
		_printerAll(inc->getNext());
	}

}

//-------------------------------------
int main() {
	_filler();
	int a = _printerAll(GlobalList.getFirst());

	cout << "\n-----------------------------\n";
	_deleteFromFile();
	//_updateFile(GlobalList.getFirst());
	int d = _printerAll(GlobalList.getFirst());

}