#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    // Node sturcture: set data and pointers.
    struct Node {
        int data;
        Node* prev;
        Node* next;
        // Constructor that initialize node's data and pointers.
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    // Pointer to the first and the last node in list.
    Node* head;
    Node* tail;

public:
    // Constructor: initialize head and tail null.
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // void function that insert node after position. Also, Check whether conditions are correct or uncorrect.
    void insert_after(int value, int position) {
        // Checking position is positive.
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        // Checking list is empty and if it is empty, set head and tail to newNode.
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        // for loop that set temp to next until i reach position and temp both.
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        // Checking position exceeding the list size or not. Then show message and delete newNode.
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        // Replacing elements in newnode to elements in temp.
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    // void function that delete node with value.
    void delete_val(int value) {
        // Check the list is empty.
        if (!head) return;

        Node* temp = head;
        
        // while loop: Find node with the value.
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        // If the pointer pass the prev make temp goes to the next directly.
        if (temp->prev)
            temp->prev->next = temp->next;
        // If it's the head node, set head to next node.
        else
            head = temp->next; 
        // Doing same thing like previous code, but for next.
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;    // Delete the node.
    }

    // void function that delete node with position.
    void delete_pos(int pos) {
        // Cheking the list is emtpy.
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        // If position is the first node, run bring pop_front function and run.
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        // for loop until i(node) reach at position.
        for (int i = 1; i < pos; i++){
            // If temp is nullptr then show message and return.
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            // Move to the next.
            else
                temp = temp->next;
        }
        // After for loop, if temp is nullptr again, the position does not exist.
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        // If the last node should be deleted, run pop_back function.
        if (!temp->next) {
            pop_back();
            return;
        }
    
        // Get previous next node and set previous node to current next node then do it again with the opposite way
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    // void function that insert a value node at the end of the list.
    void push_back(int v) {
        Node* newNode = new Node(v);
        // If the list is empty, set head and tail to new node.
        if (!tail)
            head = tail = newNode;
        // Setting each pointers to others.
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    // void function that insert a value node at the beginning of the list.
    void push_front(int v) {
        Node* newNode = new Node(v);
        // If list empty, set head, tail to new node.
        if (!head)
            head = tail = newNode;
        //  Setting each pointers to others.
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    // void function that remove the front node.
    void pop_front() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        // Store the current head node.
        Node * temp = head;

        // If there are more than one node set head pointers to next node and set previous pointer to nullptr.
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        // With only one node, set head and tail nullptr.
        else
            head = tail = nullptr;
        delete temp;
    }

    // void function that remove the back node.
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        // Store the current tail node.
        Node * temp = tail;

        // Same as the pop_front function but doing for tail.
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    // Desturctor that deleing all of nodes.
    ~DoublyLinkedList() {
        // while loop that deleting until the list becomes empty.
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // void function that print all nodes (head to tail).
    void print() {
        Node* current = head;   // Set to starting from the head.
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        // while loop that print each data from nodes.
        while (current) {
            cout << current->data << " ";   // Print current node's data
            current = current->next;        // Move to next.
        }
        cout << endl;
    }

    // void function that print all nodes (tail to head).
    void print_reverse() {
        Node* current = tail;   // Set to starting from the tail.
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        // while loop that print each data from nodes. (same as print function)
        while (current) {
            cout << current->data << " ";   // Pirnt current node's data
            current = current->prev;        // Move to previous node.
        }
        cout << endl;
    }

    // void function that prints every other data from nodes.
    void every_other_element() {
        Node* current = head;   // Starting from head.
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }

        // Decide whether print or skip the current node.
        bool print = true;
        // while loop, and if print is true, print node data.
        while (current) {
            if (print) {
                cout << current->data << " ";
            }
            // Move to the next node.
            current = current->next;
            // Keep changing print true and false then it will keep change that printing and skiping.
            print = !print;
        }
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    DoublyLinkedList list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(4);
    list.push_front(5);
    list.push_front(6);

    cout << "print function: " << endl;
    list.print();

    cout << "Testing every other element function: " << endl;
    list.every_other_element();
    
    return 0;
}