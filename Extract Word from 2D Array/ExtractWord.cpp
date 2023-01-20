/*
 * @brief: The program take a 2D character array as input, and searches for all possible words from the file 'Dictionary.txt', in all possible directions.
		   All found words are saved in the file 'WordsFound.txt'.
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



class WordSearch
{
private:

	/**
	 * @brief: This struct is used to create a trie node, with 52 child nodes for each letter (26 smallcase, 26 capital)
	 */

	struct Node
	{
		Node* Alphabet[52];

		Node()
		{
			for (int i = 0; i < 52; i++)
				Alphabet[i] = NULL;
		}
	};

	Node* Root = new Node;
	char** Input;
	int RowSize, ColSize;



	/**
	 * @brief: The following eight functions traverse the 2D array in the named direction, and creates a trie node for each character.
	 * @return: void
	 */

	void Horizontal()
	{
		Node* Traverse = Root;

		for (int i = 0; i < RowSize; i++)
		{
			for (int j = 0; j < ColSize; j++)
			{
				Traverse = Root;

				for (int k = j; k < ColSize; k++)
				{
					int Index = 0;
					if (Input[i][k] >= 'a' && Input[i][k] <= 'z')
						Index = Input[i][k] - 'a';
					else if (Input[i][k] >= 'A' && Input[i][k] <= 'Z')
						Index = Input[i][k] - 'A' + 26;

					if (Traverse->Alphabet[Index] == NULL)
						Traverse->Alphabet[Index] = new Node;

					Traverse = Traverse->Alphabet[Index];
				}
			}
		}
	}

	void ReverseHorizontal()
	{
		Node* Traverse = Root;

		for (int i = RowSize - 1; i >= 0; i--)
		{
			for (int j = ColSize - 1; j >= 0; j--)
			{
				Traverse = Root;
				
				for (int k = j; k >= 0; k--)
				{
					int Index = 0;
					if (Input[i][k] >= 'a' && Input[i][k] <= 'z')
						Index = Input[i][k] - 'a';
					else if (Input[i][k] >= 'A' && Input[i][k] <= 'Z')
						Index = Input[i][k] - 'A' + 26;

					if (Traverse->Alphabet[Index] == NULL)
						Traverse->Alphabet[Index] = new Node;

					Traverse = Traverse->Alphabet[Index];
				}
			}
		}
	}

	void Vertical()
	{
		Node* Traverse = Root;

		for (int i = 0; i < ColSize; i++)
		{
			for (int j = 0; j < RowSize; j++)
			{
				Traverse = Root;

				for (int k = j; k < RowSize; k++)
				{
					int Index = 0;
					if (Input[k][i] >= 'a' && Input[k][i] <= 'z')
						Index = Input[k][i] - 'a';
					else if (Input[k][i] >= 'A' && Input[k][i] <= 'Z')
						Index = Input[k][i] - 'A' + 26;

					if (Traverse->Alphabet[Index] == NULL)
						Traverse->Alphabet[Index] = new Node;

					Traverse = Traverse->Alphabet[Index];
				}
			}
		}
	}

	void ReverseVertical()
	{
		Node* Traverse = Root;

		for (int i = ColSize - 1; i >= 0; i--)
		{
			for (int j = RowSize - 1; j >= 0; j--)
			{
				Traverse = Root;

				for (int k = j; k >= 0; k--)
				{
					int Index = 0;
					if (Input[k][i] >= 'a' && Input[k][i] <= 'z')
						Index = Input[k][i] - 'a';
					else if (Input[k][i] >= 'A' && Input[k][i] <= 'Z')
						Index = Input[k][i] - 'A' + 26;

					if (Traverse->Alphabet[Index] == NULL)
						Traverse->Alphabet[Index] = new Node;

					Traverse = Traverse->Alphabet[Index];
				}
			}
		}
	}

	void LeftDiagonal()
	{
		Node* Traverse = Root;

		for (int x = (-ColSize + 1); x <= (RowSize - 1); x++)
		{
			Traverse = Root;

			for (int i = 0; i < RowSize; i++)
			{
				Traverse = Root;

				for (int j = i; j < RowSize; j++)
				{
					for (int k = 0; k < ColSize; k++)
					{
						if (j - k - x == 0)
						{
							int Index = 0;
							if (Input[j][k] >= 'a' && Input[j][k] <= 'z')
								Index = Input[j][k] - 'a';
							else if (Input[j][k] >= 'A' && Input[j][k] <= 'Z')
								Index = Input[j][k] - 'A' + 26;

							if (Traverse->Alphabet[Index] == NULL)
								Traverse->Alphabet[Index] = new Node;

							Traverse = Traverse->Alphabet[Index];
						}
					}
				}
			}
		}
	}

	void ReverseLeftDiagonal()
	{
		Node* Traverse = Root;

		for (int x = (RowSize - 1); x >= (-ColSize + 1); x--)
		{
			Traverse = Root;

			for (int i = RowSize - 1; i >= 0; i--)
			{
				Traverse = Root;

				for (int j = i; j >= 0; j--)
				{
					for (int k = ColSize - 1; k >= 0; k--)
					{
						if (j - k - x == 0)
						{
							int Index = 0;
							if (Input[j][k] >= 'a' && Input[j][k] <= 'z')
								Index = Input[j][k] - 'a';
							else if (Input[j][k] >= 'A' && Input[j][k] <= 'Z')
								Index = Input[j][k] - 'A' + 26;

							if (Traverse->Alphabet[Index] == NULL)
								Traverse->Alphabet[Index] = new Node;

							Traverse = Traverse->Alphabet[Index];
						}
					}
				}
			}
		}
	}

	void RightDiagonal()
	{
		Node* Traverse = Root;

		for (int x = 0; x < (RowSize + ColSize - 1); x++)
		{
			Traverse = Root;

			for (int i = 0; i < RowSize; i++)
			{
				Traverse = Root;

				for (int j = i; j < RowSize; j++)
				{
					for (int k = 0; k < ColSize; k++)
					{
						if (j + k - x == 0)
						{
							int Index = 0;
								if (Input[j][k] >= 'a' && Input[j][k] <= 'z')
									Index = Input[j][k] - 'a';
								else if (Input[j][k] >= 'A' && Input[j][k] <= 'Z')
									Index = Input[j][k] - 'A' + 26;

								if (Traverse->Alphabet[Index] == NULL)
									Traverse->Alphabet[Index] = new Node;

							Traverse = Traverse->Alphabet[Index];
						}
					}
				}
			}
		}
	}

	void ReverseRightDiagonal()
	{
		Node* Traverse = Root;

		for (int x = (RowSize + ColSize - 2); x >= 0; x--)
		{
			Traverse = Root;

			for (int i = RowSize - 1; i >= 0; i--)
			{
				Traverse = Root;

				for (int j = i; j >= 0; j--)
				{
					for (int k  = ColSize - 1; k >= 0; k--)
					{
						if (j + k - x == 0)
						{
							int Index = 0;
							if (Input[j][k] >= 'a' && Input[j][k] <= 'z')
								Index = Input[j][k] - 'a';
							else if (Input[j][k] >= 'A' && Input[j][k] <= 'Z')
								Index = Input[j][k] - 'A' + 26;

							if (Traverse->Alphabet[Index] == NULL)
								Traverse->Alphabet[Index] = new Node;

							Traverse = Traverse->Alphabet[Index];
						}
					}
				}
			}
		}
	}



