#include <iostream>
#include <cstring>
#include <limits>

namespace LibrarySystem
{
    class Book
    {
    private:
        char *title;
        int pages;

    public:
        Book(const char *t = nullptr, int p = 0);

        Book(const Book &other);

        Book &operator=(const Book &other);

        virtual ~Book();

        virtual void readData();

        virtual void displayData() const;
    };

    class EBook : public Book
    {
    private:
        double fileSizeMB;
        char *format;

    public:
        EBook(const char *t = nullptr, int p = 0, double size = 0.0, const char *f = nullptr);

        EBook(const EBook &other);

        EBook &operator=(const EBook &other);

        ~EBook() override;

        void readData() override;

        void displayData() const override;
    };

    Book::Book(const char *t, int p) : pages(p)
    {
        if (t != nullptr)
        {
            title = new char[strlen(t) + 1];
            strcpy(title, t);
        }
        else
        {
            title = new char[1];
            title[0] = '\0';
        }
    }

    Book::Book(const Book &other) : pages(other.pages)
    {
        title = new char[strlen(other.title) + 1];
        strcpy(title, other.title);
    }

    Book &Book::operator=(const Book &other)
    {
        if (this != &other)
        {
            delete[] title;
            pages = other.pages;
            title = new char[strlen(other.title) + 1];
            strcpy(title, other.title);
        }
        return *this;
    }

    Book::~Book()
    {
        delete[] title;
    }

    void Book::readData()
    {
        char tempTitle[256];
        std::cout << "Enter Book Title: ";

        if (std::cin.peek() == '\n')
            std::cin.ignore();
        std::cin.getline(tempTitle, 256);

        delete[] title;
        title = new char[strlen(tempTitle) + 1];
        strcpy(title, tempTitle);

        std::cout << "Enter Number of Pages: ";
        std::cin >> pages;
    }

    void Book::displayData() const
    {
        std::cout << "Title: " << (title && title[0] != '\0' ? title : "Unknown") << "\n"
                  << "Pages: " << pages << "\n";
    }

    EBook::EBook(const char *t, int p, double size, const char *f)
        : Book(t, p), fileSizeMB(size)
    {
        if (f != nullptr)
        {
            format = new char[strlen(f) + 1];
            strcpy(format, f);
        }
        else
        {
            format = new char[1];
            format[0] = '\0';
        }
    }

    EBook::EBook(const EBook &other)
        : Book(other), fileSizeMB(other.fileSizeMB)
    {
        format = new char[strlen(other.format) + 1];
        strcpy(format, other.format);
    }

    EBook &EBook::operator=(const EBook &other)
    {
        if (this != &other)
        {
            Book::operator=(other);
            delete[] format;
            fileSizeMB = other.fileSizeMB;
            format = new char[strlen(other.format) + 1];
            strcpy(format, other.format);
        }
        return *this;
    }

    EBook::~EBook()
    {
        delete[] format;
    }

    void EBook::readData()
    {
        Book::readData();

        std::cout << "Enter File Size (in MB): ";
        std::cin >> fileSizeMB;

        char tempFormat[64];
        std::cout << "Enter Format (e.g., PDF, TXT, EPUB, MOBI): ";
        std::cin >> tempFormat;

        delete[] format;
        format = new char[strlen(tempFormat) + 1];
        strcpy(format, tempFormat);
    }

    void EBook::displayData() const
    {
        Book::displayData();
        std::cout << "File Size: " << fileSizeMB << " MB\n"
                  << "Format: " << (format && format[0] != '\0' ? format : "Unknown") << "\n";
    }

}

using namespace LibrarySystem;

int main()
{
    std::cout << "=== Demonstrating Parameterized Constructor ===\n";
    EBook book1("C++ Programming Paradigms", 450, 15.5, "PDF");
    book1.displayData();

    std::cout << "\n=== Demonstrating Copy Constructor ===\n";
    EBook book2 = book1;
    book2.displayData();

    std::cout << "\n=== Demonstrating Default Constructor & readData() ===\n";
    EBook book3;
    book3.readData();

    std::cout << "\n=== Demonstrating Assignment Operator ===\n";
    std::cout << "Assigning Book 3's data over to Book 1...\n";
    book1 = book3;

    std::cout << "\nUpdated Book 1 Details:\n";
    book1.displayData();

    return 0;
}