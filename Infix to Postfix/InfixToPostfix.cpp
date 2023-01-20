/*
 * Description: A 4-way linked list used to store phone numbers of
 *              users which includes the functions of adding a user,
 *              deleting a user, displaying all users, and searching
 *              a user data.
*/

#include <iostream>
#include <string>
using namespace std;



//Globally defined variables:
int N = 0;			//Current Number of Nodes
int Count = 0;		//Number of Nodes Searched/Displayed
int RowMax = 3;		//Max number of Rows
int ColMax = 3;		//Max number of Columns



struct Node
{
	int Phone;
	char Name[25];
	char Address[25];
	char Email[25];

	Node* Next;
	Node* Back;
	Node* Up;
	Node* Down;
};



Node* CreateNode();
Node* AddInfo(Node* HeadPtr);
Node* VerticalLinks(Node* HeadPtr);
Node* DeleteInfo(Node* HeadPtr, int DeletePtr);
bool SearchInfo(Node* HeadPtr, char SearchChar[], int SearchInt, int Option);
void DisplayInfo(Node* HeadPtr);



Node* CreateNode()			//Function to create and initialize a node
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	if (NewNode == NULL)
	{
		cout << "No memory left!" << endl;;
		return NULL;
	}

	NewNode->Phone = NULL;
	NewNode->Name[0] = '\0';
	NewNode->Address[0] = '\0';
	NewNode->Email[0] = '\0';

	NewNode->Next = NULL;
	NewNode->Back = NULL;
	NewNode->Up = NULL;
	NewNode->Down = NULL;

	return NewNode;
}



Node* AddInfo(Node* HeadPtr)			//Function to add a new node
{
	//Condition if linked list is full
	if (N == (RowMax * ColMax))
	{
		cout << "No more data can be stored in this directory!" << endl;
		return NULL;
	}

	bool InputFail;
	string Option;
	Node* NewData = CreateNode();

	//Input of Phone Number
	do
	{
		InputFail = 0;
		cout << endl << "Enter 5-digit Phone Number: ";
		cin >> NewData->Phone;

		if (cin.fail())
		{
			InputFail = 1;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "You can only enter a number! ";
		}

		else if (NewData->Phone < 10000 || NewData->Phone > 99999)
		{
			InputFail = 1;
			cout << "Not a valid input!" << endl;
		}

		else if (N != 0 && SearchInfo(HeadPtr, NULL, NewData->Phone, 0))
		{
			InputFail = 1;
			cout << "This data already exists!" << endl;
		}

	} while (InputFail);
	cin.ignore(1000, '\n');

	//Input of Name
	do
	{
		InputFail = 0;
		cout << endl << "Enter Name: ";
		cin.getline(NewData->Name, 25);

		if (NewData->Name[0] == '\0')
		{
			InputFail = 1;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Not a valid input!" << endl;
		}

		else if (N != 0 && SearchInfo(HeadPtr, NewData->Name, NULL, 10))
		{
			InputFail = 1;
			cout << "This data already exists!" << endl;
		}

	} while (InputFail);

	//Input of Address
	do
	{
		InputFail = 0;
		cout << endl << "Enter Address: ";
		cin.getline(NewData->Address, 25);

		if (NewData->Address[0] == '\0')
		{
			InputFail = 1;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Not a valid input!" << endl;
		}

		else if (N != 0 && SearchInfo(HeadPtr, NewData->Address, NULL, 20))
		{
			InputFail = 1;
			cout << "This data already exists!" << endl;
		}

	} while (InputFail);

	//Input of Email
	do
	{
		InputFail = 0;
		cout << endl << "Press only ENTER if no Email!" << endl << "Enter Email: ";
		cin.getline(NewData->Email, 25);

		if (N != 0 && NewData->Email[0] != '\0' && SearchInfo(HeadPtr, NewData->Email, NULL, 30))
		{
			InputFail = 1;
			cout << "This data already exists!" << endl;
		}

	} while (InputFail);

	//Condition to add first node
	if (N == 0)
	{
		HeadPtr = NewData;
		return HeadPtr;
	}

	Node* Curr = HeadPtr;
	Node* Prev = CreateNode();

	//Traversal of rows
	int CurrRow = N / ColMax;		//Row of new node to be added
	for (int i = 0; i < CurrRow; i++)
	{
		Prev = Curr;
		Curr = Curr->Down;
	}

	//Traversal of columns
	int CurrCol = N % ColMax;		//Column of new node to be added
	for (int j = 1; j < CurrCol; j++)
		Curr = Curr->Next;

	if (CurrCol == 0)
	{
		NewData->Up = Prev;
		Curr = NewData;
		Prev->Down = Curr;
	}
	else
	{
		NewData->Back = Curr;
		Curr->Next = NewData;
	}

	return HeadPtr;
}



