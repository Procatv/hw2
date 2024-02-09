#include "mydatastore.h"
#include "fstream"

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
    std::set<Product*> deletedProducts;

    for(std::map<std::string, User*>::iterator it = users.begin(); it != users.end(); ++it){
        delete it->second;
    }
    for(std::map<std::string, std::set<Product*>>::iterator it = products.begin(); it != products.end(); ++it){
        for(std::set<Product*>::iterator prodIt = it->second.begin(); prodIt != it->second.end(); ++prodIt){
            if(deletedProducts.find(*prodIt) == deletedProducts.end()){
                delete *prodIt;
                deletedProducts.insert(*prodIt);
            }
        }
    }
    
}

void MyDataStore::addProduct(Product *p){
    std::set<std::string> keywords = p->keywords();
    for(std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it){
        products[*it].insert(p);
    }

}

void MyDataStore::addUser(User* u){
    users[convToLower(u->getName())] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    std::set<Product*> results;
    if(terms.empty()) return std::vector<Product*>(results.begin(), results.end());

    if(type == 0){
        std::set<Product*> tempResult = products[terms[0]];
        for(size_t i =1; i <terms.size(); ++i){
            if(products.find(terms[i]) != products.end()){
                tempResult = setIntersection(tempResult, products[terms[i]]);
            }
        }
        results = tempResult;
    }
    else if(type == 1){
        for(std::vector<std::string>::iterator termIt = terms.begin(); termIt != terms.end(); ++termIt){
            if(products.find(*termIt) != products.end()){
                results = setUnion(results, products[*termIt]);
            }
        }
    }

   hits = std::vector<Product*>(results.begin(), results.end());
    return hits;

}

void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>\n";
    std::set<Product*> dumpedProducts;

    for(std::map<std::string, std::set<Product*>>::iterator it = products.begin(); it != products.end(); ++it){
        for(std::set<Product*>::iterator prodIt = it->second.begin(); prodIt != it->second.end(); ++prodIt){
            if(dumpedProducts.find(*prodIt) == dumpedProducts.end()){
                (*prodIt)->dump(ofile);
                dumpedProducts.insert(*prodIt);
            }
        }
    }
    ofile << "</products>\n";
    ofile << "<users>\n";
    for(std::map<std::string, User*>::iterator userIt = users.begin(); userIt != users.end(); ++userIt){
        userIt->second->dump(ofile);
    }
    ofile << "</users>\n";
}

void MyDataStore::buyCart(const std::string& username){
    std::string username_lower = convToLower(username);
    std::map<std::string, User*>::iterator userIt = users.find(username_lower);
    if(userIt == users.end()){
        std::cout << "Invalid username" << std::endl;
        return;
    }

    User* user = userIt->second;
    std::map<std::string, std::vector<Product*>>::iterator cartIt = userCarts.find(username_lower);
    if(cartIt != userCarts.end()){
        std::vector<Product*>& cart = cartIt->second;
        for(std::vector<Product*>::iterator it = cart.begin(); it != cart.end();){
            Product* p = *it;
            if(((p->getQty() > 0)) && (user->getBalance() >= p->getPrice())){
                p->subtractQty(1);
                user->deductAmount(p->getPrice());
                it = cart.erase(it);
            }
            else{
                ++it;
            }
        }
    }
    else{
       std::cout <<"User has no cart" << std::endl;
    }
}

void MyDataStore::addToCart(const std::string& username, int hit_results_index){
    std::string username_lower = convToLower(username);

    if(users.find(username_lower) == users.end()){
        std::cout << "Invalid request" << std::endl;
        return;
    }

    if(hit_results_index < 0 || hit_results_index >= static_cast<int>(hits.size())){
        std::cout << "Invalid hit number" << std::endl;
        return;
    }

    Product* selectedProduct = hits[hit_results_index];
    userCarts[username].push_back(selectedProduct);
}

std::vector<Product*> MyDataStore::getUserCart(const std::string& username) {
    std::string username_lower = convToLower(username);
    std::map<std::string, std::vector<Product*>>::iterator it = userCarts.find(username_lower);
    if (it != userCarts.end()) {
        // User found, return their cart
        return it->second;
    } else {
        // User not found, return an empty vector
        return std::vector<Product*>();
    }
}

void MyDataStore::viewCart(const std::string& username){
    std::string username_lower = convToLower(username);

    if(users.find(username_lower) == users.end()){
        std::cout << "Invalid username" << std::endl;
        return;
    }

    std::vector<Product*> &cart = userCarts[username_lower];

    for(size_t i =0; i < cart.size(); ++i){
        Product* product = cart[i];
        std::cout << "Item " << (i +1) << std::endl;
        std::cout << product->displayString() << std::endl;

    }
}

bool MyDataStore::isUserValid(const std::string& username){
    std::string username_lower = convToLower(username);
    return users.find(username_lower) != users.end();
}