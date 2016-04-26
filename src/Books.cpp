#include "Books.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

Books::Books()
{
    //ctor
}

Books::~Books()
{
    //dtor
    DeleteAll(root);
}

void Books::createBookTree(Books & b, char const*  fileName)
{
    ifstream inFile;
    inFile.open(fileName);
    if(inFile.good())
    {
        string bookData;
        while(getline(inFile, bookData))
        {
            stringstream ss(bookData);
            string temp;

            getline(ss, temp, ',');
            int quantity = atoi(temp.c_str());

            getline(ss, temp, ',');
            string title = temp;

            getline(ss, temp, ',');
            string author = temp;

            getline(ss, temp,',');
            int price = atoi(temp.c_str());

            getline(ss, temp, ',');
            string description = temp;

            getline(ss, temp, ',');
            string review = temp;
            b.addBooksNode(quantity,title,author,price,description,review);
        }
    }else{
        cout<<"no"<<endl;
    }
    inFile.close();
}

void Books::printBookInventory() //public
{
    printBookInventory(root);
}

void Books::addBooksNode(int quantity, string title, string author, int price, string description, string review)
{
    BooksNode *tmp = root;
    BooksNode *parent = NULL;
    BooksNode *node = new BooksNode(quantity, title, author, price, description, review);
    while(tmp!=NULL)
    {
        parent = tmp;
        if(node->title.compare(tmp->title)<0){
            tmp = tmp->left;
        }else{
            tmp = tmp->right;
        }
    }
    if(parent == NULL){
        root = node;
    }
    else if(node->title.compare(parent->title)<0){
        parent->left = node;
        node->parent = parent;
    }else{
        parent->right = node;
        node->parent = parent;
    }
}

void Books::addBook(string name)
{
    BooksNode *node = search(name);
    if(node != NULL)
    {
        addToCart(node);
    }else
    {
        cout<<"Book was not found"<<endl;
    }
}

void Books::addToCart(BooksNode *node)
{
    Cart * addBook;
   // BooksNode * traverse = head;
    if(head == NULL){
        addBook = new Cart(node->title, NULL, node->price, node->author);
        head = addBook;
    }else{
        Cart * tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        addBook = new Cart(node->title, NULL, node->price, node->author);
        tmp->next = addBook;
    }
}

void Books::viewCart(){
    int counts = 0;
    if (head == NULL)
        cout<<endl;
    else
    {
        Cart *current = head;
        cout<<endl;
        while (current->next != NULL)
        {
            cout<<"+ "<<current->name<<endl;
            current = current->next;
            counts++;
        }
        cout<<"+ "<<current->name<<endl;
        counts++;
        cout<<endl;
    }
    cout<<"You have "<<counts<<" book(s) in your cart"<<endl;
}

void Books::findMovie(string title)
{
    BooksNode *searched = search(title);
    if (searched != NULL) {
        cout << "Book Info:" << endl;
        cout << "=========" << endl;
        cout << "Quantity: " << searched->quantity <<endl;
        cout << "Title: " << searched->title <<endl;
        cout << "Author: " << searched->author <<endl;
        cout << "Price: " << searched->price <<endl;
        cout << "Description: " << searched->description <<endl;
        cout << "Review: " << searched->review <<endl;
        cout<<"Do you want to buy this movie?"<<endl;
        string buy;
        getline(cin,buy);
        if(buy == "yes"){
            addToCart(searched);
        }
    }else{
        cout << "Book not found." << endl;
    }
}


void Books::buyBooks(string title)
{
    BooksNode *foundBook = search(title);

    if(foundBook != NULL) //need to double check that search did in fact return a movie
    {
       if(foundBook->quantity != 0)
       {
         foundBook->quantity--;

        cout << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Quantity: " << foundBook->quantity <<endl;
        cout << "Title: " << foundBook->title <<endl;
        cout << "Author: " << foundBook->author <<endl;
        cout << "Price: " << foundBook->price <<endl;
        cout << "Description: " << foundBook->description <<endl;
        cout << "Review: " << foundBook->review <<endl;
        if(foundBook->quantity == 0)
            {
                deleteBooksNode(title); //we don't want to go here
            }
       }
    }
      else
      {
       cout << "Book not found." << endl;
      }
}

void Books::printBookInventory(BooksNode * tmp) //private
{
   int counts = 0;
   if(tmp->left != NULL)
    {
        printBookInventory(tmp->left);

    }
    cout<< "Book: " <<tmp->title<<" "<<tmp->quantity<<endl;
    counts++;
    if(tmp->right != NULL)
    {
        printBookInventory(tmp->right);
    }

    cout<<"We have "<<counts<<"books in our inventory"<<endl;
}

BooksNode* Books::search(string title)
{
    BooksNode *tmp = root;

    while(tmp != NULL)
    {
        if(tmp->title.compare(title) < 0)
        {
            tmp = tmp->right;
        }
        else if(tmp->title.compare(title) > 0)
        {
            tmp = tmp->left;
        }
        else
        {
            return tmp;
        }
    }
    return NULL; //tmp will get set to NULL if is a book we don't have on the list
}

int Books::countBooksNodes() //public
{
    int *c = new int;
    *c = 0; // the star changes our values otherwise we would be changing the address.
    countBookNodes(root, c);
    return *c; //returns number of movies

}

