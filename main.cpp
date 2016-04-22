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
    ifstream inFile;
    //inFile.open(argv[1]);
    inFile.open("booksList.txt");
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

            libros.addBooksNode(quantity,title,author,price,description,review);

        }
    }

    string menu;
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Find a book"<<endl;
    cout<<"2. Buy a book"<<endl;
    cout<<"3. Print the inventory"<<endl;
    cout<<"4. Delete a book"<<endl;
    cout<<"5. Count the books"<<endl;
    cout<<"6. Quit"<<endl;
    getline(cin, menu);



while (menu != "6")
{
    if(menu == "1")
    {
        cout<<"Enter title:"<<endl;
        string found;
        getline(cin, found);
        libros.findMovie(found);
    }

    if(menu == "2")
    {
        cout<<"Enter title:"<<endl;
        string rent;
        getline(cin, rent);
        libros.buyBooks(rent);

    }

    if(menu == "3") //print movie
    {
        libros.printBookInventory();
    }

    if(menu == "4") //delete node
    {
        cout<<"Enter title:"<<endl;
        string deleted;
        getline(cin, deleted);
        libros.deleteBooksNode(deleted);
    }

    if(menu == "5")//count movies
    {
     int c;
     c = libros.countBooksNodes();
      cout<<"Tree contains: "<<c<<" books."<<endl;
    }

    cout<<"======Main Menu======"<<endl;
    cout<<"1. Find a book"<<endl;
    cout<<"2. Buy a book"<<endl;
    cout<<"3. Print the inventory"<<endl;
    cout<<"4. Delete a book"<<endl;
    cout<<"5. Count the books"<<endl;
    cout<<"6. Quit"<<endl;
    getline(cin, menu);

} //end of while
    cout<<"Goodbye!"<<endl;
    return 0;
}

