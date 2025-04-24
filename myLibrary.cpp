#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

class Book
{
protected:
    string title, author, dateAdded;
    int isbn;
    bool available;

public:
    Book() {}
    Book(string t, string a, int i, bool avail, string date)
        : title(t), author(a), isbn(i), available(avail), dateAdded(date) {}

    void displayBookDetails()
    {
        cout << "Title: " << title << endl
             << "Author: " << author << endl
             << "ISBN: " << isbn << endl
             << "Availability: " << (available ? "Available" : "Borrowed") << endl
             << "Date Added: " << dateAdded << endl;
    }

    int getISBN() { return isbn; }

    bool borrowBook()
    {
        if (available)
        {
            available = false;
            return true;
        }
        return false;
    }

    void returnBook() { available = true; }

    virtual ~Book() {}
};

class Ebook : public Book
{
private:
    string url;

public:
    Ebook(string t, string a, int i, bool avail, string date, string u)
        : Book(t, a, i, avail, date), url(u) {}

    void displayeBookDetails()
    {
        Book::displayBookDetails();
        cout << "Ebook: Yes" << endl
             << "URL: " << url << endl;
    }
};

// Utility for sorting
bool compareISBN(Book *a, Book *b)
{
    return a->getISBN() < b->getISBN();
}

// ---------- MAIN ----------

int main()
{
    const int MAX_SIZE = 10;
    Ebook *books[MAX_SIZE];
    int currentCount = 0;

    // Initial books
    books[currentCount++] = new Ebook("T1", "A1", 11111, false, "2025-01-10", "https://book1.com");
    books[currentCount++] = new Ebook("T2", "A2", 22222, true, "2020-03-19", "https://book2.com");
    books[currentCount++] = new Ebook("T3", "A3", 33333, true, "2019-07-23", "https://book3.com");
    books[currentCount++] = new Ebook("T4", "A4", 44444, true, "2010-11-03", " ");
    books[currentCount++] = new Ebook("T5", "A5", 55555, true, "2013-03-11", " ");

    int choice;
    do
    {
        cout << "\nMenu:\n"
             << "1. List all Books\n"
             << "2. Borrow a Book\n"
             << "3. Return a Book\n"
             << "4. Add a new Book\n"
             << "5. Sort Books\n"
             << "6. Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            for (int i = 0; i < currentCount; ++i)
            {
                books[i]->displayeBookDetails();
                cout << "------------------\n";
            }
            break;

        case 2:
        {
            int isbn;
            cout << "Enter ISBN to borrow: ";
            cin >> isbn;
            bool found = false;
            for (int i = 0; i < currentCount; ++i)
            {
                if (books[i]->getISBN() == isbn)
                {
                    if (books[i]->borrowBook())
                        cout << "Book borrowed successfully!\n";
                    else
                        cout << "Book is currently unavailable.\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Book not found.\n";
            break;
        }

        case 3:
        {
            int isbn;
            cout << "Enter ISBN to return: ";
            cin >> isbn;
            bool found = false;
            for (int i = 0; i < currentCount; ++i)
            {
                if (books[i]->getISBN() == isbn)
                {
                    books[i]->returnBook();
                    cout << "Book returned successfully!\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Book not found.\n";
            break;
        }

        case 4:
        {
            if (currentCount >= MAX_SIZE)
            {
                cout << "Library full.\n";
                break;
            }

            string t, a, date, url;
            int i;
            bool avail, isEbook;

            cout << "Enter Title: ";
            getline(cin, t);
            cout << "Enter Author: ";
            getline(cin, a);

            // ISBN validation
            while (true)
            {
                cout << "Enter ISBN (positive number): ";
                cin >> i;
                if (cin.fail() || i <= 0)
                {
                    cin.clear();            // clear error flag
                    cin.ignore(1000, '\n'); // discard input
                    cout << "Invalid ISBN. Please enter a positive number.\n";
                }
                else
                {
                    cin.ignore();
                    break;
                }
            }

            cout << "Is it available? (1 for yes, 0 for no): ";
            cin >> avail;
            cin.ignore();

            // Date validation
            while (true)
            {
                cout << "Enter Date (YYYY-MM-DD): ";
                getline(cin, date);
                if (date.size() != 10 || date[4] != '-' || date[7] != '-' ||
                    !isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[2]) || !isdigit(date[3]) ||
                    !isdigit(date[5]) || !isdigit(date[6]) || !isdigit(date[8]) || !isdigit(date[9]))
                {
                    cout << "Invalid date format. Please use YYYY-MM-DD.\n";
                }
                else
                {
                    break;
                }
            }

            cout << "Is it an ebook? (1 for yes, 0 for no): ";
            cin >> isEbook;
            cin.ignore();

            if (isEbook)
            {
                cout << "Enter URL: ";
                getline(cin, url);
                books[currentCount++] = new Ebook(t, a, i, avail, date, url);
            }
            else
            {
                books[currentCount++] = new Ebook(t, a, i, avail, date, "");
            }

            cout << "Book added.\n";
            break;
        }

        case 5:
            int sortChoice;
            cout << "\nSort Order Options:" << endl;
            cout << "1. Ascending" << endl;
            cout << "2. Descending" << endl;
            cout << "3. Mixed" << endl;
            cout << "Enter sort option: ";
            cin >> sortChoice;
            cin.ignore();

            if (sortChoice == 1)
            {
                sort(books, books + currentCount, [](Book *a, Book *b)
                     { return a->getISBN() < b->getISBN(); });
                cout << "\nBooks sorted in Ascending order by ISBN:\n";
            }
            else if (sortChoice == 2)
            {
                sort(books, books + currentCount, [](Book *a, Book *b)
                     { return a->getISBN() > b->getISBN(); });
                cout << "\nBooks sorted in Descending order by ISBN:\n";
            }
            else if (sortChoice == 3)
            {
                shuffle(books, books + currentCount, default_random_engine(static_cast<unsigned>(time(0))));
                cout << "\nBooks randomly shuffled:\n";
            }
            else
            {
                cout << "Invalid sort option. Returning to menu.\n";
                break;
            }

            for (int i = 0; i < currentCount; ++i)
            {
                books[i]->displayeBookDetails();
                cout << "------------------------\n";
            }
            break;

        case 6:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    // Cleanup
    for (int i = 0; i < currentCount; ++i)
    {
        delete books[i];
    }

    return 0;
}
