/*
 * @brief: Header file containing stack functions to be used in the file Infix_Postfix.cpp
 */
#include<iostream>
using namespace std;

template <typename T> class stack
{
    private:
        T *arr;
        int stackSize;
        int top;

    public:

        /**
         * @brief: Constructor that initializes the stack
         * @param: size
         */
        stack(int size)
        { 
            arr = new T[size];
            stackSize = size;
            top = -1;
        }

        /**
         * @brief: Function that checks if the stack is empty
         * @return: bool
         */
        bool isEmpty()
        {
            if(top == -1)
            {
                return true;
            }
            return false;
        }

        /**
         * @brief: Function that adds data to the stack
         * @param data
         * @return: void
         */
        void push(T data)
        {
            if(top == stackSize)
            {
                return;
            }
            top++;
            arr[top] = data;
        }

        /**
         * @brief: Function that removes data from the stack
         * @return: void
         */
        void pop()
        {
            if(isEmpty())
            {
                return;
            }
            top--;
            
        }

        /**
         * @brief: Function that returns the top value of the stack
         * @return: T
         */
        T Top() { return arr[top]; }

        /**
         * @brief: Function that displays all data in the stack
         * @return: void
         */
        void display()
        {
            if(isEmpty())
            {
                cout << "Stack is Empty" << endl;
                return;
            }
            int i = 0;
            while(i != top)
            {
                cout<<arr[i]<<" ";
                i++;
            }
            cout << arr[top];
            cout << endl;
        }
};
