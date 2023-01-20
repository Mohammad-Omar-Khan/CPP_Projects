/*
 * @brief: Converts an Infix equation to a Postfix equation, and solves it, through the use of stacks.
 */
#include<iostream>
#include<math.h>
#include "Stack.h"
#include<string>
using namespace std;


/**
 * @brief: Function that adds two values
 * @param: a, b
 * @return: double
 */
double Add(double a, double b) { return a + b; }

/**
 * @brief: Function that subtracts two values
 * @param: a, b
 * @return: double
 */
double Subtract(double a, double b) { return b - a; }

/**
 * @brief: Function that multiplies two values
 * @param: a, b
 * @return: double
 */
double Multiply(double a, double b) { return a * b; }

/**
 * @brief: Function that divides two values
 * @param: a, b
 * @return: double
 */
double Divide(double a, double b) { return b / a; }

/**
 * @brief: Function that exponents two values
 * @param: a, b
 * @return: double
 */
double Exponent(double a, double b) { return pow(b, a); }



/**
 * @brief: Function that returns the preference of the operation
 * @param: c
 * @return: int
 */
int Precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else
        return -1;
}

/**
 * @brief: Function that checks if the character is an operator
 * @param: c
 * @return: bool
 */
bool isOperator(char s)
{
    if (s == '+' || s == '-' || s == '*' || s == '/' || s == '^')
        return true;
    else
        return false;
}



/**
 * @brief: Function that takes input for the infix equation
 * @return: string
 */
string Input()
{
    string Infix;
    int OpenBrackets;
    bool OperatorAtEnd, InputFail;

    do
    {
        OpenBrackets = 0;
        OperatorAtEnd = false;
        InputFail = false;

        cout << "Enter an equation in infix notation: ";
        getline(cin, Infix, '\n');

        if (Infix.empty())
        {
            InputFail = true;
            cout << "You cannot enter an empty string!" << endl << endl;
            continue;
        }

        int x = 0;
        while (Infix[x] == ' ')
            x++;
        if (isOperator(Infix[x]))
        {
            InputFail = true;
            cout << "There must be a number before the operator!" << endl << endl;
        }


        for (int i = 0; i < Infix.length(); i++)
        {
            if ((Infix[i] < '-' || Infix[i] > '9') && (Infix[i] < '(' || Infix[i] > '+') && Infix[i] != '^' && Infix[i] != ' ' && Infix[i] != '[' && Infix[i] != ']' && Infix[i] != '{' && Infix[i] != '}')
            {
                InputFail = true;
                cout << "You can only input the following characters: 0-9, +, -, *, /, ^, ., ()!" << endl << endl;
                break;
            }

            if (Infix[i] == '(' || Infix[i] == '[' || Infix[i] == '{')
                OpenBrackets++;

            else if (Infix[i] == ')' || Infix[i] == ']' || Infix[i] == '}')
            {
                OpenBrackets--;
                if (OpenBrackets == -1)
                {
                    InputFail = true;
                    OpenBrackets = 0;
                    cout << "You cannot enter a closing bracket before its corresponding opening bracket!" << endl << endl;
                    break;
                }
            }
            
            if (Infix[i] != ' ')
                OperatorAtEnd = isOperator(Infix[i]);
        }

        if (OpenBrackets != 0)
        {
            InputFail = true;
            cout << "There must be an equal number of opening and closing brackets!" << endl << endl;
        }

        if (OperatorAtEnd)
        {
            InputFail = true;
            cout << "There must be a number after the operator!" << endl << endl;
        }

    } while (InputFail);

    string temp;
    for (int i = 0; i < Infix.length(); i++)
    {
        if (isOperator(Infix[i]) && i != Infix.length() - 1)
        {
            temp += ' ';
            temp += Infix[i];
            temp += ' ';
        }
        else if (Infix[i] == '(' || Infix[i] == '{' || Infix[i] == '[')
        {
            temp += '(';
            temp += ' ';
        }
        else if (Infix[i] == ')' || Infix[i] == '}' || Infix[i] == ']')
        {
            temp += ' ';
            temp += ')';
        }
        else if (Infix[i] == ' ')
            continue;
        else
            temp += Infix[i];
    }
    Infix = temp;
    Infix += ' ';

    return Infix;
}



/**
 * @brief: Function that converts an Infix equation to a postfix equation using stacks
 * @param: Infix
 * @return: string
 */
string InfixToPostfix(string Infix)
{
    string Result;
    int length = Infix.length();
    stack<char> s(length);
    string Temp = "";

    for (int i = 0; i < Infix.length(); i++)
    {
        if ((Infix[i] >= '0' && Infix[i] <= '9') || (Infix[i] == '.'))
        {
            if (Infix[i + 1] != ' ')
            {
                Temp += Infix[i];
            }
            else
            {
                Temp += Infix[i];
                Result += Temp;
                Temp = "";
                Result += " ";
            }
        }

        else if (Infix[i] == ' ')
            continue;

        else if (Infix[i] == '(')
            s.push('(');

        else if (Infix[i] == ')')
        {
            while (s.Top() != '(')
            {
                Result += s.Top();
                Result += ' ';
                s.pop();
            }
            s.pop();
        }

        else
        {
            while (!s.isEmpty() && Precedence(Infix[i]) <= Precedence(s.Top()))
            {
                Result += s.Top();
                Result += ' ';
                s.pop();
            }
            s.push(Infix[i]);
        }
    }

    while (!s.isEmpty())
    {
        Result += s.Top();
        Result += ' ';
        s.pop();
    }

    return Result;

}



/**
 * @brief: Function that solves the Postfix equation using stacks
 * @param: s
 * @return: double
 */
double Evaluate(string s)
{
    stack<double> exp(s.length());
    int i = 0;
    string Temp = "";

    while (i != s.length())
    {
        if (s[i] == ' ')
        {
            i++;
            continue;
        }

        else if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
        {
            if (s[i + 1] != ' ')
            {
                Temp += s[i];
            }

            else
            {
                Temp += s[i];

                float a = stof(Temp);
                exp.push(a);
                Temp = "";
            }
        }

        else
        {
            double a = exp.Top();
            exp.pop();
            double b = exp.Top();
            exp.pop();

            switch (s[i])
            {
            case '+':
            {
                exp.push(Add(a, b));
                break;
            }
            case '-':
            {
                exp.push(Subtract(a, b));
                break;
            }
            case '*':
            {
                exp.push(Multiply(a, b));
                break;
            }
            case '/':
            {
                exp.push(Divide(a, b));
                break;
            }
            case '^':
            {
                exp.push(Exponent(a, b));
                break;
            }
            }
        }

        i++;
    }

    return exp.Top();
}



/**
 * @brief: Main Function
 * @return: int
 */
int main()
{
    string Infix = Input();
    string Postfix = InfixToPostfix(Infix);

    system("pause");
    system("cls");

    cout << "Infix: " << Infix << endl << endl;
    cout << "Postfix: " << Postfix << endl << endl;
    cout << "Solution: " << Evaluate(Postfix) << endl << endl;

    return 0;
}
