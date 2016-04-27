#include "Books.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

Books::Books()
{
    //ctor
}

Books::~Books()
{
    //dtor
}

/** CREATE THE BOOK LIBRARY FROM TEXT FILE **/
void Books::createBookTree(Books & b, char const * fileName)
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
            int rating = atoi(temp.c_str());
            b.addBooksNode(quantity,title,author,price,description,rating);
        }
    }else{
        cout<<"file not opened"<<endl;
    }
    inFile.close();
}
/** FUNCTION TO SEARCH THROUGH BST **/
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

/** PUBLIC FUNCTION TO CALL PUBLIC PRINT BOOK INVENTORY **/
void Books::printBookInventory() //public
{
    printBookInventory(root);
}

///PRIVATE PRINTING FUNCTION FOR LIBRARY BOOKS (BST PRINT)
void Books::printBookInventory(BooksNode * tmp) //private
{
   if(tmp->left != NULL)
    {
        printBookInventory(tmp->left);

    }
    cout<< "Book: " <<tmp->title<<endl;
    cout<< "Author: "<<tmp->author<<endl;
    cout<< "Price: $"<<tmp->price<<endl;
    cout<< "Quantity: "<<tmp->quantity<<endl;
    if(tmp->rating == 0){
            cout<<"Rating: not yet rated"<<endl;
    }else{
    cout << "Rating: " << tmp->rating <<endl;
    }
    cout<< "------------------------------------------------"<<endl;
    if(tmp->right != NULL)
    {
        printBookInventory(tmp->right);
    }
}

/** FIND A BOOK IN THE LIBRARY **/
void Books::findBook(string title)
{
    BooksNode *searched = search(title);
    if (searched != NULL) {
        cout << "Book Info:" << endl;
        cout << "=========" << endl;
        cout << "Quantity: " << searched->quantity <<endl;
        cout << "Title: " << searched->title <<endl;
        cout << "Author: " << searched->author <<endl;
        cout << "Price: $" << searched->price <<endl;
        cout << "Description: " << searched->description <<endl;
        if(searched->rating == 0){
            cout<<"Rating: not yet rated"<<endl;
        }else{
        cout << "Rating: " << searched->rating <<endl;
        }
        cout<<"Do you want to buy this book? (yes/no)"<<endl;
        string buy;
        getline(cin,buy);
        if(buy == "yes" || buy == "Yes" || buy == "y"){
            addBook(title);
        }
    }else{
        cout << "Book not found." << endl;
    }
}

/** RATE A BOOK IN THE LIBRARY **/
void Books::insertRating(string title)
{
    BooksNode *searched = search(title);
    if(searched != NULL)
    {
        string rate;
        cout<<"Book: "<<searched->title<<endl;
        cout<<"Add a rating: (1-5)"<<endl;
        getline(cin, rate);
        int rating = atoi(rate.c_str());
        bool range = false;
        while(!range)
        {
            int rating = atoi(rate.c_str());
            if(rating >= 1 && rating <= 5)
            {
                range = true;
                searched->rating = rating;
                break;
            }
            cout<<"Rating must be be from 1 to 5. Try again:"<<endl;
            getline(cin, rate);
        }
    }else{
        cout<<"Book not found."<<endl;
    }
}

/** COUNT BOOKS IN LIBRARY**/
int Books::countBooksNodes() //public
{
    int *c = new int;
    *c = 0; // the star changes our values otherwise we would be changing the address.
    countBookNodes(root, c);
    return *c; //returns number of movies

}
///PRIVATE COUNT
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

/** TREE MIN FOR DELETING NODE **/
BooksNode* Books::treeMinimum(BooksNode *node)
{
    while(node->left != NULL) //if the node
    {
        node = node->left; //treeMinimum(node->leftChild); //this will call a recursion for this fct to find the smallest value
    }
    return node; //this should return all the information about the last node

}

