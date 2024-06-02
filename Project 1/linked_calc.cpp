#include "linked_calc.hpp"

// Default constructor definition
template <typename T>
LinkedCalc<T>::LinkedCalc() : head(nullptr)
{
    Logger = new Anderson::Logging::Logger(Anderson::Logging::LogLevel::Trace, "linked_calc");
    Logger->Initialize();
}

template <typename T>
void LinkedCalc<T>::Initialize()
{
    Logger = new Anderson::Logging::Logger(Anderson::Logging::LogLevel::Trace, "linked_calc");
    Logger->Initialize();
}

// Destructor to deallocate memory
template <typename T>
LinkedCalc<T>::~LinkedCalc() {
//to be implemented
}

// Function to insert a new node at the end of the linked list
template <typename T>
void LinkedCalc<T>::insert(const T& value) {
    if (!Logger->IsInitialized())
        Logger->Initialize();

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
    //to be implemented
    return true;
}


// Function to evaluate the expression represented by the linked list
template <typename T>
float LinkedCalc<T>::evaluateExpression() {
    createEvaluationList();
    evaluateEvaluationList();
    return floatEvaluationList[0];
}

// Prints the list to the console
template <typename T>
void LinkedCalc<T>::printList()
{
    // Return if the list is empty
    if (head == nullptr)
    {
        Log->LogTrace("Empty List");
        return;
    }
    
    Log->LogTrace("Printing List ...");
    int iList = 0;
    Node<T>* pList = head;
    while (pList != nullptr)
    {
        if(strcmp(typeid(pList->data).name(), "char") == 0)
            Log->LogTrace("[%d](char) = %c", iList, pList->data);

        if (strcmp(typeid(pList->data).name(), "float") == 0)
            Log->LogTrace("[%d](float) = %f", iList, pList->data);


        //std::cout << "x" << typeid(pList->data).name() << "x" << std::endl;
        pList = pList->next;
        iList++;
    }
}

// Constructs the evaluation list
template <typename T>
void LinkedCalc<T>::createEvaluationList()
{
    // Clear evaluation lists
    Log->LogTrace("Clearing evaluation lists ...");
    floatEvaluationList.clear();
    operatorEvaluationList.clear();

    if (head == nullptr)
        return;

    Node<T>* pLinkedCalcList = head;
    while (pLinkedCalcList != nullptr)
    {
        // If node is an operator
        if (isOperator(pLinkedCalcList->data))
        {
            Log->LogTrace("Next node is operator %c", pLinkedCalcList->data);
            operatorEvaluationList.push_back(pLinkedCalcList->data);
            pLinkedCalcList = pLinkedCalcList->next;
        }
        else
        {
            // Node is a number
            Log->LogTrace("Next node is a number");
            float f;
            pLinkedCalcList = createFloat(pLinkedCalcList, &f);
            floatEvaluationList.push_back(f);
        }
    }

    std::reverse(floatEvaluationList.begin(), floatEvaluationList.end());
    std::reverse(operatorEvaluationList.begin(), operatorEvaluationList.end());

    if (Logger->WillLog(Anderson::Logging::LogLevel::Trace))
        LogEvaluationLists();
}

// Evaluates the evaluation list
template <typename T>
float LinkedCalc<T>::evaluateEvaluationList()
{
    evaluateDivision();
    evaluateMultiplication();
    evaluateAddition();
    evaluateSubtraction();

    return floatEvaluationList[0];
}

template <typename T>
void LinkedCalc<T>::evaluateAddition()
{
    Log->LogTrace("Evaluating addition ...");

    // Loop through operators backwards
    for (int iOperator = operatorEvaluationList.size() - 1; iOperator >= 0; iOperator--)
    {
        if (operatorEvaluationList[iOperator] == '+')
        {
            Log->LogTrace("Addition found at index %d", iOperator);

            float sum = floatEvaluationList[iOperator + 1] + floatEvaluationList[iOperator];
            floatEvaluationList[iOperator] = sum;
            
            floatEvaluationList.erase(floatEvaluationList.begin() + iOperator + 1);
            operatorEvaluationList.erase(operatorEvaluationList.begin() + iOperator);

            if (Logger->WillLog(Anderson::Logging::LogLevel::Trace))
                LogEvaluationLists();
        }
    }
}

