//
//  main.cpp
//  GA-Assembly-Exercise-Jorge
//
//  Created by Jorge Davila on 10/31/12.
//  Copyright (c) 2012 Jorge Davila. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "AVLTree.h"

using namespace std;

void compute( vector<int>&, string );
void parse( ifstream&,string, vector<int>&, vector<string>, vector<string> , vector<string>, AvlTree& );
void commonThreeWordPhrase( string, vector<string>&, vector<string>&, vector<string>&, AvlTree& );
void viewCommonThreeWordPhrases( AvlTree& );

int main(int argc, const char * argv[])
{
    string search; 
    ifstream file;
    vector<int> numOfWordsBetweenKeywords;
    vector<string> arr1;
    vector<string> arr2;
    vector<string> arr3;
    AvlTree tree;
    
    if (argc != 2){
        cout << "You did not enter a file. (i.e  ./exe text.txt) \n";
        cout << "The program will terminate, please try again. \n";
        return 0;
    }
    
    
    file.open(argv[1]);
    if (file.is_open()!= true){
        cerr << "Couldn't open file" << endl;
        return 0;
    }
    cout << "What word would you like to search? ";
    cin >> search;
    
    parse( file, search,numOfWordsBetweenKeywords, arr1, arr2, arr3, tree );
    compute( numOfWordsBetweenKeywords, search );
    viewCommonThreeWordPhrases( tree );

    return 0;
}

void parse(ifstream& text, string search,vector<int>& numOfWordsBetweenKeywords, vector<string> arr1, vector<string> arr2, vector<string> arr3, AvlTree& tree)
{
    int wordCounter = 0;
    int check = 0;
    string word;
    
    while(!text.eof()){
        getline (text, word);
        stringstream ss;
        ss << word;
        while (ss){
            string word2;
            ss >> word2;
            if (word2.length() != 0)// don't count white spaces as words
                wordCounter++;
            if(ss){
                char letter;
                for (int j=0; j<word2.length();j++){
                    letter = word2.at(j);
                    if((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122)){
                        if(check == 1)
                            word2.erase(j,1);
                    }else{
                        word2.erase(j, 1);
                        j--;
                        check = 1;
                    }
                }
                check = 0;
                if (word2 == search){
                    numOfWordsBetweenKeywords.push_back(wordCounter-1);
                    wordCounter = 0; 
                }
                commonThreeWordPhrase(word2, arr1, arr2, arr3, tree);
            }
        }
    }
}
void compute(vector<int>& numOfWordsBetweenKeywords, string search){
    float sum = 0;
    vector<int>::iterator it;
    for ( it=numOfWordsBetweenKeywords.begin() ; it < numOfWordsBetweenKeywords.end(); it++ ){
        sum +=*it;
    }
    cout << "This is the number of times \"" << search << "\" appeared on the given text: " << numOfWordsBetweenKeywords.size() << endl;
    if(numOfWordsBetweenKeywords.size() != 0)
        cout << "This the average number of words between each instance of \"" << search << "\": " << sum/numOfWordsBetweenKeywords.size() << endl;
}
void commonThreeWordPhrase(string word, vector<string>&arr1, vector<string>&arr2, vector<string>&arr3, AvlTree& tree){
    string concatenate = "";
 
    
    if(tree.isEmpty() == true){
        if(arr1.size() == 0 && arr2.size() == 0 && arr3.size() == 0)
            arr1.push_back(word);
        else if(arr1.size() == 1 && arr2.size() == 0 && arr3.size() == 0){
            arr1.push_back(word);
            arr2.push_back(word);
        }else if (arr1.size() == 2 && arr2.size() == 1 && arr3.size() == 0){
            arr1.push_back(word);
            arr2.push_back(word);
            arr3.push_back(word);
            if(arr1.size() == 3){
                for (int i = 0; i < arr1.size(); i++)
                    i == 0 ? concatenate = arr1[i] : concatenate = concatenate + " " + (string)arr1[i];

                tree.insert(concatenate);
                arr1.clear();
            }
        }
    }else{
        if(arr1.size()!= 3 && word.length() > 0)
            arr1.push_back(word);
        if(arr2.size() != 3 && word.length() > 0)
            arr2.push_back(word);
        if(arr3.size() != 3 && word.length() > 0)
            arr3.push_back(word);
        
        if(arr1.size() == 3) {
            for (int i = 0; i < arr1.size(); i++)
                i == 0 ? concatenate = arr1[i] : concatenate = concatenate + " " + (string)arr1[i];

            tree.insert(concatenate);
            arr1.clear();
        }
        if (arr2.size() == 3) {
            for (int i = 0; i < arr2.size(); i++)
                i == 0 ? concatenate = arr2[i] : concatenate = concatenate + " " + (string)arr2[i];

            tree.insert(concatenate);
            arr2.clear();
        }
        if (arr3.size() == 3) {
            for (int i = 0; i < arr3.size(); i++)
                i == 0 ? concatenate = arr3[i] : concatenate = concatenate + " " + (string)arr3[i];

            tree.insert(concatenate);
            arr3.clear();
        }
    }
}
void viewCommonThreeWordPhrases( AvlTree& tree ){
    cout << "Most common three word phrase is: " << tree.getLargestElement() << endl;
    cout << "It appeared: " << tree.getLargest() << " times." << endl;
}
