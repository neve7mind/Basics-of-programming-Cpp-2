
#include <iostream>
using namespace std;

struct Human {
    string name;
    int growth;
    double weight;
    Human* next;
};

void AddFirst(Human* &pNode, string name, int growth, double weight) {
    Human* newNode = new Human;
    newNode->name = name;
    newNode->growth = growth;
    newNode->weight = weight;
    newNode->next = pNode;
    pNode=newNode;
}


void AddLast(Human* &pNode, string name, int growth, double weight) {
    Human* newNode = new Human;
    newNode->name = name;
    newNode->growth = growth;
    newNode->weight = weight;
    newNode->next = pNode;
    if (pNode == nullptr) {
        newNode->next = nullptr;
        pNode = newNode;
    }
    else {
        Human* tmp = pNode;
        while (tmp->next != nullptr)
            tmp = tmp->next;
        newNode->next = nullptr;
        tmp->next=newNode;
    }
}


void AddAfter (Human* pNode, string Node, string name, int growth, double weight) {
    if (pNode == nullptr) {
        cout << "This list is empty\n";
        return;
    }
    Human* tmp = pNode;
    while (tmp->next != nullptr and tmp->name != Node)
        tmp = tmp->next;
    if (tmp->next == nullptr and tmp->name != Node) {
        cout << "No element in the list\n";
        return;
    }
    Human* newNode = new Human;
    newNode->name = name;
    newNode->growth = growth;
    newNode->weight = weight;
    newNode->next = pNode->next;
    pNode->next = newNode;
}


void AddBefore(Human* pNode, string Node, string name, int growth, double weight) {
    if (pNode == nullptr) {
        cout << "This list is empty\n";
        return;
    }
    if (pNode->name == Node) {
        AddFirst(pNode, name, growth, weight);
        return;
    }
    Human *prev = pNode, *tmp = pNode->next;
    while (tmp->next != nullptr and tmp->name != Node) {
        tmp = tmp->next;
        prev = prev->next;
    }
    if (tmp->next == nullptr and tmp->name != Node) {
        cout << "No element in the list\n";
        return;
    }
    Human* newNode = new Human;
    newNode->name = name;
    newNode->growth = growth;
    newNode->weight = weight;
    newNode->next = tmp;
    prev->next = newNode;
}


void Del(Human* &pNode, string Node) {
    if(pNode == nullptr) {
        cout << "List is empty\n";
        return;
    }
    Human *tmp = pNode;
    if(pNode->name == Node) {
        pNode = pNode->next;
        delete tmp;
        return;
    }
    if (pNode->next == nullptr) {
        cout << "No element in the list\n";
        return;
    }
    Human *prev=pNode;
    tmp = pNode->next;
    while (tmp->next != nullptr and tmp->name != Node) {
        tmp = tmp->next;
        prev = prev->next;

    }
    if(tmp->next == nullptr and tmp->name != Node) {
        cout << "No element in the list\n";
        return;
    }
    if(tmp->name == Node) {
        prev->next = tmp->next;
        delete tmp;
        return;
    }
}


void Showmen(Human *pNode) {
    if (pNode == nullptr) {
        cout << "This list is empty\n";
        return;
    }
    Human *tmp = pNode;
    while(tmp != nullptr) {
        cout<<"Name: " << tmp->name << "\nGrowth: " << tmp->growth << "\nWeight: " << tmp->weight << endl << endl;
        tmp = tmp->next;
    }
}


int main() {
    Human* list1 = nullptr;
    AddFirst(list1, "Tom", 175, 70.55);
    Showmen(list1);
    cout<<"-----------------------------------------------------------------------"<<endl << endl;
    AddFirst(list1, "Lisa", 150, 59.64);
    Showmen(list1);
    cout<<"-----------------------------------------------------------------------"<<endl << endl;
    AddAfter(list1, "Tom", "Fred", 189, 100.38);
    Showmen(list1);
    cout<<"-----------------------------------------------------------------------"<<endl << endl;
    AddBefore(list1, "Fred", "Jeff", 140, 56.49);
    Showmen(list1);
    cout<<"-----------------------------------------------------------------------"<<endl << endl;
    Del(list1, "Lisa");
    Showmen(list1);
    cout<<"-----------------------------------------------------------------------"<<endl << endl;
    AddLast(list1, "Mary", 162, 51.26);
    Showmen(list1);
    cout<<"-----------------------------------------------------------------------"<<endl << endl;

    return 0;
}