Node* VerticalLinks(Node* HeadPtr)			//Function to create Up and Down links
{
	int CurrRow = N / ColMax;
	int CurrCol = N % ColMax;

	if (CurrRow > 0 && CurrCol > 0)
	{
		Node* UpperRow = HeadPtr;
		Node* LowerRow = HeadPtr->Down;

		for (int i = 1; i < CurrRow; i++)
		{
			UpperRow = UpperRow->Down;
			LowerRow = LowerRow->Down;
		}
		for (int j = 0; j < CurrCol; j++)
		{
			UpperRow = UpperRow->Next;
			LowerRow = LowerRow->Next;
		}

		UpperRow->Down = LowerRow;
		LowerRow->Up = UpperRow;
	}

	return HeadPtr;
}



Node* DeleteInfo(Node* HeadPtr, int DeletePtr)			//Function to delete an existing node
{
	//Condition if linked list is empty
	if (N == 0)
	{
		cout << "There is no data in this directory!" << endl;
		return NULL;
	}

	//Condition to avoid repeated input during recursions
	if (Count == 0)
	{
		cout << "Input the phone number you wish to delete: ";
		cin >> DeletePtr;
	}

	Node* Temp = CreateNode();
	Node* CurrH = HeadPtr;		//Current Horizontal Node
	Node* CurrV = HeadPtr;		//Current Vertical Node

	//Traversal of rows
	int i;
	int CurrRow = Count / ColMax;
	for (i = 0; i < CurrRow; i++)
	{
		CurrV = CurrV->Down;
		CurrH = CurrV;
	}

	//Traversal of columns
	for (int j = 0; j < ColMax; j++)
	{
		//Swapping of elements and deletion of node
		if (CurrH->Phone == DeletePtr)
		{
			CurrRow = N / ColMax;

			for (i; i < CurrRow; i++)
			{
				while (CurrH->Next != NULL)
				{
					CurrH->Phone = CurrH->Next->Phone;
					strcpy_s(CurrH->Name, CurrH->Next->Name);
					strcpy_s(CurrH->Address, CurrH->Next->Address);
					strcpy_s(CurrH->Email, CurrH->Next->Email);
					CurrH = CurrH->Next;
					Count++;

					//Condition to return if no more nodes exist
					if (Count == N - 1)
					{
						CurrH = NULL;
						Count = 0;
						return HeadPtr;
					}
				}

				Temp = CurrH;
				CurrV = CurrV->Down;

				if (CurrV != NULL)
				{
					Temp->Phone = CurrV->Phone;
					strcpy_s(Temp->Name, CurrV->Name);
					strcpy_s(Temp->Address, CurrV->Address);
					strcpy_s(Temp->Email, CurrV->Email);
					CurrH = CurrV;
				}
				Count++;

				//Condition to return if no more nodes exist
				if (Count == N - 1)
				{
					CurrH = NULL;
					Count = 0;
					return HeadPtr;
				}
			}

			Count = 0;
			return HeadPtr;
		}

		CurrH = CurrH->Next;
		Count++;

		//Condition to return if no more nodes exist
		if (Count == N)
		{
			cout << "This phone number does not exist in the directory!" << endl;
			Count = 0;
			return NULL;
		}
	}

	//Recursion to access new row of nodes
	HeadPtr = DeleteInfo(HeadPtr, DeletePtr);
	return HeadPtr;
}



