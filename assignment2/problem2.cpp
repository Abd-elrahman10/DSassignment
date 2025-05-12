#include <iostream>
#include <limits>
#include <stdexcept>
#include <regex>
#include <fstream>
using namespace std;

struct Node{
    int ID;
    int height;
    string E_mail;
    string Name;
    string phone;

    Node* left;
    Node* right;

    Node(int key ,string name ,string number, string email){
        ID = key;
        Name = name;
        phone = number;
        E_mail = email;
        height = 1;

        left = nullptr;
        right = nullptr;

    }
};


class AVL{
private:
    Node* root;

    int getID(bool key){// it is function to get id in case to ensure uniqueness the key will turn true

        int id;
        while(true){
            try {
                cout << "enter your id:";
                cin >> id;

                if (cin.fail()){
                    throw ios_base::failure("invalid input, the ID must be number");
                }

                if(id < 0){
                    throw invalid_argument("the ID must be positive");
                }

                if (key){
                    Node* node = searchNode(root,id);

                    if (node != nullptr){
                        throw invalid_argument("the ID must be different");
                    }
                }

                return id;
            } catch (const ios_base::failure& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
    }

    int getHeight(Node* node){
        return (node == nullptr)? 0: node->height;
    }

    int getBalance(Node* node){
        return (node == nullptr)? 0: getHeight(node->left) - getHeight(node->right);
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node* rotate_left(Node* node){
        Node* Right = node->right;
        Node* RightLeft = Right->left;

        Right->left = node;
        node->right = RightLeft;

        node->height = max(getHeight(node->left), getHeight(node->right))+1;
        Right->height= max(getHeight(Right->left), getHeight(Right->right))+1;

        return Right;
    }

    Node* rotate_right(Node* node){
        Node* Left = node->left;
        Node* LeftRight = Left->right;

        Left->right = node;
        node->left = LeftRight;

        node->height = max(getHeight(node->left), getHeight(node->right))+1;
        Left->height= max(getHeight(Left->left), getHeight(Left->right))+1;

        return Left;

    }

    Node* insert_complete(Node* node, int ID,string name ,string number, string email){

        if (node == nullptr){
            return new Node(ID,name,number,email);
        }else if (ID > node->ID){
            node->right = insert_complete(node->right,ID,name,number,email);
        } else if (ID < node->ID){
            node->left = insert_complete(node->left,ID,name,number,email);
        }

        node->height = max(getHeight(node->left), getHeight(node->right))+1;

        int balance = getBalance(node);

        if (balance > 1){

            if (node->left->ID > ID){
                node = rotate_right(node);
            }

            else if (node->left->ID < ID){
                node = rotate_left(node->left);
                node = rotate_right(node);
            }

        }else if (balance <-1){

            if (node->right->ID < ID){
                node = rotate_left(node);
            }

            else if (node->right->ID > ID){
                node = rotate_right(node->right);
                node = rotate_left(node);
            }
        }

        return node;
    }

    Node* searchNode(Node* node,int id){// function to find node in the tree if exists
        if (node == nullptr || node->ID == id){
            return node;
        }

        if (node->ID < id){
            return searchNode(node->right,id);
        }else{
            return searchNode(node->left,id);
        }
    }

    Node* deleteNode(Node* node , int id){// function to delete and balance the tree after every delete

        // find the node and to balance the tree from deleted node to the root
        if (node->ID < id){
            node->right = deleteNode(node->right,id);
        } else if (node->ID > id){
            node->left = deleteNode(node->left, id);
            // when the node is found
        } else {
            // in case the node doesn`t have two children
            if (node->left == nullptr || node->right == nullptr) {
                Node *tmp = node->left != nullptr? node->left:node->right;

                // in case one child
                if (tmp == nullptr){
                    tmp = node;
                    node = nullptr;
                    // in case no children
                } else{
                    *node = *tmp;
                }

                delete tmp;
            }
                // in case two children
            else{

                Node* tmp = node->left;

                while (tmp->right != nullptr ){
                    tmp = tmp->right;
                }

                node->ID = tmp->ID;
                node->phone = tmp->phone;
                node->E_mail = tmp->E_mail;
                node->Name = tmp->Name;

                node->left = deleteNode(node->left,tmp->ID);
            }
        }

        if (node == nullptr){
            return node;
        }

        node->height = 1+ max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1){// in case the right part is greater than the left one

            if (getBalance(node->left) >= 0){ // in case
                node = rotate_right(node);
            }

            else if (getBalance(node->left) < 0){
                node = rotate_left(node->left);
                node = rotate_right(node);
            }

        }else if (balance <-1){

            if (getBalance(node->right) <= 0){
                node = rotate_left(node);
            }

            else if (getBalance(node->right) > 0){
                node = rotate_right(node->right);
                node = rotate_left(node);
            }
        }

        return node;
    }

    void inOrderTraversal(Node *node) {
        if (node == nullptr)
            return;
        inOrderTraversal(node->left);
        cout << "ID: " << node->ID << ", Name: " << node->Name
             << ", Phone: " << node->phone << ", Email: " << node->E_mail << endl;
        inOrderTraversal(node->right);
    }

    int calculateHeight(Node* node) {
        if (!node) return 0;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    void printSpaces(int count) {
        for (int i = 0; i < count; ++i)
            cout << ' ';
    }

    void printLevel(Node* node, int level, int indentSpace, int levelSpace) {
        if (!node) {
            printSpaces(indentSpace);
            cout << " ";
            printSpaces(levelSpace);
            return;
        }
        if (level == 1) {
            printSpaces(indentSpace);
            cout << node->ID;
            printSpaces(levelSpace);
        } else if (level > 1) {
            printLevel(node->left, level - 1, indentSpace, levelSpace);
            printLevel(node->right, level - 1, indentSpace, levelSpace);
        }
    }

    void printBranches(Node* node, int level, int indentSpace, int levelSpace) {
        if (!node) {
            printSpaces(indentSpace);
            cout << " ";
            printSpaces(levelSpace);
            return;
        }
        if (level == 1) {
            printSpaces(indentSpace);
            cout << (node->left ? "/" : " ");
            printSpaces(2);
            cout << (node->right ? "\\" : " ");
            printSpaces(levelSpace - 2);
        } else if (level > 1) {
            printBranches(node->left, level - 1, indentSpace, levelSpace);
            printBranches(node->right, level - 1, indentSpace, levelSpace);
        }
    }
public:

    AVL() : root(nullptr) {}

    ~AVL(){
        delete root;
    }

    void Add_content(){

        int id = getID(true);
        string name, phone, email;
        cin.ignore();

        while(true){

            regex FullName("[a-z]+ [a-z]+");

            cout << "Enter your name (firstname lastname):";
            getline(cin,name);

            if (regex_match(name,FullName)){
                name[0] = toupper(name[0]);

                for (int i = 0; i < name.length(); ++i) {
                    if (isspace(name[i])){
                        name[i+1] = toupper(name[i+1]);
                        i+=name.length();
                    }
                }

                break;
            }
            cout << "the name form is invalid, try again" << endl;
        }

        while(true){
            cout << "Enter your phone number:" ;
            getline(cin,phone);

            if (all_of(phone.begin(),phone.end(), ::isdigit) &&
                (phone.length() <= 11 && phone.length() >= 7)){
                break;
            }

            else if(!all_of(phone.begin(),phone.end(), ::isdigit)){
                cout << "the phone number must be all numbers" << endl;
            }

            else{
                cout << "the phone number digits must be between 7 and 11" << endl;
            }

        }

        while(true){
            cout << "Enter your email (...@Example.{com/org/..etc.}):" ;
            getline(cin,email);

            regex EmailEnd("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");


            if (regex_match(email,EmailEnd)){
                break;
            }

            cout << "the email form is invalid, try again" << endl;
        }


        root = insert_complete(root,id,name,phone,email);

        cout << "the Contents has been saved successfully" << endl;
    }

    void search(){
        int id = getID(false);

        Node* node = searchNode(root,id);

        if (node != nullptr){
            cout<<"Contact is founded\n";
            cout << "ID: " << node->ID << ", Name: " << node->Name
                 << ", Phone: " << node->phone << ", Email: " << node->E_mail << endl;
        }else{
            cout << "Contact with id : " << id<<" could not be found" <<endl;
        }
    }

    void Delete(){

        int id = getID(false);
        Node* node = searchNode(root,id);

        if (node != nullptr){
            root = deleteNode(root,id);
            cout << "Contact with id: "<<id << " is deleted successfully" << endl;
        } else{
            cout << "Contact with id: "<<id << " doesn`t exist" << endl;
        }
    }


    void printSortedByID() {
        cout << "\nContacts sorted by ID:\n";
        inOrderTraversal(root);
    }

    void printTreeWithSlashes() {
        if (!root) {
            cout << "Tree is empty!" << endl;
            return;
        }

        int height = calculateHeight(root);
        int indentSpace = 6;
        int levelSpace = 2;

        for (int i = 1; i <= height; ++i) {
            printLevel(root, i, indentSpace, levelSpace);
            cout << endl;
            if (i != height) {
                printBranches(root, i, indentSpace, levelSpace);
                cout << endl;
            }
            indentSpace /= 2;
            levelSpace = levelSpace * 2 / 3;
            if (indentSpace < 1) indentSpace = 1;
            if (levelSpace < 1) levelSpace = 1;
        }
    }

    void processTestFile(int testCaseNumber, const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        bool foundTestCase = false;
        bool processingTestCase = false;

        while (getline(file, line)) {
            // Skip empty lines
            if (line.empty()) continue;

            // Check for test case number
            if (line[0] == '#') {
                // Extract number after #
                int currentTestCase = stoi(line.substr(1));

                if (currentTestCase == testCaseNumber) {
                    foundTestCase = true;
                    processingTestCase = true;
                    cout << "\nProcessing Test Case " << line << endl;
                    continue;
                } else if (processingTestCase) {
                    // If we were processing a test case and found a new #, stop processing
                    break;
                }
            }

            // Only process commands if we're in the right test case
            if (processingTestCase) {
                if (line == "add content:") {
                    while (true) {
                        string field;
                        getline(file, field);
                        if (field.empty()) break;

                        // Extract ID
                        int id = stoi(field.substr(field.find(":") + 1));

                        // Extract Name
                        getline(file, field);
                        string name = field.substr(field.find(":") + 1);
                        name.erase(0, name.find_first_not_of(" "));

                        // Extract Email
                        getline(file, field);
                        string email = field.substr(field.find(":") + 1);
                        email.erase(0, email.find_first_not_of(" "));

                        // Extract Phone
                        getline(file, field);
                        string phone = field.substr(field.find(":") + 1);
                        phone.erase(0, phone.find_first_not_of(" "));

                        root = insert_complete(root, id, name, phone, email);
                        cout << "Added contact with ID: " << id << endl;
                    }
                }
                else if (line == "show the tree") {
                    printTreeWithSlashes();
                }
                else if (line == "delete" ) {
                    int id;
                    while (file >> id) {
                        Node* node = searchNode(root, id);
                        if (node != nullptr) {
                            root = deleteNode(root, id);
                            cout << "Contact with id: " << id << " is deleted successfully" << endl;
                        } else {
                            cout << "Contact with id: " << id << " doesn't exist" << endl;
                        }
                        file.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (file.peek() == '\n' || file.peek() == EOF) break;
                    }
                }
                else if (line == "search") {
                    int id;
                    while (file >> id) {
                        Node* node = searchNode(root, id);
                        if (node != nullptr) {
                            cout << "Contact is found\n";
                            cout << "ID: " << node->ID << ", Name: " << node->Name
                                 << ", Phone: " << node->phone << ", Email: " << node->E_mail << endl;
                        } else {
                            cout << "Contact with id: " << id << " could not be found" << endl;
                        }
                        file.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (file.peek() == '\n' || file.peek() == EOF) break;
                    }
                }
                else if (line == "show sorted list") {
                    printSortedByID();
                }
                else if (line == "exit") {
                    break;
                }
            }
        }

        if (!foundTestCase) {
            cout << "Test case #" << testCaseNumber << " not found in the file." << endl;
        }

        file.close();
    }

};

void menu(AVL &tree){
    int c;

    try {
        cout << "1) Add New Contacts" << endl;
        cout << "2) Search For Contacts" << endl;
        cout << "3) Delete a Contacts" << endl;
        cout << "4) show all Contacts (ascending-ly by ID)" << endl;
        cout << "5) show the tree" << endl;
        cout << "6) Exit" << endl;
        cin >> c;

        if (cin.fail()){
            throw ios_base::failure("the input must be number" );
        }

    } catch (const ios_base::failure& e) {
        cout << e.what() <<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        menu(tree);
    }


    if(c == 1){
        tree.Add_content();
        menu(tree);
    }else if (c == 2){
        tree.search();
        menu(tree);
    } else if (c == 3){
        tree.Delete();
        menu(tree);
    }else if (c == 4){
        tree.printSortedByID();
        menu(tree);
    }else if (c == 5){
        tree.printTreeWithSlashes();
        menu(tree);
    } else if (c == 6){
        exit(0);
    }else{
        cout << "invalid choice, Please try again" << endl;
        menu(tree);
    }
}


int main(){
    AVL tree;


    tree.processTestFile(1, "TestCases2.txt");
    return 0;
}
