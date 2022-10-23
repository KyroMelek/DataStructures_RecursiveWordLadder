// Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

vector<string> constructDictionaryFromFile(string pathToFile);
vector<string> constructDictionaryFromDictionary(string startWord, vector<string> originalDictionary);
int searchDictionary(string word, vector<string>& dictionary);
bool wordLadder(string startWord, string endWord, vector<string>& dictionary);

int main()
{    
    vector<string> originalDictionary = constructDictionaryFromFile("Dictionary.txt");

    bool validString = false;
    string startWord = "";
    string endWord = "";

    while (!validString)
    {
        cout << "Enter a start word: ";
        cin >> startWord;

        cout << "\nEnter a target word: ";
        cin >> endWord;

        if (startWord.size() != endWord.size())
        {
            cout << "\nStart and target words are not the same length, try again" << endl;
            cin.clear();
            cin.ignore(123, '\n');
            continue;
        }
        else if (searchDictionary(endWord, originalDictionary) == -1)
        {
            cout << "\nTarget word is not in the dictionary, try again" << endl;
            cin.clear();
            cin.ignore(123, '\n');
            continue;
        }
        else
        {
            vector<string> dictionary = constructDictionaryFromDictionary(startWord, originalDictionary); 
            cout << "Loading..." << endl;
            if (wordLadder(startWord, endWord, dictionary))
                cout << startWord << endl;
            else
                cout << "No ladder could be found from " + startWord + " to " + endWord << endl;

            bool validInput = false;
            bool keepPlaying = false;

            while (!validInput)
            {
                string shouldContinue = "";
                cout << "\nDo you want to try another ladder? (Y or N):";
                cin >> shouldContinue;

                if (shouldContinue == "Y" || shouldContinue == "y")
                {
                    keepPlaying = true;
                    validInput = true;
                }
                else if (shouldContinue == "N" || shouldContinue == "n")
                {
                    keepPlaying = false;
                    validInput = true;
                }                    
                else
                {
                    cout << "\nInvalid option, please try again\n";
                    validInput = false;
                }
            }

            if (keepPlaying)
            {
                cin.clear();
                cin.ignore(123, '\n');
                continue;
            }
            else
                break;
        }
    }
}

/// <summary>
/// Consturcts a dictionary from a file using a vector of strings
/// </summary>
/// <param name="pathToFile"></param>
/// <returns> The dictionary as a vector of strings </returns>
vector<string> constructDictionaryFromFile(string pathToFile)
{
    string line;
    ifstream cityDatabaseFile;
    int numOfWordsInDictionary = 0;
    vector<string> dictionary;
    //Count number of cities in file
    cityDatabaseFile.open(pathToFile, std::ios::in);
    if (cityDatabaseFile.is_open())
    {
        while (!cityDatabaseFile.eof())
        {
            getline(cityDatabaseFile, line);
            //ignore empty lines
            if (line == "")
                continue;
            dictionary.push_back(line);
            numOfWordsInDictionary++;
        }
        cityDatabaseFile.close();
    }
    return dictionary;
}

/// <summary>
/// Creates a new dictionary from an existing one where all words are equal in length 
/// to the start and target words
/// </summary>
/// <param name="startWord"></param>
/// <param name="originalDictionary"></param>
/// <returns> Dictionary with words of size startWord.size() </returns>
vector<string> constructDictionaryFromDictionary(string startWord, vector<string> originalDictionary)
{
    vector<string> newDictionary;
    for (unsigned int i = 0; i < originalDictionary.size(); ++i)
    {
        if (originalDictionary[i].size() == startWord.size())
        {
            newDictionary.push_back(originalDictionary[i]);
        }
    }
    return newDictionary;
}

/// <summary>
/// Searches for a given word in the dictionary
/// </summary>
/// <param name="word"></param>
/// <param name="dictionary"></param>
/// <returns> index of word if found, -1 otherwise </returns>
int searchDictionary(string word ,vector<string>& dictionary)
{   
    for (unsigned int i = 0; i < dictionary.size(); ++i)
    {
        if (dictionary[i] == "")
            continue;
        else if (dictionary[i] == word)
        {            
            return i;
        }
    }
    return -1;
}

/// <summary>
/// Recursively searches for a word ladder from a start word to a target word
/// </summary>
/// <param name="startWord"></param>
/// <param name="endWord"></param>
/// <param name="dictionary"></param>
/// <returns> true if a ladder has been found from a given start word, false otherwise </returns>
bool wordLadder(string startWord, string endWord, vector<string>& dictionary)
{
    //Base Case
    if (startWord == endWord)
        return true;
   
    vector<string> adjacentWords;
    //Find and store all words adjacent to the start word (all words that differ by one letter from the startWord)
    for (unsigned int i = 0; i < dictionary.size(); ++i)
    {
        if (dictionary[i] == "")
            continue;
        int differingCharacters = 0;
        for (unsigned int j = 0; j < startWord.size(); ++j)
        {
            if (startWord[j] != dictionary[i][j])
            {
                ++differingCharacters;
            }
            if (differingCharacters > 1)
                break;
        }
        if (differingCharacters == 1)
        {
            adjacentWords.push_back(dictionary[i]);
            //Delete adjacent words from dictionary so we do not reuse/ repeat the same function on the same words 
            dictionary[i] = "";
        }            
    }

    for (string word : adjacentWords)
    {
        if (wordLadder(word, endWord, dictionary))
        {
            cout << word << endl;
            return true;
        }            
    }
    //No Path from startWord (or a given adjacent word) to endWord
    return false;    
}