template <typename T>
void LinkedCalc<T>::evaluateSubtraction()
{
    Log->LogTrace("Evaluating subtraction ...");

    // Loop through operators backwards
    for (int iOperator = operatorEvaluationList.size() - 1; iOperator >= 0; iOperator--)
    {
        if (operatorEvaluationList[iOperator] == '-')
        {
            Log->LogTrace("Subtraction found at index %d", iOperator);

            float difference = floatEvaluationList[iOperator + 1] - floatEvaluationList[iOperator];
            floatEvaluationList[iOperator] = difference;

            floatEvaluationList.erase(floatEvaluationList.begin() + iOperator + 1);
            operatorEvaluationList.erase(operatorEvaluationList.begin() + iOperator);

            if (Logger->WillLog(Anderson::Logging::LogLevel::Trace))
                LogEvaluationLists();
        }
    }
}

template <typename T>
void LinkedCalc<T>::evaluateMultiplication()
{
    Log->LogTrace("Evaluating multiplication ...");

    // Loop through operators backwards
    for (int iOperator = operatorEvaluationList.size() - 1; iOperator >= 0; iOperator--)
    {
        if (operatorEvaluationList[iOperator] == '*')
        {
            Log->LogTrace("Multiplication found at index %d", iOperator);

            float product = floatEvaluationList[iOperator + 1] * floatEvaluationList[iOperator];
            floatEvaluationList[iOperator] = product;

            floatEvaluationList.erase(floatEvaluationList.begin() + iOperator + 1);
            operatorEvaluationList.erase(operatorEvaluationList.begin() + iOperator);

            if (Logger->WillLog(Anderson::Logging::LogLevel::Trace))
                LogEvaluationLists();
        }
    }
}

template <typename T>
void LinkedCalc<T>::evaluateDivision()
{
    Log->LogTrace("Evaluating division ...");

    // Loop through operators backwards
    for (int iOperator = operatorEvaluationList.size() - 1; iOperator >= 0; iOperator--)
    {
        if (operatorEvaluationList[iOperator] == '/')
        {
            Log->LogTrace("Division found at index %d", iOperator);

            float quotient = floatEvaluationList[iOperator + 1] / floatEvaluationList[iOperator];
            floatEvaluationList[iOperator] = quotient;

            floatEvaluationList.erase(floatEvaluationList.begin() + iOperator + 1);
            operatorEvaluationList.erase(operatorEvaluationList.begin() + iOperator);

            if (Logger->WillLog(Anderson::Logging::LogLevel::Trace))
                LogEvaluationLists();
        }
    }
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

// Creates a float
template <typename T>
Node<T>* LinkedCalc<T>::createFloat(Node<T>* floatListHead, float* f)
{
    float integerHalf = 0.0;
    float fractionalHalf = 0.0;
    int fractionalPower = -1;
    bool inIntegerHalf = true;

    while (floatListHead != nullptr && !isOperator(floatListHead->data))
    {
        if (isdigit(floatListHead->data))
        {
            float digit = convertToFloat(floatListHead);
            if (inIntegerHalf)
                integerHalf = integerHalf * 10 + digit;
            else
            {
                fractionalHalf += float(digit * pow(10, fractionalPower));
                fractionalPower--;
            }
        }
        else
            inIntegerHalf = false;

        Log->LogTrace("char = %c, integerHalf = %f, fractionalHalf = %f, fractionalPower = %d, inIntegerHalf = %s",
            floatListHead->data, integerHalf, fractionalHalf, fractionalPower, inIntegerHalf ? "True" : "False");

        floatListHead = floatListHead->next;
        //if (floatListHead->next == nullptr)
        //    break;
    }

    // Create the float
    *f = integerHalf + fractionalHalf;
    return floatListHead;
}

template<typename T>
void LinkedCalc<T>::LogEvaluationLists()
{
    std::string floatList = floatListToString(floatEvaluationList);
    Log->LogTrace("Float list:  %s", floatList.c_str());

    std::string operatorList = operatorListToString(operatorEvaluationList);
    Log->LogTrace("Operator list:  %s", operatorList.c_str());
}

template <typename T>
std::string LinkedCalc<T>::floatListToString(std::vector<float> v)
{
    // Guard clause
    if (v.empty())
        return "";

    std::string s = std::to_string(v[0]);

    for (int iFloat = 1; iFloat < v.size(); iFloat++)
        s += ", " + std::to_string(v[iFloat]);

    return s;
}

template <typename T>
std::string LinkedCalc<T>::operatorListToString(std::vector<char> v)
{
    // Guard clause
    if (v.empty())
        return "";

    std::string s{ v[0] };
    for (int iChar = 1; iChar < v.size(); iChar++)
    {
        s.append(", ");
        s.push_back(v[iChar]);
    }

    return s;
}