#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "product.h"

class Book : public Product{
    public:
     Book(const std::string& category, const std::string& name_, double price_, int qty_, const std::string& isbn_, const std::string& author_);
     ~Book();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
     std::set<std::string> keywords() const;
    /**
     * Returns a string to display the product info for hits of the search
     */
     std::string displayString() const;
     std::string getIsbn() const;
     std::string getAuthor() const;
    /**
     * Outputs the product info in the database format
     */
     void dump(std::ostream& os) const;
     private:
       std::string isbn_;
       std::string author_; 
};

#endif
