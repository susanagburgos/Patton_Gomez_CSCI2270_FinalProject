///Susana and Maggie Final Project
#include <iostream>
#include "Books.h"
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
    cout<<"Welcome to Agora Bookstore!"<<endl;
    cout<<endl;
    Books libros;
    libros.createBookTree(libros,"bookList.txt");
    bool quit = false;
    while (!quit)
    {
        string menu;
        cout<<"====== Agora ======"<<endl;
        cout<<"1. Find a book"<<endl;
        cout<<"2. View our inventory"<<endl;
        cout<<"3. Add a book to cart"<<endl;
        cout<<"4. Remove a book from cart"<<endl;
        cout<<"5. View cart"<<endl;
        cout<<"6. Add a book rating"<<endl;
        cout<<"7. Checkout"<<endl;
        cout<<"8. Quit"<<endl;
        getline(cin, menu);
        if(menu == "1")///FIND A BOOK
        {
            cout<<"Enter title:"<<endl;
            string found;
            getline(cin, found);
            libros.findBook(found);
        }
        else if(menu == "2")///VIEW INVENTORY
        {
            int c;
            c = libros.countBooksNodes();
            cout<<"Library contains "<<c<<" titles to choose from."<<endl;
            cout<<"============================"<<endl;
            libros.printBookInventory();
        }
        else if(menu == "3")///ADD BOOK
        {
            cout<<"Enter title:"<<endl;
            string bookname;
            getline(cin, bookname);
            libros.addBook(bookname);
        }
        else if(menu == "4") ///REMOVE BOOK
        {
            cout<<"Enter title:"<<endl;
            string deleted;
            getline(cin, deleted);
            libros.deleteCartNode(deleted);

        }
        else if(menu == "5") ///VIEW CART
        {
            libros.viewCart();
        }
        else if(menu == "6")///BOOK RATING
        {
            cout<<"Enter title:"<<endl;
            string rater;
            getline(cin, rater);
            libros.insertRating(rater);
        }
        else if(menu == "7")///CHECKOUT
        {
            libros.checkout();
        }
        else
        {
            quit = true;
        }
    }
cout<<"Goodbye!"<<endl;
return 0;
}
