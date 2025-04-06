#include <bits/stdc++.h>

using namespace std;

template<class T>
class Node{
public:
    T data;
    Node* next;
Node(T val){
    data=val;
    next = nullptr;
}
};



template<class T>
class SortedLinkedList{
private:
     Node<T>* head;

public:

 SortedLinkedList(){
        head= nullptr;
}


 void insert(T value){
  Node<T>* newnode=new Node<T>(value);

 if(head==NULL){//case 1 list is empty
     head =newnode;
     newnode->next=NULL;
     return;
 }
 if(head->data>=value){
     newnode->next=head;
     head=newnode;
     return;
 }
else{
Node<T>* current=head;
Node<T>* trailcurrent= nullptr;
bool found=false;
       while (!found&&current!=NULL){
                if(current->data>=value)//is new node is less than some element
                    found=true;

                else{
                    trailcurrent=current;
                    current=current->next;
                }
            }

            if(current==head){//if list has one element before
                newnode->next=head;
                head=newnode;
                current->next=NULL;
            }
            else{
                trailcurrent->next=newnode;
                newnode->next=current;
            if(current==NULL){
                trailcurrent->next=newnode;
                newnode->next=NULL;
            }


            }

}

}


T operator[] (int index){
     Node<T>* current=head;
bool found = false;
int i =0;
  while(current!=NULL){
      if(i==index){
          found=true;
          return current->data;

      }
      i++;
      current=current->next;
  }
    if(!found)
        throw out_of_range("Index out of range");


 }

void remove(int index){
    Node<T>* current=head;
    Node<T>* tailcurrent= nullptr;

    if(index==0){
        head=head->next;
        delete current;
        delete tailcurrent;
        return;
    }
    for (int i = 0; i <= index &&current!=NULL; ++i) {
         if(i==index){
            tailcurrent->next=current->next;
            delete current;
            return;
        }
        tailcurrent=current;
        current=current->next;

    }

 }

friend ostream& operator<<(ostream& os,const SortedLinkedList<T>& List){

Node<T>* temp=List.head;
    while(temp!=NULL){
        os<<temp->data<<" ";
        temp=temp->next;
    }
    return os;
    }

  ~SortedLinkedList() {
        while (head) {

            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }


}
};


void test(int testCaseNumber) {
    SortedLinkedList<int> L;
    ifstream file ("test_cases.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    string line;
    bool testCaseFound = false;

    while (getline(file , line)) {
        if (line.empty()) continue;

        if (line[0] == '#') {
            int currentTestCase = stoi(line.substr(1));
            if (currentTestCase == testCaseNumber) {
                testCaseFound = true;
                cout << line << endl;
            } else if (testCaseFound) {
                break;
            }
        } else if (testCaseFound) {
            if (line.substr(0, 6) == "insert") {
                int value = stoi(line.substr(7));
                L.insert(value);
            } else if (line.substr(0, 6) == "delete") {
                int index = stoi(line.substr(7));
                L.remove(index);
            } else if (line == "-------------------------------------") {
                try {
                    cout << "First element: " << L[0] << endl;

                    cout << "List: " << L << endl;
                } catch (const out_of_range& e) {
                    cout << "List is empty" << endl;
                }
                cout << "-------------------------------------" << endl;
                break;  // End of test case
            }
        }
    }

    if (!testCaseFound) {
        cout << "Test case #" << testCaseNumber << " not found!" << endl;
    }

}

int main() {
SortedLinkedList<char> L;

/*//Test case 1

    L.insert(5); // L = [5]
    L.insert(8); // L = [5, 8]
    L.insert(7); // L = [5, 7, 8]
    L.insert(6); // L = [5, 6, 7, 8]
    L.insert(6); // L = [5, 6, 6, 7, 8]
    cout << L<<endl; // Output: [5, 6, 6, 7, 8]

   */

/*
//Test case 2
    cout << L[2]; // Output: 6
    cout << L[10]; // Throws out_of_range exception*/




/*
//Test case 3
    L.remove(0); // L = [6, 6, 7, 8]
    cout << L; // Output: [6, 6, 7, 8]
    L.remove(100); // No change (out of bounds)
    cout << L; // Output: [6, 6, 7, 8]
    L.remove(2); // L = [6, 6, 8]
    cout << L; // Output: [6, 6, 8]
    L.remove(2); // L = [6, 6]
    cout << L; // Output: [6, 6]
*/
    test(1);


    return 0;
}


