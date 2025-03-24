#include <bits/stdc++.h>
#define ll long long
using namespace std;
class Node{
public:
    int data;
    Node* next;
Node(int val){
    data=val;
    next = nullptr;
}
};




class SortedLinkedList{
private:
     Node* head;

public:

 SortedLinkedList(){
        head= nullptr;
}


 void insert(int value){
  Node* newnode=new Node(value);

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
Node* current=head;
Node* trailcurrent= nullptr;
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


int operator[] (int index){
     Node* current=head;
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
    Node* current=head;
    Node* tailcurrent= nullptr;

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

friend ostream& operator<<(ostream& os,const SortedLinkedList& List){

Node* temp=List.head;
    while(temp!=NULL){
        os<<temp->data<<" ";
        temp=temp->next;
    }
    return os;
    }

  ~SortedLinkedList() {
        while (head) {

            Node* temp = head;
            head = head->next;
            delete temp;
        }


}
};

int main() {
SortedLinkedList L;

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

    return 0;
}