public:

	WordSearch(int R, int C) : RowSize(R), ColSize(C)
	{
		Input = new char* [RowSize];

		for (int i = 0; i < RowSize; i++)
			Input[i] = new char[ColSize + 1];
	}

	~WordSearch()
	{
		for (int i = 0; i < RowSize; i++)
			delete[] Input[i];

		delete[] Input;
	}



	/**
	 * @brief: This function takes inputs for the 2D character array.
	 * @return: void
	 */
	void InputArray()
	{
		for (int i = 0; i < RowSize; i++)
		{
			bool InputFail;

			do
			{
				InputFail = false;
				cout << endl << "Input Row " << i + 1 << " of Array (" << ColSize << " characters only): ";
				cin >> Input[i];

				if (cin.fail())
				{
					InputFail = true;
					cout << "Not a valid input!" << endl;
					cin.clear();
					cin.ignore(10000, '\n');
				}
				
				else if (strlen(Input[i]) != ColSize)
				{
					InputFail = true;
					cout << "Input must be of " << ColSize << " characters only!" << endl;
					cin.clear();
					cin.ignore(10000, '\n');
				}

				else
				{
					for (int j = 0; j < ColSize; j++)
					{
						if ((Input[i][j] < 'a' || Input[i][j] > 'z') && (Input[i][j] < 'A' || Input[i][j] > 'Z'))
						{
							InputFail = true;
							cout << "Input can only consist of letters!" << endl;
							cin.clear();
							cin.ignore(10000, '\n');
							break;
						}
					}
				}

			} while (InputFail);
		}

		cout << endl;
		system("pause");
		system("cls");
		return;
	}

	/**
	 * @brief: This function displays the 2D character array.
	 * @return: void
	 */
	void DisplayArray()
	{
		for (int i = 0; i < RowSize; i++)
		{
			for (int j = 0; j < ColSize; j++)
				cout << Input[i][j] << "\t";

			cout << endl;
		}

		cout << endl;
		return;
	}

	/**
	 * @brief: This function converts the 2D array into trie nodes, by calling the eight private functions listed above.
	 * @return: void
	 */
	void ArrayToNodes()
	{
		Horizontal();
		ReverseHorizontal();
		Vertical();
		ReverseVertical();
		LeftDiagonal();
		ReverseLeftDiagonal();
		RightDiagonal();
		ReverseRightDiagonal();
	}

	/**
	 * @brief: This function takes a word from the file 'Dictionary.txt', and checks through the trie nodes to see if it exists in the 2D array.
	 *		   If the word exists, it is added to the file 'WordsFound.txt'.
	 * @param: Key
	 * @return: void
	 */
	void SearchWord(string Key)
	{
		Node* Traverse = Root;

		for (int i = 0; i < Key.length(); i++)
		{
			int Index = 0;
			if (Key[i] >= 'a' && Key[i] <= 'z')
				Index = Key[i] - 'a';
			else if (Key[i] >= 'A' && Key[i] <= 'Z')
				Index = Key[i] - 'A' + 26;
			// If the word contains an invalid letter, such as '.', '-', '_' etc., then it is instantly ignored.
			else
				return;

			if (Traverse->Alphabet[Index] == NULL)
				return;


			Traverse = Traverse->Alphabet[Index];
		}

		cout << Key << endl;

		ofstream WordsFound;
		WordsFound.open("WordsFound.txt", ios::app);
		WordsFound << Key << endl;
		WordsFound.close();
		return;
	}
};



