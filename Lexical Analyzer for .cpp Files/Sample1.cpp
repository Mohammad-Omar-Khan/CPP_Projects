//This code is used to test the lexical analyzer

#include <iostream>
using namespace std;

class Calculator
{
public:

	void Add(int a, int b) { cout << a + b; }

	void Subtract(int a, int b) { cout << a - b; }

	void Multiply(int a, int b) { cout << a * b; }

	void Divide(int a, int b)
	{ 
		if (b != 0)
			cout << a / b;

		else
			cout << "Denominator cannot be 0!";
	}
};

int main()
{
	Calculator Obj;
	Obj.Add(3, 4);
	return 0;
}