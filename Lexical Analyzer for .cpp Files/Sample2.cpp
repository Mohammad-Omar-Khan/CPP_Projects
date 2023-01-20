// This code is used to test lexical analyzer

#include <iostream>
using namespace std;

struct Node
{
	int Data;
	Node* Next;
};

void Insert(Node* Head, int NewData)
{
	Node* NewNode = new Node;
	NewNode->Data = NewData;
	NewNode->Next = NULL;

	Node* Temp = Head;

	while (Temp != NULL)
		Temp = Temp->Next;

	Temp = NewNode;
}

int main()
{
	Node* Head;
	Insert(Head, 3);
	Insert(Head, 7);
	return 0;
}