bool SearchInfo(Node* HeadPtr, char SearchChar[], int SearchInt, int Option)			//Function to search an existing node
{
	//Condition if linked list is empty
	if (N == 0)
	{
		cout << "There is no data in this directory!" << endl;
		return false;
	}

	Node* Curr = HeadPtr;
	bool NotFound = 1;

	//Traversal of rows
	int CurrRow = Count / ColMax;
	for (int i = 0; i < CurrRow; i++)
		Curr = Curr->Down;

	//Traversal of columns
	for (int j = 0; j < ColMax; j++)
	{
		//Comparing search input with data in node
		switch (Option)
		{
		case 0:
			if (Curr->Phone == SearchInt)
				NotFound = 0;
			break;

		case 1:
		case 10:
			NotFound = strcmp(Curr->Name, SearchChar);
			break;

		case 2:
		case 20:
			NotFound = strcmp(Curr->Address, SearchChar);
			break;

		case 3:
		case 30:
			NotFound = strcmp(Curr->Email, SearchChar);
			break;
		}

		//Displaying data of searced node if it is found
		if (NotFound == 0 && (Option == 1 || Option == 2 || Option == 3))
		{
			cout << endl;
			cout << "NODE " << Count + 1 << ":" << endl;
			cout << "Phone Number: " << Curr->Phone << endl;
			cout << "Name: " << Curr->Name << endl;
			cout << "Address: " << Curr->Address << endl;
			cout << "Email: " << Curr->Email << endl;
			cout << endl;

			Count = 0;
			return true;
		}

		//Checks if added node already exists or not
		else if (NotFound == 0 && (Option == 0 || Option == 10 || Option == 20 || Option == 30))
		{
			Count = 0;
			return true;
		}

		Curr = Curr->Next;
		Count++;

		//Condition to return if no more nodes exist
		if (Count == N)
		{
			cout << "This data does not exist in the directory!" << endl;
			Count = 0;
			return false;
		}
	}

	//Recursion to access new row of nodes
	return SearchInfo(HeadPtr, SearchChar, SearchInt, Option);
}



void DisplayInfo(Node* HeadPtr)			//Function to display all existing node
{
	//Condition if linked list is empty
	if (N == 0)
	{
		cout << "There is no data in this directory!" << endl;
		return;
	}

	Node* Curr = HeadPtr;

	//Traversal of rows
	int CurrRow = Count / ColMax;
	for (int i = 0; i < CurrRow; i++)
		Curr = Curr->Down;

	//Traversal of columns
	for (int j = 0; j < ColMax; j++)
	{
		//Displaying data of current node
		cout << endl;
		cout << "NODE " << Count + 1 << ":" << endl;
		cout << "Phone Number: " << Curr->Phone << endl;
		cout << "Name: " << Curr->Name << endl;
		cout << "Address: " << Curr->Address << endl;
		cout << "Email: " << Curr->Email << endl;
		cout << endl;

		Curr = Curr->Next;
		Count++;

		//Condition to return if no more nodes exist
		if (Count == N)
		{
			Count = 0;
			return;
		}
	}

	//Recursion to access new row of nodes
	DisplayInfo(HeadPtr);
}



int main()
{
	Node* Head = CreateNode();
	Node* Temp = CreateNode();

	bool InputFail;
	int Instruction, Option;
	int Delete = 0;
	char Search[25] = { '\0' };

	do
	{
		cout << "MAIN MENU:" << endl;
		cout << "0: Exit." << endl;
		cout << "1: Add Phone Number." << endl;
		cout << "2: Delete Phone Number." << endl;
		cout << "3: Search Phone Number." << endl;
		cout << "4: Display Phone Numbers." << endl;

		do
		{
			InputFail = 0;
			cout << endl << "Enter a number to perform its corresponding action: ";
			cin >> Instruction;

			if (cin.fail())
			{
				InputFail = 1;
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "You can only enter a number!";
			}

		} while (InputFail);

		switch (Instruction)
		{
		case 0:
			cout << "SYSTEM IS SHUTTING DOWN!" << endl;
			break;

		case 1:
			Temp = AddInfo(Head);

			if (Temp != NULL)
			{
				Head = Temp;
				Head = VerticalLinks(Head);
				N++;
			}
			break;

		case 2:
			Temp = DeleteInfo(Head, Delete);
			if (Temp != NULL)
			{
				Head = Temp;
				N--;
			}
			break;

		case 3:
			cout << endl;
			cout << "SEARCH BY:" << endl;
			cout << "1: Name." << endl;
			cout << "2: Address." << endl;
			cout << "3: Email." << endl;

			do
			{
				InputFail = 0;
				cout << endl << "Enter a number to perform its corresponding action: ";
				cin >> Option;

				if (cin.fail())
				{
					InputFail = 1;
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "You can only enter a number!";
				}

				if (Option != 1 && Option != 2 && Option != 3)
				{
					InputFail = 1;
					cout << "This number has no corresponding action!" << endl;
				}

			} while (InputFail);

			cin.ignore(1000, '\n');
			do
			{
				InputFail = 0;
				cout << endl << "Enter search info: ";
				cin.getline(Search, 25);

				if (Search[0] == '\0')
				{
					InputFail = 1;
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Not a valid input!" << endl;
				}

			} while (InputFail);

			SearchInfo(Head, Search, NULL, Option);
			break;

		case 4:
			DisplayInfo(Head);
			break;

		default:
			cout << "This number has no corresponding action!" << endl;
			break;
		}

		cout << endl;
		system("pause");
		system("cls");

	} while (Instruction != 0);

	return 0;
}