void Books::countBookNodes(BooksNode *node, int *c)
{
   if(node->left != NULL)
    {
        countBookNodes(node->left, c);
    }
    *c = *c + 1;
    if(node->right != NULL)
    {
        countBookNodes(node->right, c); //I'm calling a fct with two inputs and I was forgetting to add the c
    }
}

BooksNode* Books::treeMinimum(BooksNode *node)
{
    while(node->left != NULL) //if the node
    {
        node = node->left; //treeMinimum(node->leftChild); //this will call a recursion for this fct to find the smallest value
    }
    return node; //this should return all the information about the last node

}

/******* FUNCTION TO DELETE BOOK IF QUANTITY IS ZERO *******/
void Books::deleteBooksNode(std::string title)
{
    BooksNode* node = search(title);
    ///if the tree is empty
    if(node == NULL){
        cout << "Book not found." << endl;
    }
    /**BOOK TO BE DELETED IS NOT THE ROOT**/
    else if(node != root)
    {///NO CHILDREN
        if(node->left == NULL && node->right == NULL){
            if(node == node->parent->left){
                node->parent->left = NULL;
            }else{
                node->parent->right = NULL;
            }
        }///TWO CHILDREN
        else if(node->left != NULL && node->right != NULL){
            BooksNode* mini = treeMinimum(node->right);
            if(node == node->parent->left){ //left
                if(mini == node->right){//if mini is the right child
                    node->parent->left = mini;
                    node->left->parent = mini;
                    mini->parent = node->parent;
                    mini->left = node->left;
                }else{
                    mini->parent->left = mini->right;
                    mini->parent = node->parent;
                    mini->right->parent = mini->parent;
                    node->parent->left = mini;
                    mini->left = node->left;
                    mini->right = node->right;
                    node->right->parent = mini;
                    node->left->parent = mini;
                }
            }else //right
            {
                if(mini == node->left){
                    node->parent->right = mini;
                    node->right->parent = mini;
                    mini->parent = node->parent;
                    mini->right = node->right;
                }else{
                    mini->parent->right = mini->left;
                    mini->parent = node->parent;
                    mini->left->parent = mini->parent;
                    node->parent->right = mini;
                    mini->right = node->right;
                    mini->left = node->left;
                    node->left->parent = mini;
                    node->right->parent = mini;
                }
            }
        }
        else///ONE CHILD
        {
            if(node->right == NULL && node->left!=NULL){///only left
                if(node->parent->left == node){///is left child
                    BooksNode* x = node->left;
                    node->parent->left = x;
                }else{///right child
                    BooksNode* x = node->left;
                    node->parent->right = x;
                    x->parent = node->parent;
                }
            }else{ ///only right
                if(node->parent->right == node){///right child
                    BooksNode* x = node->right;
                    node->parent->right = x;
                    x->parent = node->parent;
                }else{///left child
                    BooksNode* x = node->right;
                    node->parent->left = x;
                    x->parent = node->parent;
                }
            }
        }
    }
    /******* end of not root*******/
    /**BOOK TO BE DELETED IS THE ROOT**/
    else
    {
        if(node->left == NULL && node->right == NULL)///no children
        {
            //root is deleted
        }
        else if(node->left != NULL && node->right != NULL)///two kids
        {
            BooksNode *node = root;
            BooksNode* mini = treeMinimum(node->right);
            if(mini->parent == root){
                if(mini->right != NULL){
                    mini->parent->right = mini->right;
                    mini->parent = mini->parent;
                }else{
                    mini->parent->right = NULL;
                    mini->parent = NULL;
                }
            }else{
                if(mini->right != NULL){
                    mini->parent->left = mini->right;
                    mini->right->parent = mini->parent;
                }else{
                    mini->parent->left = NULL;
                    mini->parent = NULL;
                }
            }
            mini->left = root->left;
            mini->right = root->right;
            if(mini->left != NULL){
                mini->left->parent = mini;
            }
            if(mini->right != NULL){
                mini->right->parent = mini;
            }
            delete root;
            root = mini;
        }else{///one child
            if(node->right == NULL && node->left!=NULL){
                BooksNode* x = node->left;
                x = root;
                x->parent = NULL;
            }else{
                BooksNode* x = node->right;
                x = root;
                x->parent = NULL;
            }
        }
    }
    delete node; ///deleting book that user selected
}

void Books::cartDelete(string book){
    //find city and delete it
    Cart *delBook = NULL;
    Cart *searchBook = head;
    bool found = false;

    while(!found and searchBook != NULL){
        if(searchBook->name == book){
            found = true;
        }else
        {
            searchBook = searchBook->next;
        }
    }
    if(found == true){
        if(searchBook == head){
            delBook = head;
            head = head->next;
            delete delBook;
        }else{

            delete searchBook;
        }
    }else{
        cout<<book<<"not found"<<endl;
    }
}


void Books::DeleteAll(BooksNode * node) //use this for the post-order traversal deletion of the tree - post order deletes from root to kids
{
    if(node->left != NULL) //children are deleted before the root value
    {
        DeleteAll(node->left);
    }
    if(node->right)
    {
        DeleteAll(node->right);
    }
    cout<<"Deleting: "<<node->title<<endl;
    delete node;
}
