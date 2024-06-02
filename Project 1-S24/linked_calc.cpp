#include "linked_calc.hpp"

// Default constructor definition
template <typename T>
LinkedCalc<T>::LinkedCalc() : head(nullptr) {}

// Destructor to deallocate memory
template <typename T>
LinkedCalc<T>::~LinkedCalc() {
    Node<T>* cur = head;
    while(cur){
        Node<T>* temp = cur;
        cur = cur->next;
        delete temp;
    }
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

//helper function to convert needed parts of expression to floats
template <typename T>
float LinkedCalc<T>::convertToFloat(Node<T>*& current){
    float num = 0.0f;
    
    //iterates if value is digit or decimal 
    while (current && (isDigit(current->data) || current->data == '.')) {
        //if decimal it adds 1/10 of the value after the decimal to num
        if (current->data == '.') {
            current = current->next;
            num += 0.1 * (current->data - '0');
        //if before the decimal it adds the value to num
        }else{
            num += (current->data - '0');
        }
        current = current->next;
    }
    
    return num;
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
    Node<T>* cur = head;
    
    //first float or int is calculated
    float float1 = convertToFloat(cur);
    
    //iterating to find the operator
    while(!(isOperator(cur->data))){
        cur = cur->next;
    }
    char operation = cur->data;
    
    //second float or int is calculated
    float float2 = convertToFloat(cur->next);

    //return value is calculated based on the operator
    float num = 0.0f;
    if (operation == '+') {
        num = float1 + float2;
    }else if(operation == '-') {
        num = float1 - float2;
    } else if (operation == '*') {
        num = float1 * float2;
    } else if (operation == '/') {
        num = float1 / float2;
    }
    return num;
}



