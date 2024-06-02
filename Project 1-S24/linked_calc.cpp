#include "linked_calc.hpp"

// Default constructor definition
template <typename T>
LinkedCalc<T>::LinkedCalc() : head(nullptr) {}

// Destructor to deallocate memory
template <typename T>
LinkedCalc<T>::~LinkedCalc() {
    //To be implemented
}

// Function to insert a new node at the end of the linked list
template <typename T>
void LinkedCalc<T>::insert(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Helper function to determine if a character is a digit
template <typename T>
bool LinkedCalc<T>::isDigit(const T& c) {
    return (c >= '0' && c <= '9') ;
}

// Checks if a char is an operator
template <typename T>
bool LinkedCalc<T>::isOperator(char c)
{
    return c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '/';
}

// Converts a node to its floating point representation
template <typename T>
float LinkedCalc<T>::convertToFloat(Node<T>*& current)
{
    if (strcmp(typeid(current->data).name(), "char") == 0)
        return (float)(current->data - 48);
    else
        return 0.0;
}
template <typename T>
bool LinkedCalc<T>::validateExpression() {
    Node<T>* cur = head;
    
    while(cur && cur->next){
        //returns false if two consective decimals or a decimal not followed by a digit
        if((cur->data == '.') && (cur->next->data == '.' || !isDigit(cur->next->data))){
            return false;
        }
        //returns false if two consecutive operators
        if(isOperator(cur->data) && isOperator(cur->next->data)){
            return false;
        }
        cur = cur-> next;
    }
    
    //returns false if operator is not followed by a number
    if((cur->data == '.' || isOperator(cur->data))  && cur->next == nullptr){
        return false;
    }

    return true;
}


// Function to evaluate the expression represented by the linked list
template <typename T>
float LinkedCalc<T>::evaluateExpression() {
    //To be implemented
}

