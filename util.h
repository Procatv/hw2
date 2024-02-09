#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
//These functions will help you later to performing search
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
//And OR search is defined as all products that contain
//ANY of the search terms entered

//results set
std::set<T> result;
 
//Compare & store
const std::set<T>& smallerSet = s1.size() <= s2.size() ? s1 : s2;
const std::set<T>& largerSet = s1.size() > s2.size() ? s1 : s2;


//Iterate throught both sets independently
    //Smallest set - iterating 
    //Largest set - iterating and comparing
for(typename std::set<T>::iterator it = smallerSet.begin(); it != smallerSet.end(); ++it){
    if(largerSet.find(*it) != largerSet.end()){
        result.insert(*it);
    }
} 
return result;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
//An AND search should return all the products that contain ALL the
//search terms entered

std::set<T> result;

for(typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it){
    result.insert(*it);
}

for(typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it){
    result.insert(*it);
}

return result;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
