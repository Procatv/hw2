/*rite derived product classes: 
Book, Clothing and Movie implementing the keywords() which returns the appropriate keywords to index the product, 
displayString() [to create a string that contains the product info] and dump() [that outputs the database format of the product info].
*/

#include <sstream>
#include <iomanip>
#include "Movie.h"
#include "util.h"

using namespace std;


Movie::Movie(const std::string& category, const std::string& name, double price, int qty, const std::string& genre, const::string& rating)
: Product(category, name, price, qty), genre_(genre), rating_(rating) {}

Movie::~Movie(){
   
}
/**
     * Returns the appropriate keywords that this product should be associated with
     */
     std::set<std::string> Movie::keywords() const {
        std::set<std::string> keys; 
        std::set<std::string> name = parseStringToWords(this->name_);
        std::set<std::string> category = parseStringToWords(this->category_);
        std::set<std::string> genre = parseStringToWords(this->genre_);
        std::set<std::string> rating = parseStringToWords(this->rating_);



        //so we declare two sets one from name and author and call
        //the parsekeywords in (this->name), (this_>author)
        keys.insert(name.begin(), name.end());
        keys.insert(category.begin(), category.end());
        keys.insert(genre.begin(), genre.end());
        keys.insert(rating.begin(), rating.end());

        //and then insert those keys from beginning to end in the keys
        //determine if you should add any other identifying information
        return keys;
     }
    /**
     * Returns a string to display the product info for hits of the search
     */
     std::string Movie::displayString() const{
         std::ostringstream stream;
       stream << name_ << "\n";
       stream << "Genre: " << getGenre() << " Rating: " << getRating() << "\n";
       stream << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
       return stream.str();
     }

    /**
     * Outputs the product info in the database format
     */
     void Movie::dump(std::ostream& os)const{
        os << "movie\n" << this->name_ << "\n" << std::fixed << std::setprecision(2) << this->price_ << "\n"
        << this->qty_ << "\n" << this->genre_<< "\n" << this->rating_ << std::endl;
     }

     std::string Movie::getGenre() const{
      return genre_;
     }
     std::string Movie::getRating() const{
      return rating_;
     }