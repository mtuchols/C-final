#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::right;
using std::string;
using std::ofstream;
using std::ostream;
#include <fstream>

template <class List>
class linkedList
{
private:
    struct listNode
    {
        Restaurant value;
        struct listNode *next;
    };
public:
    int NumberOfNodes;
    listNode *head;
    listNode *current;
    friend void taskC ();
    int getAmountofNodes();
    void insertAtBack(Restaurant);
    void deleteNode(Restaurant);
    void removeFromFront();
    void print() const;
    void printToFile() const;
    friend std::ostream& operator << (std::ostream &, const linkedList<Restaurant> & ); // output
    linkedList()
    {
        head = nullptr;
        NumberOfNodes = 0;
    }
    ~linkedList();
};

template <class List>
typename linkedList<List>::ostream& operator << (ostream& projectOutputFile, const linkedList<Restaurant> & list1)
{
    struct listNode *tempPtr;
    while (tempPtr!= nullptr)
    {
    projectOutputFile << tempPtr->value.getPatronName() << "    " << tempPtr->value.getMealTime()<< "    " << tempPtr->value.getMealName()<< "    ";
    projectOutputFile << tempPtr->value.getCalories()<< "   "<< tempPtr->value.getProtein()<< " "<<tempPtr->value.getVitamins()<< endl;
    tempPtr = tempPtr -> next;
    }

    return projectOutputFile;
}

// returns amount of nodes in the linked list
template <class List>
int linkedList<List>::getAmountofNodes()
{
    return NumberOfNodes;
}

// inserts node at the back
template <class List>
void linkedList<List>::insertAtBack(Restaurant num)
{
    listNode *newNode;
    listNode *nodePtr;

    newNode = new listNode;
    newNode -> value = num;
    newNode -> next = nullptr;
    if (!head)
    {
        head = newNode;
    }
    else
    {
        nodePtr = head;
        while (nodePtr -> next)
        {
            nodePtr = nodePtr -> next;
        }
        nodePtr -> next = newNode;
    }
    NumberOfNodes++;
}

template <class List>
void linkedList<List> :: removeFromFront()
{
    listNode *nodePtr;
    nodePtr = head -> next;
    delete head;
    head = nodePtr;

}

//deletes node by comparing table numbers
template <class List>
void linkedList<List> :: deleteNode(Restaurant num)
{
    listNode *nodePtr;
    listNode *previousNode;
    if (!head)
    {
        return;
    }
    if (head ->value.getTableNumber() == num.getTableNumber())
    {
        nodePtr = head -> next;
        delete head;
        head = nodePtr;
    }
    else
    {
        nodePtr = head;
        while (nodePtr != nullptr &&  nodePtr -> value.getTableNumber() != num.getTableNumber())
        {
            previousNode = nodePtr;
            nodePtr = nodePtr -> next;
        }
        if (nodePtr -> value.getTableNumber() == num.getTableNumber())
        {
            previousNode -> next = nodePtr -> next;
            delete nodePtr;
        }
    }
}

//outputs to the console
template <class List>
void linkedList<List> :: print() const
{
    struct listNode *tempPtr = head;
    while (tempPtr!= nullptr)
    {
    cout <<tempPtr->value.getRestaurantNumber()<< " "<<tempPtr->value.getTableNumber()<< " " << tempPtr->value.getPatronID() <<" ";
    cout <<tempPtr->value.getPatronName()<<" " << tempPtr->value.getMealTime()<<" " << tempPtr->value.getMealNumber() << endl;
        tempPtr = tempPtr -> next;
    }
}
// outputs to the text file
template <class List>
void linkedList<List> :: printToFile() const
{
    ofstream projectOutputFile;
    projectOutputFile.open("output.txt", std::fstream::out | std::fstream::app); // opens text file
    if (!projectOutputFile) // fail sequence
    {
        projectOutputFile << "File Creation Failure" << endl;
    }
   /* if (head ==nullptr) // was used to check is list is empty after everything is deleted
    {
        projectOutputFile << "The list is  empty" << endl;
    } */
    struct listNode *tempPtr = head;
    while (tempPtr!= nullptr)
    {
    projectOutputFile << tempPtr->value.getPatronName() << "," << tempPtr->value.getMealTime()<< "," << tempPtr->value.getMealNumber()<< "," <<tempPtr->value.getMealName()<< ",";
    projectOutputFile << tempPtr->value.getRestaurantNumber()<<"," <<tempPtr->value.getCalories()<< ","<< tempPtr->value.getProtein()<< ","<<tempPtr->value.getVitamins()<< endl;
        tempPtr = tempPtr -> next;
    }
}

// destroys linked list
template <class List>
linkedList<List>:: ~linkedList()
{
    listNode *nodePtr;
    listNode *nextNode;
    nodePtr = head;

    while (nodePtr != nullptr)
    {
        nextNode = nodePtr ->next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}

#endif // LINKEDLIST_H_INCLUDED
