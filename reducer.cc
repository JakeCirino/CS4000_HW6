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

using namespace std;

int main(){
    string line;
    string old = "";
    int count = 0;
    while(!cin.eof()){
        getline(cin, line);
        if(!cin.fail()){
            //get all words
            vector<string> words;
            istringstream ss(line);
            do{
                string word;
                ss >> word;

                words.push_back(word);
            }while(ss);
            //cout << (words[2] == "\t") << endl;

            //construct word
            string word;
            for(int i = 0; i < words.size()-2; i++){
                word += words[i];
                if(i != words.size()-3)
                    word += " ";
            }

            if(old == ""){
                old = word;
            }

            if(old != word){
                cout << old << "\t" << count << endl;
                old = word;
                count = atoi(words[words.size()-2].c_str());
            }else{
                //cout << atoi(words[words.size()-1].c_str()) << endl;
                count += atoi(words[words.size()-2].c_str());
            }
        }
    }
    if(old != ""){
        cout << old << "\t" << count << endl;
    }

    return 0;
}