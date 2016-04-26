///susana and maggie final project
#include <iostream>
#include "Books.h"
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//int main(int argc, char* argv[])
int main()
{
    Books libros;
    libros.createBookTree(libros,"booksList.txt");
    bool quit = false;


while (!quit)
{
    string menu;
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Find a book"<<endl;
    cout<<"2. View our Inventory"<<endl;
    cout<<"3. Add a Book to Cart"<<endl;
    cout<<"4. Remove a Book from Cart"<<endl;
    cout<<"5. View Cart"<<endl;
    cout<<"6. Add a Book Review"<<endl;
    cout<<"7. Checkout"<<endl;
    cout<<"8. Quit"<<endl;
    getline(cin, menu);

    if(menu == "1")
    {
        cout<<"Enter title:"<<endl;
        string found;
        getline(cin, found);
        libros.findMovie(found);
    }

    else if(menu == "2")
    {

        libros.printBookInventory();

    }

    else if(menu == "3") //print movie
    {
        cout<<"Enter title to add:"<<endl;
        string name;
        getline(cin, name);
        libros.addBook(name);
    }
    else if(menu == "4") //delete node
    {
        cout<<"Enter title:"<<endl;
        string deleteCart;
        getline(cin, deleteCart);
        libros.cartDelete(deleteCart);
    }
    else if(menu == "5")//count movies
    {
        libros.viewCart();
    }
    else if(menu == "6")
    {
        //add a review
    }
    else if(menu == "7")
    {
        //checkout
    }
    else
    {
        quit = true;
    }
} //end of while
    cout<<"Goodbye!"<<endl;
    return 0;
}

