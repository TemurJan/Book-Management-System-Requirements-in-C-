#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <map>

class Authors
{
private:
    std::vector<std::string> name;
public:
    Authors(std::vector<std::string> name) :name(std::move(name)) {}

    Authors() {}

    bool operator==(const Authors& other) const
    {
        if (other.name.size() != name.size())
            return false;
        for (std::size_t i = 0; i < name.size(); ++i)
            if (name[i] != other.name[i])
                return false;
        return true;
    }

    bool operator<(const Authors& other) const
    {
        return name < other.name;
    }

    bool operator>(const Authors& other) const
    {
        return name > other.name;

    }

    bool operator<=(const Authors& other) const
    {
        return !(name > other.name);
    }

    bool operator>=(const Authors& other) const
    {
        return !(name < other.name);
    }

    void printAuthors() const
    {
        std::cout << "Authors: ";
        for (const auto& elem : name)
            std::cout << elem << ", ";
        std::cout << "\n";
    }

    std::vector<std::string> getName() const
    {
        return name;
    }
};

class Genre
{
private:
    std::vector<std::string> genre;
public:
    Genre() {}

    Genre(std::vector<std::string> genre)
        :genre(std::move(genre)) {}

    bool operator==(const Genre& other) const
    {
        if (other.genre.size() != genre.size())
            return false;
        for (std::size_t i = 0; i < genre.size(); ++i)
            if (other.genre[i] != genre[i])
                return false;
        return true;
    }

    bool operator<(const Genre& other) const
    {
        return genre < other.genre;
    }
    bool operator>(const Genre other) const
    {
        return genre > other.genre;
    }

    bool operator<=(const Genre& other) const
    {
        return genre <= other.genre;
    }

    bool operator>=(const Genre& other) const
    {
        return genre >= other.genre;
    }

    std::vector<std::string> getGenre() const
    {
        return genre;
    }

    void printGenre() const
    {
        std::cout << "Genre: ";
        for (const auto& elem : genre)
            std::cout << elem << ", ";
        std::cout << "\n";
    }

};

class Book
{
private:
    std::string title;
    std::string description;
    Genre genre;
    Authors authors;
    std::size_t year;
public:
    Book(std::string title, std::string description, Genre genre, Authors authors, std::size_t year)
        : title(std::move(title))
        , description(std::move(description))
        , genre(std::move(genre))
        , authors(std::move(authors))
        , year(year)
    {}

    void print() const
    {
        std::cout << "Title: " << title << "\n" << "Description: " << description << "\n";
        genre.printGenre();
        authors.printAuthors();
        std::cout << "Year: " << year << "\n";
        std::cout << std::endl;
    }

    bool operator==(const Book& book) const
    {
        return this->authors == book.authors &&
            this->description == book.description &&
            this->genre == book.genre &&
            this->title == book.title &&
            this->year == book.year;
    }

    bool operator<(const Book& book) const
    {
        return this->title < book.title ;
    }

    bool operator>(const Book& book) const
    {
        return book < *this;
    }

    bool operator<=(const Book& book) const
    {
        return !(book < *this);
    }

    bool operator>=(const Book& book) const
    {
        return book <= *this;
    }

    std::string getTitle()const
    {
        return title;
    }

    std::vector<std::string> getGener() const
    {
        return genre.getGenre();
    }

    std::vector<std::string> getAuthors() const
    {
        return authors.getName();
    }

    std::size_t getYear() const
    {
        return year;
    }
     
    bool empty() const
    {
        return genre.getGenre().size() == 0;
    }
};

class Library
{
private:
    std::vector<Book> library;

    bool equal(const std::vector<std::string>& rhs, const std::vector<std::string>& lhs)
    {
        if (rhs.size() and rhs.size() != lhs.size())
            return false;
        
        for (int i = 0; i < rhs.size(); ++i)
            if (rhs[i] != lhs[i])
                return false;
            return true;
    }

