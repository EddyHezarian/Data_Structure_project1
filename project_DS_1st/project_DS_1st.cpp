#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include "project_DS_1st.h"
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
	void AddPropertyFeature(Node* node, string value, string parent, bool option)
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
				if (option == true) {
					Node* item = new Node(value, 1, inc->indent );
					inc->setNext(item);
				}
				else {
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
			}
			
			
			
			
			if (inc->type == 1)
			{
				AddPropertyFeature(inc->dlink, value, parent,option);
			}
			else if (inc->type == 2) {
				AddPropertyFeature(inc->next, value, parent, option);
			}
		}
	}
	void addDataFeature(Node* node, string value, string parent)
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
				if (inc->type == 2) {
					//Node* item = ;
					inc->next = new Node(value, 2, inc->indent);
				}
				else {
					if (inc->dlink == NULL)
					{
						//Node* item = new Node(value, 2, inc->indent + 1);
						inc->dlink = new Node(value, 2, inc->indent + 1);//Pass
					}
					else {
						cout << "\n\tyou selected the right parent !\n";
					}
				}
			}
			if (inc->type == 1)
			{
				addDataFeature(inc->dlink, value, parent);
			}
			else if (inc->type == 2) {
				addDataFeature(inc->next, value, parent);
			}
		}
	}
	int DeleteItemFeature(Node* node, string parent)
	{
		Node* inc = node;
		if (inc == NULL)
		{
			node = inc;
		}
		if (inc != NULL)
		{

			if (inc->value == parent) {
				if (inc->next == NULL) {
					inc = NULL;
					return 0;
				}
				else
				{
					Node* item = inc->next;
					inc = item;
					return 0;
				}
			}
			else if (inc->next != NULL) {
				if (inc->next->value == parent)
				{
					if (inc->next->next == NULL) {
						inc->next = NULL;

					}
					else {
						Node* item = inc->next->next;
						inc->next = item;
					}
				}
			}
			else if (inc->dlink != NULL) {
				if (inc->dlink->value == parent)
				{
					if (inc->dlink->next == NULL) {
						inc->dlink = NULL;

					}
					else {
						Node* item = inc->dlink->next;
						inc->dlink = item;

					}
				}

			}
			if (inc->type == 1)
			{
				DeleteItemFeature(inc->dlink, parent);
			}
			else if (inc->type == 2) {
				DeleteItemFeature(inc->next, parent);
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
		this->top = NULL;
		this->size = 0;
	}
	//*Add methods --> push to stack  
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
	bool _searchForItem(string value) {
		Node* inc = this->firstNode;
		while (inc != NULL)
		{
			if (inc->value == value)
			{
				return true;
			}
			inc = inc->next;
		}
		return false;
	}
	//pop methods --->
	void pop() {
		Node* inc = this->top;
		Node* inc2 = this->firstNode;
		while (inc2->next != inc)
			inc2 = inc2->next;
		this->top->next = NULL;
		this->top = inc2;
		delete(inc);
		size--;
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
int PrintContactTree(Node* contact) {
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
			if (inc->getDLink() == NULL)
				return 0;
			else
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
int _menu() {
	int i;
	system("Cls");
	cout << "\n\t\t Contact APP\n--------choose an option:--------\n\n\t1 - print All List\n\t2 - add contact\n\t3 - show a contact info\n\t4 - add property to contact\n\t5 - add data to contact\n";
	cout << "\t6 - delete List\n\t7 - delete item\n\t8 - search item \n\t 9 - exit\n\n>>  ";
	cin >> i;
	return i;
}
void LayerStylePrintStack(Stack stack) {
	Node* inc = stack.getFirst();
	int indent = inc->getIndent();
	while (inc)
	{
		int indent = inc->getIndent();
		for (int j = 1; j <= indent; j++)
			cout << "\t";
		cout << inc->getValue() << endl;
		inc = inc->getNext();
	}
	exit(0);
}
//!Features------------------------------------------
void _filler() {
	//* filler function --> fill the global list with  data in file 
	ifstream _File;
	_File.open(FilePath);
	string _currentLine;
	Node* parent = new Node(" ", 0);//? this node will specify the parent of data and property by indent 
	Stack DLStack = Stack(); //? once contact created --> this stack will start to build and collect all of property of contact  than atach as DLink of contact 
	while (getline(_File, _currentLine)) {
		int lineAction = actionDetectorFUNC(_currentLine);//? detect the Type of line whether is Contact , Property or Data .
		int lineIndent = indentCounterFUNC(_currentLine); //? detect indent of Line 
		string lineTitle = titleDetectorFUNC(_currentLine);//? detect Title of Line 
		Node* instance = new Node(lineTitle, lineAction, lineIndent);
		switch (lineAction)
		{
		case 0: { //! action 0 = Contact Type 

			if (GlobalList.getSize() != 0) { //? befor creating new contact set Dlink for last contact in globlal list 
				GlobalList.getTop()->setDLink(DLStack.getFirst());
			}
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
int _printerAll(Node* list) {
	//*priter function --> print all the elements in global list with specefic form .
	if (list == NULL)
	{
		cout << "\nEnd of list ...\n ";
		return 1;
	}
	Node* inc = list;
	string value = inc->getValue();
	if (inc != NULL) {

		if (inc->getType() == 0) {

			cout << " - contact : " << value << endl;
			_printerAll(inc->getDLink());
		}
		else if (inc->getType() == 1) {
			int indent = inc->getIndent();
			for (int i = 1; i <= indent; i++)
				cout << "\t";
			cout << " - property : " << value << endl;
			if(inc->getDLink()!= NULL)
			_printerAll(inc->getDLink());
		}
		else if (inc->getType() == 2) {
			int indent = inc->getIndent();
			for (int i = 1; i <= indent; i++)
				cout << "\t";
			cout << " - data : " << value << endl;
		}
	}
	if (inc->getNext()) {
		_printerAll(inc->getNext());
	}

}
void _deleteAll() {
	//* deleteAll Function --> delete the whole list 
	GlobalList.deleteList();
	cout << "\n\tAll data has been deleted\n\n ";
}
void _showContactTree(Node* list, string name) {
	//* showContactTree Function ---> show info of selected contact .
	Node* inc = list;
	bool flag = true;
	while (inc->getValue() != name) {
		inc = inc->getNext();
		if (inc == NULL) {
			flag = false;
			cout << "\n\tContact NOT found \n\n";
			break;
		}
	}
	if (flag) {
		PrintContactTree(inc->getDLink());
		system("pause");
	}
}
void _Addcontact() {
	//*addContact Function ---> creat a single contact with single property and data . 
	//* warning --> user can not enter empty value for any items ...
	string Namevalue;
	do {
		cout << "\n\tEnter Name For Contact : ";
		cin.ignore();
		getline(cin, Namevalue);
	} while (Namevalue == "");
	Node* newContact = new Node(Namevalue, 0, NULL, NULL, 0);
	GlobalList._addHeadToStack(newContact);
	cout << "\ncontact create successfully ... " << Namevalue << "\n\n";
	system("pause");
}
void _addPropOnly() {
	Node* instance = GlobalList.getFirst();
	string name;
	bool flag = false;
	do {
		cout << "\n enter contact name for adding property : ";
		cin.ignore();
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
				if (instance->getNext() == NULL)
					instance = GlobalList.getFirst();
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
		cout << "place as Next of Property ?\n\t\t1- yes\n\t\t2-NO\n>> ";
		int option ;
		bool flag = false ;
			cin >> option;
			if (option == 1 )
				flag = true;	
		//?creat new property 
		cout << "\n\t\tadding first property\n\n";
		cout << "\n\tChoose a title :  ";
		cin.ignore();
		string value;
		getline(cin, value);
		//add to instance
		if(flag)
		instance->AddPropertyFeature(instance->getDLink(), value, loc,true);
		else 
			instance->AddPropertyFeature(instance->getDLink(), value, loc, false);
		updateGlobalList(GlobalList.getFirst(), instance->getDLink(), name);

	}
}
void _addDataOnly() {
	Node* instance = GlobalList.getFirst();
	string name;
	bool flag = false;
	do {
		cout << "\n enter contact name for adding property : ";
		cin.ignore();
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
				if (instance->getNext() == NULL)
					instance = GlobalList.getFirst();
				else
					instance = instance->getNext();
		}
		if (!flag) { cout << "\nname dosent exist--- try again\n type EXT for cancel adding property ....\n "; }
	} while (!flag);
	if (!instance->getDLink())
	{ // first property for contact 
	  //Passed^^^
		cout << "must add a property first...";
	}
	else {
		//?showing the contact tree 
		_showContactTree(GlobalList.getFirst(), instance->getValue());
		//? choosing the location in tree to add property .
		cout << "\n\t\tenter the name of the parent : ";
		string loc;
		getline(cin, loc);
		//?creat new property 
		cout << "\n\t\tadding first Data\n\n";
		cout << "\n\tChoose a title :  ";
		string value;
		getline(cin, value);
		//?add to instance
		instance->addDataFeature(instance->getDLink(), value, loc);
		//?update global list 
		updateGlobalList(GlobalList.getFirst(), instance->getDLink(), name);
	}
}
void _deleteItem() {
	//* deleteItem Function---> delete an item in global list then update file 
	Node* instance = GlobalList.getFirst();
	string name;
	bool flag = false;
	//? find contact in global list 
	do {
		cout << "\n enter contact name for adding property : ";
		cin.ignore();
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
				if (instance->getNext() == NULL)
					instance = GlobalList.getFirst();
				else
					instance = instance->getNext();
		}
		if (!flag) { cout << "\nname dosent exist--- try again\n type EXT for cancel adding property ....\n "; }
	} while (!flag);
	//? show contact tree 
	_showContactTree(GlobalList.getFirst(), instance->getValue());
	//? selecting item for delete 
	cout << "\n\t\tDELETE ITEM \n\tNAME OF ITEM : ";
	string loc;
	getline(cin, loc);
	//? delete operation in class 
	instance->DeleteItemFeature(instance->getDLink(), loc);
	//? update global list 
	updateGlobalList(GlobalList.getFirst(), instance->getDLink(), name);
}
int _search(Node* list, string item, Stack stack) {
	//*search function --> search for a data and return its whole route  .
	if (list == NULL)
	{
		cout << "\nitem not fount\n ";
		return 1;
	}
	Node* inc = list;
	string value = inc->getValue();
	if (inc != NULL) {
		if (inc->getType() == 0) {
			//clear list 
			stack.deleteList();
			// push head 
			Node* tmp = new Node(inc->getValue(), 0, 0);
			stack._addHeadToStack(tmp);
			//cout << " - contact : " << value << endl;
			_search(inc->getDLink(), item, stack);
		}
		else if (inc->getType() == 1) {
			// push head 
			Node* tmp = new Node(inc->getValue(), 1, inc->getIndent());
			stack._addHeadToStack(tmp);
			_search(inc->getDLink(), item, stack);
		}
		else if (inc->getType() == 2) {
			if (inc->getValue() == item) {
				Node* tmp = new Node(inc->getValue(), 2, inc->getIndent());
				stack._addHeadToStack(tmp);
				LayerStylePrintStack(stack);
			}
			else {
				if (inc->getNext() == NULL) {}
			}
		}
	}
	if (inc->getNext()) {
		_search(inc->getNext(), item, stack);
	}

}
int _deleteFromFile() {
	//*deleteFromFile Function ---> delete All data from File and get ready for updateFile Function 
	fstream ofs;
	ofs.open(FilePath, ios::out | ios::trunc);
	ofs.close();
	return 0;
}
int _updateFile(Node* list, int size) {
	//* updateFile Function ---> update file after changing datas 
	if (list == NULL)
	{
		cout << "\nEnd of list ...\n ";
		return 1;
	}
	Node* inc = list;
	string value = inc->getValue();
	if (inc != NULL) {
		if (inc->getType() == 0) {
			size++;
			ofstream openfile(FilePath, ios::app);
			if (size > 1)
				openfile << "\n";
			openfile << " - contact : " << value;
			openfile.close();
			_updateFile(inc->getDLink(), size);
		}
		else if (inc->getType() == 1) {
			int  indent = inc->getIndent();
			ofstream openfile(FilePath, ios::app);
			openfile << "\n";
			for (int i = 1; i <= indent; i++)
				openfile << "\t";
			openfile << "- property : " << value; openfile.close();
			_updateFile(inc->getDLink(), size);
		}
		else if (inc->getType() == 2) {
			int  indent = inc->getIndent();
			ofstream openfile(FilePath, ios::app);
			openfile << "\n";
			for (int i = 1; i <= indent; i++)
				openfile << "\t";
			openfile << "- data : " << value; openfile.close();
		}
	}
	if (inc->getNext()) {
		_updateFile(inc->getNext(), size);
	}
}
//------------------------------------
int main() {
	_filler();
	int menuOption;
	while (true)
	{
		system("color F0");
		menuOption = _menu();
		
		switch (menuOption)
		{
		case 1: { //* print ALL LIST 
			system("CLs");
			system("COLOR F2");
			cout << "\n\tPrint ALL List\n\n";
			_printerAll(GlobalList.getFirst()); 
			system("pause");break;
		}
		case 2: { //? Add CONTACT
			system("CLs");
			system("COLOR F1");
			cout << "\n\tAdd Contact\n\n";
			_Addcontact();
			_deleteFromFile();
			_updateFile(GlobalList.getFirst(), 0); break;
		}
		case 3: { //* print CONTACT INFO
			system("CLS");
			system("COLOR FA");
			cout << "\n\tPrint contact Info\n\n";
			cout << "\tEnter the contact name : ";
			string name;
			cin.ignore();
			getline(cin, name);
			cout << endl;
			Node* inc = GlobalList.getFirst();
			while (true)
			{
				if (name == inc->getValue()) {
					system("CLS");
					cout << name<<"\n";
					_showContactTree(GlobalList.getFirst(), name);
					cout << "\n\n\n";
					break;
				}

				if (inc->getNext() != NULL)
					inc = inc->getNext();
				else {
					cout << "\n\tcontact not Found ... try again\n\n\tname of contact : ";
					//cin.ignore();
					getline(cin, name);
					if (name == "EXT")break;
					cout << endl;
					inc = GlobalList.getFirst();
				}
			}
			//_showContactTree(GlobalList.getFirst(), name);
			break;
		}
		case 4: { //? add PROPERTY
			system("CLs");
			system("COLOR F1");
			cout << "\n\tAdd Property\n\n";
			_addPropOnly();
			_deleteFromFile();
			_updateFile(GlobalList.getFirst(), 0);
			system("pause"); break;
		}
		case 5: { //? add DATA
			system("CLs");
			system("COLOR F1");
			cout << "\n\tAdd Data\n\n";
			_addDataOnly();
			_deleteFromFile();
			_updateFile(GlobalList.getFirst(), 0);
			system("pause"); break;
		}
		case 6: { //! delete LIST 
			system("CLs");
			system("COLOR F4");
			cout << "\n\tDelete All List \n\n";
			_deleteAll();
			_deleteFromFile();
			system("pause"); break;
		}
		case 7: { //! delete ITEM

			system("CLs");
			system("COLOR F4");
			cout << "\n\tDelete an Item\n\n";
			_deleteItem();
			_deleteFromFile();
			_updateFile(GlobalList.getFirst(), 0);
			system("pause"); break;
		}
		case 8: { //* print SEARCHED DATA
			system("CLs");
			system("COLOR FA");
			cout << "\n\tsearch item\n\n";
			cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
			Stack  stack = Stack();
			string value;
			cout << "enter the item name for search >> ";
			cin.ignore();
			getline(cin, value);
			_search(GlobalList.getFirst(), value, stack);
			system("pause");
			break;
		}
		case 9: { //! EXIT
			system("CLs");
			system("COLOR 04");
			cout << "\n\tFinished Proccess \n\n";
			exit(1); break;
		}
		default: {
			system("CLs");
			system("COLOR 04");
			cout << "\n\n\t\toption not found ";
			system("pause"); break;
		}
		}
	}
}