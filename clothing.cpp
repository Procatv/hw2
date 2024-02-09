/*rite derived product classes: 
Book, Clothing and Movie implementing the keywords() which returns the appropriate keywords to index the product, 
displayString() [to create a string that contains the product info] and dump() [that outputs the database format of the product info].
*/

#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string& category, const std::string& name, double price, int qty, const std::string& size, const::string& brand) 
: Product(category, name, price, qty), size_(size), brand_(brand) {}

Clothing::~Clothing(){
   
}
/**
     * Returns the appropriate keywords that this product should be associated with
     */

    //clarify how ISBN is supposed to be captured???
     std::set<std::string> Clothing::keywords() const {
        std::set<std::string> keys; 
        std::set<std::string> clothing_name = parseStringToWords(this->name_);
        std::set<std::string> category = parseStringToWords(this->category_);
        std::set<std::string> size = parseStringToWords(this->size_);
        std::set<std::string> brand = parseStringToWords(this->brand_);



        //so we declare two sets one from name and author and call
        //the parsekeywords in (this->name), (this_>author)
        keys.insert(clothing_name.begin(), clothing_name.end());
        keys.insert(category.begin(), category.end());
        keys.insert(size.begin(), size.end());
        keys.insert(brand.begin(), brand.end());


        //keys.insert(quantity.begin(), quantity.end());

        //and then insert those keys from beginning to end in the keys
        //determine if you should add any other identifying information
        return keys;
     }
    /**
     * Returns a string to display the product info for hits of the search
     */
     std::string Clothing::displayString() const {
       std::ostringstream stream;
       stream << std::fixed << std::setprecision(2); // To ensure the price is formatted correctly
      stream << getName() << "\n"
           << "Size: " << getSize() << " Brand: " << getBrand() << "\n"
           << getPrice() << " " << getQty() << " left.";
       return stream.str();
        
     }

    /**
     * Outputs the product info in the database format
     */
     void Clothing::dump(std::ostream& os) const {
        os << "clothing\n" << this->name_ << "\n" << std::fixed << std::setprecision(2) << this->price_ << "\n"
        << this->qty_ << "\n" << this->size_ << "\n" << this->brand_ << std::endl;
     }
     
     std::string Clothing::getSize() const{
      return size_;
     }

     std::string Clothing::getBrand() const{
      return brand_;
     }