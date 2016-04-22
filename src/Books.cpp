#include "Books.h"
#include <iostream>

using namespace std;

Books::Books()
{
    //ctor
}

Books::~Books()
{
    //dtor
    DeleteAll(root); //calling just here bc it's a private
}

//void Books::createBookTree(string FileName)
//{

//}

void Books::printBookInventory() //public
{
    printBookInventory(root);
}

void Books::addBooksNode(int quantity, string title, string author, int price, string description, string review)
{
    BooksNode *tmp = root;
    BooksNode *parent = NULL;
    BooksNode *newNode = new BooksNode(quantity, title, author, price, description, review);

    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->parent = NULL;

    while(tmp != NULL)
    {
        parent = tmp;

        if (newNode->title.compare(parent->title)== 0)
        {
          tmp = tmp->rightChild;
        }
        else
        {
            if(newNode->title.compare(parent->title) < 0)
            {
              tmp = tmp->leftChild;
            }
            else
            {
                tmp = tmp->rightChild;
            }
        }
    }
     if(parent == NULL)
     {
         root = newNode;
     }
     else if(newNode->title.compare(parent->title) < 0)
     {
          parent->leftChild = newNode;
          newNode->parent = parent;
     }
    else
    {
        parent->rightChild = newNode;
        newNode->parent = parent;
    }
}
void Books::findMovie(string title)
{
    BooksNode *searched = search(title);
    if (searched != NULL) { //it is the duty of searched* to check that search worked
        cout << "Book Info:" << endl;
        cout << "===========" << endl;
        cout << "Quantity:" << searched->quantity <<endl;
        cout << "Title:" << searched->title <<endl;
        cout << "Author:" << searched->author <<endl;
        cout << "Price:" << searched->price <<endl;
        cout << "Description:" << searched->description <<endl;
        cout << "Review:" << searched->review <<endl;
    }
    else
    {
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
   if(tmp->leftChild != NULL)
    {
        printBookInventory(tmp->leftChild);

    }
    cout<< "Book: " <<tmp->title<<" "<<tmp->quantity<<endl;
    if(tmp->rightChild != NULL)
    {
        printBookInventory(tmp->rightChild);
    }
}

BooksNode* Books::search(string title)
{
    BooksNode *tmp = root;

    while(tmp != NULL)
    {
        if(tmp->title.compare(title) < 0)
        {
            tmp = tmp->rightChild;
        }
        else if(tmp->title.compare(title) > 0)
        {
            tmp = tmp->leftChild;
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
   if(node->leftChild != NULL)
    {
        countBookNodes(node->leftChild, c);
    }
    *c = *c + 1;
    if(node->rightChild != NULL)
    {
        countBookNodes(node->rightChild, c); //I'm calling a fct with two inputs and I was forgetting to add the c
    }
}

BooksNode* Books::treeMinimum(BooksNode *node)
{
    while(node->leftChild != NULL) //if the node
    {
        node = node->leftChild; //treeMinimum(node->leftChild); //this will call a recursion for this fct to find the smallest value
    }
    return node; //this should return all the information about the last node

}

void Books::deleteBooksNode(std::string title)
{
    BooksNode *node = search(title);

    if(node != NULL)
    {
        if(node != root)
        {
            if(node->leftChild == NULL && node->rightChild == NULL) //no children
            {
                if(node->parent->leftChild == node)
                {
                 node->parent->leftChild = NULL;
                }
                else if(node->parent->rightChild == node)
                {
                node->parent->rightChild = NULL;
               // delete node; it will delete at the end
                }
            }
            else if(node->leftChild != NULL and node->rightChild != NULL) //two children
            {
                BooksNode *minValue = treeMinimum(node->rightChild);//this is looking for the replacement value

                if(minValue == node->rightChild) //this is if node is the left child of its parent
                {
                    node->parent->leftChild = minValue; //if there is nothing else on the subtree but the node->rightchild
                    minValue->parent = node->parent;
                    node->leftChild->parent = minValue;//this is assigning the pointers to the correct places
                    minValue->leftChild = node->leftChild;
                }
                else
                {
                  minValue->parent->leftChild = minValue->rightChild;
                  minValue->parent = node->parent;
                  minValue->rightChild->parent = minValue->parent;
                  node->parent->leftChild = minValue;
                  minValue->leftChild = node->leftChild;
                  minValue->rightChild = node->rightChild;
                  node->rightChild->parent = minValue;
                  node->leftChild->parent = minValue;
                }
            }
            else //one child
            {
                if(node->parent->leftChild == node) //if the node is a left child
                {
                    if(node->leftChild != NULL && node->rightChild == NULL) //if the node only has one left child
                    {
                        BooksNode *x = node->leftChild;
                        node->parent->leftChild = x;   //working
                        x->parent = node->parent;
                    }
                    if(node->rightChild != NULL && node->leftChild == NULL)
                    {
                        BooksNode *x = node->rightChild;
                        node->parent->leftChild = x;
                        x->parent = node->parent;   //NOT working
                        //cout<<"HELLO"<<endl;
                    }
                }//end of node as left child
                else if(node->parent->rightChild == node) //if node is a right child
                {
                     if(node->leftChild != NULL && node->rightChild == NULL) //if the node only has one left child
                    {
                        BooksNode *y = node->leftChild;
                        node->parent->leftChild = y;            //=== this works for most
                        y->parent = node->parent;
                    }
                    if(node->rightChild != NULL && node->leftChild == NULL)
                    {
                        BooksNode *x = node->rightChild;             //=== this works for most
                        node->parent->rightChild = x;
                        x->parent = node->parent;
                    }

                } //end of node as right child
            } //end of one child
       } //end of loop where node does not equal root
    } // !- NULL
    else
    {
        cout<<"Book not found."<<endl;
    }
    delete node;
}

void Books::DeleteAll(BooksNode * node) //use this for the post-order traversal deletion of the tree - post order deletes from root to kids
{
    if(node->leftChild != NULL) //children are deleted before the root value
    {
        DeleteAll(node->leftChild);
    }
    if(node->rightChild)
    {
        DeleteAll(node->rightChild);
    }
    cout<<"Deleting: "<<node->title<<endl;
    delete node;
}



