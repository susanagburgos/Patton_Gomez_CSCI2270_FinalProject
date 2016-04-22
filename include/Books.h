#ifndef BOOKS_H
#define BOOKS_H
#include <iostream>
using namespace std;


struct BooksNode{
    string title;
    string author;
    string description;
    string review;
    int quantity;
    int price;
    BooksNode *parent;
    BooksNode *leftChild;
    BooksNode *rightChild;

    BooksNode(){};

    BooksNode(int in_quantity, string in_title, string in_author, int in_price, string in_descr, string in_review)
    {
        description = in_descr;
        author = in_author;
        review = in_review;
        title = in_title;
        quantity = in_quantity;
        price = in_price;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }
};

struct Cart{

    Cart * next;
    string name;
    int price;
    int quantity;

    Cart(){}; // default constructor

    Cart(string initName, Cart *initNext, int initPrice, int initQuantity)
    {
        name = initName;
        next = initNext;
        price = initPrice;
        quantity = initQuantity;
    }
};

class Books
{

    public:
        Books();
        ~Books();
        void createBookTree(string FileName);
        void addBooksNode(int quantity, string title, string author, int price, string description, string review);
        void printBookInventory();
        int countBooksNodes();
        void deleteBooksNode(string title);
        void addBooksNode(int ranking, string title, int releaseYear, int quantity);
        void findMovie(string title);
        void buyBooks(string title);
        int calculatePrice(BooksNode * Node);
        void insertReview(string title);
        void addToCart(string title);
        void checkout(); //will call print cart here as well and ask questions etc.
        ///function to write reviews
        ///Make your own booklist! :D
    protected:

    private:
        void DeleteAll(BooksNode * node); //use this for the post-order traversal deletion of the tree
        void printBookInventory(BooksNode * node);
        void countBookNodes(BooksNode *node, int *c);
        BooksNode* search(string title);
        BooksNode* treeMinimum(BooksNode *node);
        BooksNode *root;
};

#endif // MOVIETREE_H