    bool check(const Book& rhs, const Book& lhs)
    {
        if (rhs.getTitle() == lhs.getTitle() && equal(rhs.getGener(), lhs.getGener()) &&
            equal(rhs.getAuthors(), lhs.getAuthors()) && rhs.getYear() == lhs.getYear())
            return true;
    }

public:
    Library(std::vector<Book> library)
        : library(std::move(library))
    {}

    Library() {}

    void toAdd(const Book& book)
    {
        for (const auto& elem : library)
            if (check(elem,book))
                return;

        library.push_back(book);
    }

    void toRemove(const Book& book)
    {
        std::size_t index = library.size();
        for (std::size_t i = 0; i < library.size(); ++i)
        {
            if (check(library[i], book))
            {
                index = i;
                break;
            }
        }
        if (index == library.size())
            return;
        library.erase(library.begin() + index, library.begin() + index + 1);
    }
    
    void toShow()
    {
        for (const auto& elem : library)
            elem.print();
    }
};

class User
{
private:
    std::string name;
    std::string email;
    std::string password;
    bool isAdmin;
    std::vector<Book> favorites;
public:
    User(std::string name, std::string email, std::string password, bool isAdmin = false)
    {
        this->name = name;
        while (password.size() < 6)
        {
            std::cout << "Dear " + name + " your password is unvalide... Try again\n";
            std::cin >> password;
        }
        this->password = password;
        this->isAdmin = isAdmin;
        std::string temp = email;
        std::reverse(temp.begin(), temp.end());
        
        while(std::string(temp.begin(), temp.begin() + 10) != "moc.liamg@" &&
            std::string(temp.begin(), temp.begin() + 9) != "ma.liamg@" &&
            std::string(temp.begin(), temp.begin() + 9) != "ur.liamg@")
        {
            std::cout <<"Dear " + name + " your email is wronge... Try again\n";
            std::string new_email;
            std::cin >> new_email;
            temp = new_email;
            std::reverse(temp.begin(), temp.end());
        }
        std::reverse(temp.begin(), temp.end());
        this->email = temp;
    }

    std::string getName() const
    {
        return name;
    }
    std::string getEmail() const
    {
        return email;
    }

    bool ckechPassworkd(const std::string& pass) const
    {
        return pass == password;
    }

    bool isAdministrator() const 
    { 
        return isAdmin; 
    }
    
    void toAddFavoritesBook(const Book& other)
    {
        if (std::find(favorites.begin(), favorites.end(), other) == favorites.end())
            favorites.push_back(other);
    }

    void toRemoveFavoritesBook(const Book& other)
    {
        std::size_t index = favorites.size();
        for (std::size_t i = 0; i < favorites.size(); ++i)
        {
            if (favorites[i] == other)
            {
                index = i;
                break;
            }
        }
        favorites.erase(favorites.begin() + index, favorites.begin() + index + 1);
    }

    void print()const
    {
        std::cout << "Name: " << name << "\n" << "Email: " << email << "\n";
    }

    void listOfFavoritesBook()
    {
        for (const auto& elem : favorites)
            elem.print();
        std::cout << "\n";
    }

    std::vector<Book> getFavorites() const
    {
        return favorites;
    }

};

class BookManagementSystem
{
private:
    std::map<std::string, User> users;
public:
    BookManagementSystem() {}

    void toRegisterUser(const std::string& name, const std::string& email, const std::string& password, bool isAdmin = false)
    {
        if (users.find(email) == users.end())
        {
            users[email] = User(name, email, password, isAdmin);
            std::cout << "User registered successfully." << std::endl;
        }
        else {
            std::cout << "Email already registered." << std::endl;
        }
    }


};