/**
	 * @brief: Main Function.
	 * @return: int
	 */
int main()
{
	bool InputFail;
	int Rows, Columns;

	do
	{
		InputFail = false;
		cout << "Input row size of the 2D array: ";
		cin >> Rows;

		if (cin.fail())
		{
			InputFail = true;
			cout << "Not a valid input!" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}

		if (Rows <= 0)
		{
			InputFail = true;
			cout << "Number of rows must be greater than 0!" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}

	} while (InputFail);

	do
	{
		InputFail = false;
		cout << "Input column size of the 2D array: ";
		cin >> Columns;

		if (cin.fail())
		{
			InputFail = true;
			cout << "Not a valid input!" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}

		if (Columns <= 0)
		{
			InputFail = true;
			cout << "Number of columns must be greater than 0!" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}

	} while (InputFail);


	
	WordSearch Menu(Rows, Columns);

	Menu.InputArray();
	Menu.ArrayToNodes();
	Menu.DisplayArray();



	// The file 'WordsFound.txt' is opened here to remove all previous data.
	ofstream WordsFound;
	WordsFound.open("WordsFound.txt");
	WordsFound.close();


	
	ifstream Dictionary;
	Dictionary.open("Dictionary.txt");

	cout << "The following words have been added to the file WordsFound.txt!" << endl;

	while (!Dictionary.eof())
	{
		string Key;

		// If the length of the word is larger than the number of rows or columns, then it is instantly ignored.
		if (Key.length() > Rows && Key.length() > Columns)
			continue;
		else
		{
			getline(Dictionary, Key);
			Menu.SearchWord(Key);
		}
	}

	Dictionary.close();

	return 0;
}
