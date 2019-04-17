/*********************************
 * Filename: mapper.cc
 * Author: Jake Cirino
 * Purpose: Pairs elements for an n-gram
 *********************************/
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Gets the next tweet starting at index start
 */
string get_next_tweet(istream& in){
    //get positions
    int count = 0, state = 0;
    char word[256];
    int word_index = 0;
    while(count < 29){
        //get next char
        int next;
        if((next = in.get()) == in.eof() || next == -1)
            return "";

        //add to word array if we're in tweet text area
        if(count == 11)
            word[word_index++] = next;

        //check for csv bounds
        switch(state){
            case 0:
                if(next == '"')
                    state = 1;
                else
                    state = 0;
            break;
            case 1:
                if(next == ',')
                    state = 2;
                else
                    state = 0;
            break;
            case 2:
                if(next == '"'){
                    state = 0;
                    count++;
                }else
                    state = 0;
            break;
        }
    }

    //remove last 3 indicies
    word[--word_index] = 0;
    word[--word_index] = 0;
    word[--word_index] = 0;

    string str = word;

    //remove doublequotes
    size_t start_pos = 0;
    while((start_pos = str.find("\"\"", start_pos)) != string::npos){
        str.replace(start_pos, 2, "\"");
        start_pos += 1;
    }
    return str;
}

void map_string(string& src, int gramCount){
    istringstream ss(src);
    vector<string> words;
    
    //go through words
    do{
        string word;
        ss >> word;

        words.push_back(word);
    }while(ss);

    //loop for each starting word
    for(int i = 0; i < words.size() - gramCount - 1; i++){
        string s;
        //loop to add all words
        for(int j = 0; j < gramCount; j++){
            s += words[i+j];
        }
        cout << s << "\t1" << endl;
    }
}

int main(int argc, char *argv[]){
    //get parameters
    int gramCount = 1;
    if(argc > 1)
        gramCount = atoi(argv[1]);

    string str;
    while((str = get_next_tweet(cin)) != ""){
        map_string(str, gramCount);
        //cout << str << endl;
    }

    return 0;
}