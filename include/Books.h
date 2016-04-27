#ifndef BOOKS_H
#define BOOKS_H
#include <iostream>

using namespace std;


struct BooksNode{
    string title;
    string author;
    string description;
    int rating;
    int quantity;
    int price;
    BooksNode *parent;
    BooksNode *left = NULL;
    BooksNode *right = NULL;

    BooksNode(){};

    BooksNode(int in_quantity, string in_title, string in_author, int in_price, string in_descr, int in_rating)
    {
        description = in_descr;
        author = in_author;
        rating = in_rating;
        title = in_title;
        quantity = in_quantity;
        price = in_price;
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};

struct Cart{
    Cart * next;
    string name;
    string author;
    int price;
    int quantity;

    Cart(){}; // default constructor

    Cart(string initName, Cart *initNext, int initPrice, string initAuthor)
    {
        name = initName;
        next = initNext;
        price = initPrice;
        author = initAuthor;
    }
};

class Books
{
    public:
        Books();
        ~Books();
        bool stock = false; //checks to see if book is in stock
        bool takeout = false; //for taking book out of cart
        void createBookTree(Books & b, char const * fileName); //Builds the library from books in files
        void addBooksNode(int quantity, string title, string author, int price, string description, int rating); //adds books into BST
        void printBookInventory(); //print out books in the library
        int countBooksNodes(); //counts how many books are in library
        void deleteCartNode(string book); //delete book from cart -- linked list delete
        void findBook(string title); //find a book and display information
        void booksLeft(string title); //when you add or delete from cart, function updates quantity of book in library
        void viewCart(); //prints cart -- linked list
        void addBook(string name); //part of linked list add function to check if exists and call quantity
        void addToCart(BooksNode * node);//add book to cart -- linked list
        void insertRating(string title); //rate a book in the library
        int calculatePrice(); //will calculate the total price
        void checkout(); //will call print cart items and ask questions etc.

    protected:

    private:
        void printBookInventory(BooksNode * node);
        void countBookNodes(BooksNode *node, int *c);
        BooksNode* search(string title);
        BooksNode* treeMinimum(BooksNode *node);
        BooksNode * root = NULL;
        Cart * head = NULL;
};

#endif
