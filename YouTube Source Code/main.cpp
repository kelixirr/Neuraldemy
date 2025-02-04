#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <algorithm>

class Book {

private:
  string title;
  string author;
  int year;
  bool status;

public:
   Book(const string& title, const string& author, int year, bool status = false)
        : title(title), author(author), year(year), status(status) {}

    void setTitle(const string& title) { this->title = title; }
    void setAuthor(const string& author) { this->author = author; }
    void setYear(int year) { this->year = year; }

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }

    bool isBorrowed() const { return status; }
    void borrow() { status = true; }
    void returnBook() { status = false; }
}; 

class User {

protected: 
  string name;
  int userId;
  vector<Book> borrowedBooks;

public:
  User(string name, int userId): name(name), userId(userId) {}
  
  int getId() const { return userId; }

  void myBooks() const {
  for (const auto &book: borrowedBooks){
    cout << book.getTitle() << endl;
  }}

  void returnBook(Book &bookToReturn) {
    borrowedBooks.erase(remove_if(borrowedBooks.begin(), borrowedBooks.end(),
        [&](const Book &book) { return book.getTitle() == bookToReturn.getTitle(); }),
        borrowedBooks.end());
}
};

class Student: public User {

public:
Student(string name, int userId) : User(name, userId){}

bool borrowBook(const Book &book){
  if (borrowedBooks.size() < 3) {
    borrowedBooks.push_back(book);
    return true;
  }
  cout << "Students can't borrow more than 3 books" << endl;
  return false;
}
};

class Staff: public User {

public:
Staff(string name, int userId) : User(name, userId){}

bool borrowBook(const Book &book){
  borrowedBooks.push_back(book);
  return true;
}
};

class Library {

private:
  vector<Book> books;
  vector<Staff> staffs;
  vector<Student> students;

public:
  void addBook(string title, string author, int year){
     books.push_back(Book(title, author, year));
  }

  void removeBook(string title) {
    for (auto it = books.begin(); it != books.end(); ++it){
      if (it->getTitle() == title){
        books.erase(it);
        break;
      }
    }
  }
   

 void addStudent(string name, int id) {
    students.push_back(Student(name, id));
}

void addStaff(string name, int id) {
    staffs.push_back(Staff(name, id));
}
  
  void listAvailableBooks() const {
        for (const Book& book : books) {
            if (!book.isBorrowed()) {
                cout << book.getTitle() << " by " << book.getAuthor() << " (" << book.getYear() << ")" << endl;
            }
        }
    }
  
  bool borrowBook(string title, int userId, string type = "student") {
    for(Book &book: books){
      if (book.getTitle() == title && !book.isBorrowed()){
        cout << "Book is available and permission granted";
        updateDetails(userId, book, type, "borrow");
        book.borrow();
        return true;
      } 
    }
    cout << "Book is unavailable." << endl;
    return false;
  }

   bool returnBook(string title, int userId, string type = "student") {
    for(Book &book: books){
      if (book.getTitle() == title && book.isBorrowed()){
        cout << "Thank you for returning the book";
         updateDetails(userId, book, type, "return");
         book.returnBook();
        return true;
      }
    }
    cout << "This book was not borrowed" << endl;
    return false;
  }

   void updateDetails(int userId, Book &book, string type, string action) {
    
    if (action == "borrow") {  
        if (type == "student") {
            for (auto &student : students) {  
                if (student.getId() == userId) {
                    student.borrowBook(book);
                    return;
                }
            }
            cout << "Student ID not found!" << endl;  
        }

        if (type == "staff") { 
            for (auto &staff : staffs) {
                if (staff.getId() == userId) {
                    staff.borrowBook(book);
                    return;
                }
            }
            cout << "Staff ID not found!" << endl;  
        }
    }

    if (action == "return") {  
        if (type == "student") {
            for (auto &student : students) {  
                if (student.getId() == userId) {
                    student.returnBook(book);
                    return;
                }
            }
            cout << "Student ID not found!" << endl;  
        }

        if (type == "staff") { 
            for (auto &staff : staffs) {
                if (staff.getId() == userId) {
                    staff.returnBook(book);
                    return;
                }
            }
            cout << "Staff ID not found!" << endl; 
        }
    }
  }
   
};


int main() {
  Library lib;
  lib.addBook("C++ Primer", "Stanley Lippman", 2012);
  lib.addBook("The Pragmatic Programmer", "Andrew Hunt", 1999);

  cout << "Available Books:\n";
  lib.listAvailableBooks();
  
  lib.addStudent("John Doe", 101);
  lib.borrowBook("C++ Primer", 101, "student"); 
  cout << "\nAfter Borrowing:\n";
  lib.listAvailableBooks();

  return 0;
}


