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

template <typename T>
bool LinkedCalc<T>::validateExpression() {
    Node<T>* cur = head;
    
    while(cur && cur->next){
        //returns false if two consective decimals or a decimal not followed by a digit
        if((cur->data == '.') && (cur->next->data == '.' || !isDigit(cur->next->data))){
            return false;
        }
        //returns false if two consecutive operators
        if((cur->data =='+' || cur->data =='-' || cur->data =='*' || cur->data =='/') && (cur->next->data =='+' || cur->next->data =='-' || cur->next->data =='*' || cur->next->data =='/')){
            return false;
        }
        cur = cur-> next;
    }
    
    //returns false if operator isnt followed by a number
    if((cur->data == '.' || cur->data =='+' || cur->data =='-' || cur->data =='*' || cur->data =='/') && cur->next == nullptr){
        return false;
    }

    return true;
}


// Function to evaluate the expression represented by the linked list
template <typename T>
float LinkedCalc<T>::evaluateExpression() {
    //To be implemented
}

