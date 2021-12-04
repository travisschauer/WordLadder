// Travis Schauer
// 11/2/20 finished 11/10/20
// Kramer 3700
// This program takes two words and creates a word ladder between the words
// It uses a predefined data file for the words

#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "linearlist.h"

using namespace std;

struct WordParam {
    string word;
    int nextWord;
    LinearList<int> adjacentWords;
};

int HammingDist(string inputOne, string inputTwo){
    int count = 0;

    for (int i = 0; i < inputOne.length(); i++){
        if (inputOne[i] != inputTwo[i]){
            count++;
        }
    }

    return count;
}

void GenLadder(int wordOne, int wordTwo, LinearList<string>& ladder, WordParam dictionary[]){
    int wordPointer;
    Queue<int> ladderBuilder;
    
    ladder.clear();

    ladderBuilder.enqueue(wordTwo);

    while (!ladderBuilder.isEmpty()){
        // dequeue Q into wordPointer
        wordPointer = ladderBuilder.dequeue();

        //for each word V in w.list do
        for (int i = 0; i < dictionary[wordPointer].adjacentWords.size(); i++){

            //if v.ptr = NULL and v /= wordTwo then
            int v = dictionary[wordPointer].adjacentWords[i];
            if (dictionary[v].nextWord == -1 && v != wordTwo){
                // v.ptr <--- wordPointer
                dictionary[v].nextWord = wordPointer;
                
                //Enqueue V in Q
                ladderBuilder.enqueue(v); 
            }
        }   
    }

    for (int i = wordOne; i != -1; i = dictionary[i].nextWord){
        ladder.insert(ladder.size(), dictionary[i].word);
    }
}

int main(){
    string inputWord, wordPair, wordOne, wordTwo;
    WordParam dictionary[5757];
    LinearList<string> ladder;
    ifstream sgbWords;
    sgbWords.open("sgb-words.txt");

    // read from sgb-words.txt
    if (sgbWords.is_open()){
        for (int i = 0; i < 5757; i++){
            sgbWords >> dictionary[i].word;

            dictionary[i].nextWord = -1;

            for (int j = 0; j < i-1; j++){
                if (HammingDist(dictionary[i].word, dictionary[j].word) == 1){
                    // add inputWord to wordPair list
                    dictionary[j].adjacentWords.insert(0,i);

                    // add wordPair to inputWord list
                    dictionary[i].adjacentWords.insert(0,j);
                }
            }
        }
    }

    sgbWords.close();
    
    // Read two five letter words as input
    cout << "Enter two five letter words"  << endl;
    cout << "Word One: " << endl;
        cin >> wordOne;

    cout << "Word Two: " << endl;
        cin >> wordTwo;
    
    cout << " " << endl;    

    // Find both words in the word list
    int trackerOne = -1, trackerTwo = -1;

    for (int i = 0; i < 5757; i++){
        string compareWord;

        compareWord = dictionary[i].word;

        // if it does exist ----> grab pointer
        if (wordOne == dictionary[i].word){
            trackerOne = i;
        }

        if (wordTwo == dictionary[i].word){
            trackerTwo = i;
        }
    }

    // if it doesn't exsist ----> no word ladder exists
    if (trackerOne == -1){
        cout << wordOne << " is not in dictionary" << endl;
    }
        
    if (trackerTwo == -1){
        cout << wordTwo << " is not in the dictionary" << endl;
    }
    
    // Run Algorithim 
    GenLadder(trackerOne, trackerTwo, ladder, dictionary);

    // Output ladder
    if (ladder.size() <= 1){
        cout << "\nNo word ladder exists" << endl;
    } else {
        cout << "\nHere is your ladder: " << endl;
        for (int i = 0; i < ladder.size(); i++){
            cout << ladder[i] << endl;
        }
    }

    return 0;
}