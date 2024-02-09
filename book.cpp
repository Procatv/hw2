#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"


using namespace std;



Book::Book(const std::string& category, const std::string& name, double price, int qty, const std::string& isbn, const::string& author)
: Product(category, name, price, qty), isbn_(isbn), author_(author) {}

Book::~Book(){
   
}


/**
     * Returns the appropriate keywords that this product should be associated with
     */
    //A product should match a keyword if it appears in the product name or one of the following attributes below
    //Books: authors name, and ISBN
     std::set<std::string> Book::keywords() const {
        //Name (Book)
        //Price
        //Quanity of Stock
        //ISBN
        //Author

       std::set<std::string> keys; 
        std::set<std::string> book_name = parseStringToWords(this->name_);
        std::set<std::string> category = parseStringToWords(this->category_);
        std::set<std::string> isbn = parseStringToWords(this->isbn_);
        std::set<std::string> author = parseStringToWords(this->author_);



        //so we declare two sets one from name and author and call
        //the parsekeywords in (this->name), (this_>author)
        keys.insert(book_name.begin(), book_name.end());
        keys.insert(category.begin(), category.end());
        keys.insert(isbn.begin(), isbn.end());
        keys.insert(author.begin(), author.end());

        //and then insert those keys from beginning to end in the keys
        //determine if you should add any other identifying information
        return keys;
     }

    /*
     * Returns a string to display the product info for hits of the search
     */
     std::string Book::displayString() const{
         std::ostringstream stream;
       stream << name_ << "\n";
       stream << "Author: " << getAuthor() << " ISBN: " << getIsbn() << "\n";
       stream << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
       return stream.str();
        }

    /**
     * Outputs the product info in the database format
     */
     void Book::dump(std::ostream& os)const{
        os << "book\n" << this->name_ << "\n" << std::fixed << std::setprecision(2) << this->price_ << "\n"
        << this->qty_ << "\n" << this->isbn_ << "\n" << this->author_ << std::endl;

     }

     std::string Book::getIsbn() const{
      return isbn_;
     }
     std::string Book::getAuthor() const{
      return author_;

     }