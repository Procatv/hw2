#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> keywords;
    stringstream ss(rawWords);
    string word;

    //Capturing words & parsing until end
    while(getline(ss, word, ' ')){ //split via spaces

        //identifying ISBN's
        if(word.length() == 15 && word[3] == '-' && word[13] == '-'){
            keywords.insert(word);
        }
        else{
            string buffer;

            //convert to common-case
            for(size_t i = 0; i < word.length(); ++i){
                char c = word[i];
                char lower_c = tolower(static_cast<unsigned char>(c));

                //identify punctuations
                if(ispunct(c)){
                    if(buffer.length() > 1){
                        keywords.insert(buffer);
                    }
                    buffer.clear();
                }else{
                    buffer.push_back(lower_c);
                }
            }
            
            
            if(buffer.length() > 1){
                keywords.insert(buffer);
            }

        }
    }

    return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}