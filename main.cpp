#include <iostream>
#include <string>
#include <fstream>
#include<bits/stdc++.h>

using namespace std;

struct Node
{
    struct Node *children[26];

    int numberOfAppereances = 0;

    bool endOfWord;
};

string convertToLower(string str){

    transform(str.begin(), str.end(), str.begin(), ::tolower);

    return str;

}

void insert( Node *root, string key)
{
     Node *tmp = root;

    int i = 0;
    int strSize = key.length();

    while(i < strSize)
    {
        int index = key[i] - 97;
        if (tmp->children[index] == NULL) {

            tmp->children[index] =  new Node;

            tmp->children[index]->endOfWord = false;

            for (int i = 0; i < 26; i++)
                tmp->children[index]->children[i] = NULL;

        }

        tmp = tmp->children[index];
        i++;
    }

    tmp->endOfWord = true;
    tmp->numberOfAppereances++;
}

void search( Node *root, string key)
{
    key = convertToLower(key);

     Node *tmp = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 97;
        if (!tmp->children[index]) {
            cout << "Doesent exist" << endl;
            return;
        }
        tmp = tmp->children[index];
    }

    if(tmp!= NULL && tmp->endOfWord){
        cout << "exists" << endl;
        return;

    }

    cout << "doesent exist" << endl;
    return;
}

string stringArray[1000];
int numberOfWordsInStringArray = 0;

bool containsValidCharacters(string s){

    int strSize = s.length();

        for (int i = 0; i < strSize; i++) {

            if (s[i] < 'A' || s[i] > 'Z' &&
                              s[i] < 'a' || s[i] > 'z')
            {
                return false;
            }
        }
        return true;
}

void readFromFile(string filename)
{
    fstream file;
    string word, t, q;

    file.open(filename.c_str());

    while (file >> word)
    {
               if(containsValidCharacters(word)) {

            word = convertToLower(word);

            stringArray[numberOfWordsInStringArray] = word;
            numberOfWordsInStringArray++;
        }

        if(numberOfWordsInStringArray == 500) return;

    }

}

bool isLeaf( Node* root)
{
    for (int i = 0; i < 26; i++)
        if (root->children[i])
            return false;
    return true;
}

int arrayOfConsistencies[100];
int sizeOfArrayOfConsistencies = 0;
string arrayOfMatches[100];

bool startingPrefix = true;

bool isNear(char ch1, char ch2){
    string mapOfNearCharacters[26];

    mapOfNearCharacters[0] = "qwsz"; //a
    mapOfNearCharacters[1] = "gvhjn"; //b
    mapOfNearCharacters[2] = "xdfgv";//c
    mapOfNearCharacters[3] = "xserf";//d
    mapOfNearCharacters[4] = "wsdr";//e
    mapOfNearCharacters[5] = "drtgc";//f
    mapOfNearCharacters[6] = "tyhvf";//g
    mapOfNearCharacters[7] = "gyujb";//h
    mapOfNearCharacters[8] = "ujko";//i
    mapOfNearCharacters[9] = "uihkn";//j
    mapOfNearCharacters[10] = "mjlio";//k
    mapOfNearCharacters[11] = "mokp";
    mapOfNearCharacters[12] = "njkl";
    mapOfNearCharacters[13] = "bhjkm";
    mapOfNearCharacters[14] = "iklp";
    mapOfNearCharacters[15] = "ol";
    mapOfNearCharacters[16] = "aw";
    mapOfNearCharacters[17] = "deft";
    mapOfNearCharacters[18] = "awedzx";
    mapOfNearCharacters[19] = "rygf";
    mapOfNearCharacters[20] = "yhji";
    mapOfNearCharacters[21] = "cfgb";
    mapOfNearCharacters[22] = "qeas";
    mapOfNearCharacters[23] = "zsdc";
    mapOfNearCharacters[24] = "tghu";
    mapOfNearCharacters[25] = "asx";

    for (int i = 0; i < 26; ++i)
    {
        if(ch1 == i + 97)
        {
            if (mapOfNearCharacters[i].find(ch2) != string::npos) return true;
        }

    }

    return false;

}

void suggestionsContinue( Node* root, string prefix)
{
    if (root->endOfWord)
    {
        arrayOfConsistencies[sizeOfArrayOfConsistencies] = root->numberOfAppereances;
        arrayOfMatches[sizeOfArrayOfConsistencies] = prefix;
        sizeOfArrayOfConsistencies++;

        cout << prefix;
        cout << endl;
    }

    if (isLeaf(root))
        return;

    char lastCharacterOfPrefix = prefix.back();

    for (int i = 0; i < 26; i++)
    {
        if (root->children[i])
        {

                prefix.push_back(97 + i);

                suggestionsContinue(root->children[i], prefix);

                prefix.pop_back();
            }
        }

}

int suggest(Node* root, const string str)
{
     Node* pCrawl = root;

    int i = 0;
    int strSize = str.length();
    while (i < strSize)
    {
        int index = str[i] - 97;

        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];

        i++;
    }

    if (pCrawl->endOfWord && isLeaf(pCrawl))
    {
        cout << str << endl;
        return -1;
    }

    if (!isLeaf(pCrawl))
    {
        string prefix = str;
        suggestionsContinue(pCrawl, prefix);
        return 1;
    }
}

void findThreeMostUsedCharacters(char ch, int index){

    int first, second, third;

    int arr_size = sizeOfArrayOfConsistencies;

    if (arr_size < 3)
    {
        cout << " Invalid Input ";
        return;
    }

    third = first = second = INT_MIN;
    for(int i = 0; i < arr_size; i++) {

        if (arrayOfConsistencies[i] > first && isNear(ch, arrayOfMatches[i][index])) {
            third = second;
            second = first;
            first = i;
        }

        else if (arrayOfConsistencies[i] > second && isNear(ch, arrayOfMatches[i][index])) {
            third = second;
            second = i;
        } else if (arrayOfConsistencies[i] > third && isNear(ch, arrayOfMatches[i][index])) {
            third = i;
        }
    }

    cout << "Three most used elements are: \n";

    if(first >= 0) cout << arrayOfMatches[first]<< endl;
    if(second >= 0) cout << arrayOfMatches[second]<< endl;
    if(third >= 0) cout << arrayOfMatches[third]<< endl;

}

void deleteTree(Node* root){

    for (int i = 0; i < 26; ++i) {
        if(root->children[i]->numberOfAppereances>0){
            root->children[i]->numberOfAppereances = 0;
        }
    }

    delete root;

}

int main(){

    readFromFile("file.txt");

     Node *root =  new Node;

    root->endOfWord = false;

    for (int i = 0; i < 26; i++)
        root->children[i] = NULL;

    for (int i = 0; i < 100; i++) {
        stringArray[i] = convertToLower(stringArray[i]);
        insert(root, stringArray[i]);
    }

    search(root, "agtres");
    search(root, "as");
    search(root, "lAdies");

    string word = "b";

    int comp = suggest(root, word);

    if (comp == -1)
        cout << "No other strings found with this prefix\n";

    else if (comp == 0) {
        cout << "No string found with this prefix\n";
        word.pop_back();
        comp = suggest(root, word);

        if (comp == 0) {
            cout << "No string found with this prefix\n";
            word.pop_back();
            comp = suggest(root, word);

        }

    }

    findThreeMostUsedCharacters(word.back(), word.length());

    return 0;
}