#ifndef LINKED_CALC_HPP
#define LINKED_CALC_HPP

#include <iostream>
#include <Logger.h>
#include <vector>

// Node structure
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& data) : data(data), next(nullptr) {}
};

// LinkedCalc class
template <typename T>
class LinkedCalc {
public:
    LinkedCalc();
    void Initialize();
    ~LinkedCalc();
    void insert(const T& value);
    bool validateExpression();
    float evaluateExpression();

    void printList();

private:
    Anderson::Logging::Logger* Logger;
    Node<T>* head;
    Node<T>* evaluationListHead;
    std::vector<float> floatEvaluationList;
    std::vector<char> operatorEvaluationList;
    
    bool isDigit(const T& c);
    bool isOperator(char c);
    float convertToFloat(Node<T>*& current);

    void createEvaluationList();
    Node<T>* createFloat(Node<T>* floatListHead, float* f);
    float evaluateEvaluationList();
    void evaluateAddition();
    void evaluateSubtraction();
    void evaluateMultiplication();
    void evaluateDivision();

    void LogEvaluationLists();
    std::string floatListToString(std::vector<float> v);
    std::string operatorListToString(std::vector<char> v);
};



#endif // LINKED_CALC_HPP