///possibly allow user to add a book
void Books::addBooksNode(int quantity, string title, string author, int price, string description, int rating)
{
    BooksNode *tmp = root;
    BooksNode *parent = NULL;
    BooksNode *node = new BooksNode(quantity, title, author, price, description, rating);
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

/** UPDATE QUANTITY IN LIBRARY WHEN BOOK IS ADDED TO CART**/
void Books::booksLeft(string title)
{
    BooksNode *foundBook = search(title);
    if(takeout == true)
    {
        takeout = false;
        cout << foundBook->title<< " has been removed from cart." << endl;
        foundBook->quantity++;
    }
    else if(foundBook != NULL)
    {
        if(foundBook->quantity != 0)
        {
            foundBook->quantity--;
            cout << "Book has been added to cart." << endl;
            cout << "Book Info:" << endl;
            cout << "==========" << endl;
            cout << "Title: " << foundBook->title <<endl;
            cout << "Author: " << foundBook->author <<endl;
            cout << "Price: $" << foundBook->price <<endl;
            if(foundBook->quantity == 0){
                stock = true; //no longer in stock
            }
        }

    }else{
        cout << "Sorry. Book not currently in stock." << endl;
    }
}

///********************* LINKED LIST *********************///

/** ADD A BOOK TO CART -- CREATES LINKED LIST OF CART CONTENTS **/
void Books::addBook(string name)
{
    BooksNode *node = search(name);
    if(node != NULL)
    {
        addToCart(node);
        if(stock != true){
            booksLeft(name);
        }
    }else{
        cout<<"Book was not found"<<endl;
    }
}

void Books::addToCart(BooksNode *node)
{
    stock = false;
    if(node->quantity == 0){
        cout<<"Sorry. Book not currently in stock."<<endl;
        stock = true;
    }
    else{
        Cart * addBook;
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
}

/** LINKED LIST PRINT TO SEE CART CONTENTS **/
void Books::viewCart()
{
    int counts = 0;
    if (head == NULL)
        cout<<endl;
    else{
        Cart *current = head;
        cout<<endl;
        while (current->next != NULL)
        {
            cout<<"+ "<<current->name<<", "<<current->author<<" - $"<<current->price<<endl;
            current = current->next;
            counts++;
        }
        cout<<"+ "<<current->name<<", "<<current->author<<" - $"<<current->price<<endl;
        counts++;
        cout<<endl;
    }
    cout<<"You have "<<counts<<" book(s) in your cart"<<endl;
    int price = calculatePrice();
    cout<<"Your current total is: $"<<price<<endl;
}

/** CALCULATE PRICE OF BOOKS IN CART **/
int Books::calculatePrice()
{
    int price = 0;
    Cart * tmp = head;
    while(tmp != NULL)
    {
        price = price + tmp->price;
        tmp = tmp->next;
    }
    return price;
}

/** DELETE A BOOK FROM YOUR CART **/
void Books::deleteCartNode(string book){
    takeout = true;
    Cart *delBook = NULL;
    Cart *searchBook = head;
    Cart *pretemp = head;
    int counter = 0;
    bool found = false;
    while(!found && searchBook != NULL){
        if(searchBook->name == book){
            found = true;
        }else{
            searchBook = searchBook->next;
            if(counter != 0)
            {
                pretemp = pretemp->next;
            }
            counter++;
        }
    }
    if(found == true){
        booksLeft(book);
        if(searchBook == head){
            delBook = head;
            head = head->next;
            delete delBook;
        }else{
            pretemp->next = searchBook->next;
            delete searchBook;
        }
    }else{
        cout<<book<<" not found"<<endl;
    }
}

/** THIS FUNCTION ALLOWS THE USER TO CHECKOUT AND PURCHASE THEIR BOOKS **/
void Books::checkout()
{
    if (head == NULL)
    {
        cout<<"Your cart is empty!"<<endl;
    }else{
        int counts = 1;
        cout<< "  CHECKOUT  " <<endl;
        cout<< "============" <<endl;
        cout<< "Your Items:" <<endl;
        Cart *current = head;
        while (current->next != NULL)
        {
            cout<<counts<<". "<<current->name<<", "<<current->author<<" + $"<<current->price<<endl;
            current = current->next;
            counts++;
        }
        cout<<counts<<". "<<current->name<<", "<<current->author<<" + $"<<current->price<<endl;
        cout<<endl;
        int price = calculatePrice();
        cout<<"Your total is: $"<<price<<endl;
        string checkout;
        cout<<"Proceed to checkout? (y/n)"<<endl;
        getline(cin,checkout);
        if(checkout == "y" || checkout == "yes" || checkout == "Yes"){
            int days = 0;
            string username;
            cout<<"Name: ";
            getline(cin, username);
            bool ship = false;
            while(!ship)
            {
                string method;
                cout<<"Preferred Shipping Method: (1, 2, or 3)"<<endl;
                cout<<"1. Express (2 days) - $4"<<endl;
                cout<<"2. Standard (5-7 days) - $2"<<endl;
                cout<<"3. No Rush (10-14 days) - FREE"<<endl;
                getline(cin, method);
                if(method == "1"){
                    ship = true;
                    price = price + 4;
                    days = 2;
                }
                else if(method == "2"){
                    ship = true;
                    price = price + 2;
                    days = 7;
                }
                else if(method == "3"){
                    ship = true;
                    days = 14;
                }
                else{
                    cout<<"Please enter a valid shipping method. (1, 2, or 3)"<<endl;
                }
            }
            cout<<"Thank you, "<<username<<"!"<<endl;
            cout<<"Your order will arrive within "<<days<<" days."<<endl;
            cout<<"Your total cost is $"<<price<<"."<<endl;
        }
    }

cout<<endl;
cout<<"Goodbye!"<<endl; ///the program exits after the user checks out
exit(0);
}