int main()
{
    Book obj1("To Kill a Mockingbird", "This novel is set in the Depression-era South and follows young Scout Finch and her brother, Jem, as their father, lawyer Atticus Finch, defends a black man accused of raping a white woman. It addresses themes of racial injustice, moral growth, and compassion.", Genre({ "Fiction", "Classic", "Historical" }), Authors({ "Harper Lee" }), 1960);
    Book obj2("To Kill a Mockingbird", "This novel is set in the Depression-era South and follows young Scout Finch and her brother, Jem, as their father, lawyer Atticus Finch, defends a black man accused of raping a white woman. It addresses themes of racial injustice, moral growth, and compassion.", Genre({ "Fiction", "Classic", "Historical" }), Authors({ "Harper Lee" }), 1968);
    Book obj3("1984", "A dystopian novel that explores the dangers of totalitarianism. It is set in a world of perpetual war, pervasive government surveillance, and incessant public mind control, dictated by a political regime under the control of the Party and its emblem, Big Brother.", Genre({ " Fiction", "Dystopian", "Science Fiction" }), Authors({ " George Orwell" }), 1949);
    Book obj4(" Pride and Prejudice", "This classic novel of manners explores the issues of marriage, money, and love among the British gentry of the early 19th century. It focuses on the relationship between Elizabeth Bennet and Mr. Darcy.", Genre({ "Fiction", "Romance", "Classic" }), Authors({ "Jane Austen" }), 1813);
    Book obj5("Moby - Dick", "The novel follows the adventures of the wandering sailor Ishmael and his voyage on the whaling ship Pequod, commanded by Captain Ahab.Ahab is obsessed with revenge against Moby Dick, the giant white sperm whale that on the ship's previous voyage destroyed Ahab's ship and severed his leg at the knee.", Genre({ "Fiction", "Adventure", "Classic" }), Authors({ "Herman Melville" }), 1234);

    User user("Mika", "mikajan@gmail.com", "mika789");
    user.toAddFavoritesBook(obj1);
    user.toAddFavoritesBook(obj2);
    user.toAddFavoritesBook(obj3);
    user.toAddFavoritesBook(obj4);
    user.listOfFavoritesBook();
    user.toRemoveFavoritesBook(obj2);
    user.listOfFavoritesBook();
    /*
    Book obj1("To Kill a Mockingbird" , "This novel is set in the Depression-era South and follows young Scout Finch and her brother, Jem, as their father, lawyer Atticus Finch, defends a black man accused of raping a white woman. It addresses themes of racial injustice, moral growth, and compassion.",Genre( { "Fiction", "Classic", "Historical" }), Authors({ "Harper Lee" }), 1960);
    Book obj2("To Kill a Mockingbird" , "This novel is set in the Depression-era South and follows young Scout Finch and her brother, Jem, as their father, lawyer Atticus Finch, defends a black man accused of raping a white woman. It addresses themes of racial injustice, moral growth, and compassion.",Genre( { "Fiction", "Classic", "Historical" }), Authors({ "Harper Lee" }), 1968);
    Book obj3("1984" , "A dystopian novel that explores the dangers of totalitarianism. It is set in a world of perpetual war, pervasive government surveillance, and incessant public mind control, dictated by a political regime under the control of the Party and its emblem, Big Brother.",Genre( { " Fiction", "Dystopian", "Science Fiction" }),Authors( { " George Orwell" }), 1949);
    Book obj4(" Pride and Prejudice" , "This classic novel of manners explores the issues of marriage, money, and love among the British gentry of the early 19th century. It focuses on the relationship between Elizabeth Bennet and Mr. Darcy.",Genre( { "Fiction", "Romance", "Classic" }), Authors({ "Jane Austen" }), 1813);
    Book obj5("Moby - Dick" , "The novel follows the adventures of the wandering sailor Ishmael and his voyage on the whaling ship Pequod, commanded by Captain Ahab.Ahab is obsessed with revenge against Moby Dick, the giant white sperm whale that on the ship's previous voyage destroyed Ahab's ship and severed his leg at the knee.", Genre({ "Fiction", "Adventure", "Classic" }),Authors( { "Herman Melville" }), 1234);
       

    Library lib;
    lib.toAdd(obj1);
    lib.toAdd(obj2);
    lib.toAdd(obj3);
    lib.toAdd(obj4);
    lib.toRemove(obj2);
    lib.toShow();*/
}
