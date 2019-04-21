/*********************************
 * Filename: reducer.cc
 * Author: Jake Cirino
 * Purpose: Displays key/value pairs after sorting
 *********************************/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <set>
#include <functional>
#include <algorithm>

using namespace std;

int main(){
    map<string, int> store;
    string oldword = "";
    int count = 0;
    string line;
    while(!cin.eof()){
        getline(cin, line);

        //get word
        string word = line.substr(0, line.find("\t"));
        if(oldword == ""){
            oldword = word;
        }

        if(word == oldword){
            count++;
        }else{
            //insert old element, reset count
            store[oldword] = count;
            count = 1;

            //set oldworld to new word
            oldword = word;
        }
    }

    typedef function<bool(pair<string, int>, pair<string, int>)> Comparator;
 
	// Defining a lambda function to compare two pairs. It will compare two pairs using second field
	Comparator compFunctor =
			[](std::pair<std::string, int> elem1 ,std::pair<std::string, int> elem2)
			{
				return elem1.second < elem2.second;
			};
 
	// Declaring a set that will store the pairs using above comparision logic
	set<std::pair<string, int>, Comparator> setOfWords(
			store.begin(), store.end(), compFunctor);
 
	// Iterate over a set using range base for loop
	// It will display the items in sorted order of values
	for (std::pair<std::string, int> element : setOfWords)
		std::cout << element.first << "\t" << element.second << std::endl;

    return 0;
}