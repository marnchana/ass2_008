#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// coment
class Book
{
private:
    string title;
    string author;
    string isbn;
    bool available;
    string dateAdded;

public:
    void setBookDetails(string t, string a, string i, bool avail, string date)
    {
        title = t;
        author = a;
        isbn = i;
        available = avail;
        dateAdded = date;
    }

    void displayBookDetails() const
    {
        cout << "Title: " << title << endl
             << "Author: " << author << endl
             << "ISBN: " << isbn << endl
             << "Availability: " << (available ? "Available" : "Borrowed") << endl;
    }

    bool borrowBook()
    {
        if (available)
        {
            available = false;
            return true;
        }
        return false;
    }

    void returnBook()
    {
        available = true;
    }

    string getISBN() const
    {
        return isbn;
    }

    static bool compareByISBN(const Book &a, const Book &b)
    {
        return a.getISBN() < b.getISBN();
    }

    static void sortBookData(Book books[], int size)
    {
        sort(books, books + size, compareByISBN);
    }
};

int main()
{
    const int size = 5;
    Book books[size];

    books[0].setBookDetails("T1", "A1", "I00001", false, "2025-01-10");
    books[1].setBookDetails("T2", "A2", "I00002", true, "2020-03-19");
    books[2].setBookDetails("T3", "A3", "I00003", true, "2019-07-23");
    books[3].setBookDetails("T4", "A4", "I00004", true, "2010-11-03");
    books[4].setBookDetails("T5", "A5", "I00005", true, "2013-03-11");

    Book::sortBookData(books, size);

    string userISBN;
    while (true)
    {
        cout << "Enter the ISBN of the book to borrow (0 to exit): ";
        getline(cin, userISBN);

        if (userISBN == "0")
        {
            break;
        }

        bool found = false;
        for (int i = 0; i < size; ++i)
        {
            if (books[i].getISBN() == userISBN)
            {
                found = true;
                if (books[i].borrowBook())
                {
                    cout << "Book borrowed successfully!\n";
                }
                else
                {
                    cout << "Error: Book is currently unavailable.\n";
                }
                books[i].displayBookDetails();
                break;
            }
        }

        if (!found)
        {
            cout << "Error: ISBN not found in the library.\n\n";
        }
    }

    return 0;
}
