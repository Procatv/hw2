#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include <map>
#include <iostream>

class MyDataStore : public DataStore {
    public:
        MyDataStore();
        virtual ~MyDataStore();

        void addProduct(Product* p);
        void addUser(User* u);
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        void dump(std::ostream& ofile);
        void addToCart(const std::string& username, int hitNumber);
        void viewCart(const std::string& username);
        std::vector<Product*> getUserCart(const std::string& username);
        void buyCart(const std::string& username);
        void saveToFile(const std::string& filename);
        bool isUserValid(const std::string& username);

        private:
        std::map<std::string, std::set<Product*>> products;
        std::map<std::string, User*> users;
        std::map<std::string, std::vector<Product*>> userCarts;
        std::vector<Product*> hits;


};

#endif