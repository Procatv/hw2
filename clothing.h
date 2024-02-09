#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "product.h"

class Clothing : public Product{
    public:
     Clothing(const std::string& category, const std::string& name_, double price_, int qty_, const std::string& size_, const std::string& brand_);
     ~Clothing();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
     std::set<std::string> keywords() const;
    /**
     * Returns a string to display the product info for hits of the search
     */
     std::string displayString() const;
     std::string getSize() const;
     std::string getBrand() const;
    /**
     * Outputs the product info in the database format
     */
     void dump(std::ostream& os) const;
    private:
    std::string size_;
    std::string brand_;
};

#endif