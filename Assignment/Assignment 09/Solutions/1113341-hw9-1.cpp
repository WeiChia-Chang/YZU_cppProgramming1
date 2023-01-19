#include <iostream>
#include <fstream>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load(char(*program)[100], int& numLines);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(char sourceLine[]);

// deletes all string constants from sourceLine
void delStrConsts(char sourceLine[]);

// deletes all character constants from sourceLine
void delCharConsts(char sourceLine[]);

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers(char sourceLine[], char identifiers[][32], int& numIdentifiers);

// stores all non-keyword strings in the array identifiers into a text file
void store(char(*identifiers)[32], int numIdentifiers);

// returns true if and only if str is a C++ keyword
bool keyword(char str[]);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(char(*identifiers)[32], int pos);

const char keywords[][20] = { "auto", "break", "case", "char", "const",
                                "continue", "default", "define","do", "double",
                                "else", "enum", "extern", "float", "for",
                                "goto", "if", "int", "long", "register",
                                "return", "short", "signed", "sizeof",
                                "static", "struct", "switch", "typedef",
                                "union", "unsigned", "void", "volatile",
                                "while", "bool", "catch", "class",
                                "const_cast", "delete", "dynamic_cast",
                                "explicit", "false", "friend", "inline",
                                "mutable", "namespace", "new", "operator",
                                "private", "protected", "public",
                                "reinterpret_cast", "static_cast", "template",
                                "this", "throw", "true", "try", "typeid",
                                "typename", "using", "virtual", "include" };

int main()
{
    char(*program)[100] = new char[500][100];
    int numLines = 0;

    // reads in a C++ program from a cpp file, and put it to the array program
    load(program, numLines);
    char(*identifiers)[32] = new char[500][32];
    int numIdentifiers = 0;

    for (int i = 0; i < numLines; i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]

        delCharConsts(program[i]); // deletes all character constants from program[ i ]
        // cout << program[ i ] << endl;

        if (strcmp(program[i], "") != 0)
            extractIdentifiers(program[i], identifiers, numIdentifiers);

        // extracts all identifiers from program[ i ], and put them into the array identifiers
    }

    // stores all non-keyword strings in the array identifiers into a text file
    store(identifiers, numIdentifiers);

     system( "pause" );
}

void load(char(*program)[100], int& numLines)
{
    ifstream inFile("test2.cpp", ios::in);
    if (!inFile) {
        cerr << "File cannot be opened!" << endl;
        exit(0);
    }

    while (!inFile.eof()) {
        inFile.getline(program[numLines], 100, '\n');
        numLines++;
    }

    // cout << "nL:" << numLines << endl; /* show how many sorceLines */

    inFile.close();
}

void delComment(char sourceLine[])
{
    size_t length = strlen(sourceLine);
    if (length > 1)
        for (size_t i = 0; i < length - 1; i++)
            if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
            {
                sourceLine[i] = '\0';
                return;
            }
}

void delStrConsts(char sourceLine[])
{
    size_t length = strlen(sourceLine);
    if (length > 1) {
        for (size_t i = 0; i < length - 1; i++) {
            if (sourceLine[i] == '"') {
                while (true) {
                    sourceLine[i++] = ' ';
                    if (sourceLine[i] != '\\' && sourceLine[i + 1] == '"') { /*only if the " is the last, break*/
                        sourceLine[i++] = ' ';
                        sourceLine[i++] = ' ';
                        break;
                    }
                }
            }
        }
    }
}

void delCharConsts(char sourceLine[])
{
    size_t length = strlen(sourceLine);
    if (length > 1) {
        for (size_t i = 0; i < length - 1; i++) {
            if (sourceLine[i] == '\'' && sourceLine[i + 1] == '\\') {
                for (int j = 1; j <= 4; j++) {
                    sourceLine[i++] = ' ';
                }
            }
            else if (sourceLine[i] == '\'' && sourceLine[i + 1] != '\n') {
                for (int j = 1; j <= 3; j++) {
                    sourceLine[i++] = ' ';
                }
            }
        }
    }
}

void extractIdentifiers(char sourceLine[], char identifiers[][32], int& numIdentifiers)
{
    char symbols[] = "(){}[]!=#<>;+&,.%"; /* set symbols which shoult not be print*/
    size_t length = strlen(sourceLine);
    size_t lenSymblics = strlen(symbols);
    for (int i = 0; i < length; i++) { /*if the soureceLine has a character of symbols, set it to space (delimeter)*/
        for (int j = 0; j < lenSymblics; j++) {
            if (sourceLine[i] == symbols[j] && sourceLine[i + 1] != '\0') {
                sourceLine[i] = ' ';
            }
            else if (sourceLine[i] == symbols[j] && sourceLine[i + 1] == '\0') {
                sourceLine[i] = '\0';
            }
        }
    }
    //cout << "sourceLine : " << sourceLine << endl; /* cout the souceLine after being set space on which character should not be print */


    char* ptr;
    char* next;
    int n = 0;
    ptr = strtok_s(sourceLine, " ", &next);
    
    while (ptr != nullptr) {
        if (ptr[0] >= '0' && ptr[0] <= '9') { /*set numbers which are not parts of variable to delimeter*/
            ptr = strtok_s(nullptr, " ", &next);/*if the first char. of string ptr is numbers, skip it*/
            continue;
        }
        if (!keyword(ptr)) { /* if the ptr is not one of the keywords(which should not be print), store it to array identifiers*/
            for (int i = 0; i < strlen(ptr); i++)
            {
                identifiers[numIdentifiers][i] = ptr[i];
            }
            identifiers[numIdentifiers++][strlen(ptr)] = '\0'; /*put a NUL at the last of string identifiers[numIdentifiers] */
        }
        if (duplicate(identifiers, numIdentifiers - 1)) 
            identifiers[numIdentifiers -- ][0] = '\0'; /*if the ptr sholud be stored and it has already been, let it be NUL and do next token*/

        ptr = strtok_s(nullptr, " ", &next);
    }
}

void store(char(*identifiers)[32], int numIdentifiers)
{
    ofstream outFile("identifiers(9-1).txt", ios::out);

    if (!outFile)
    {
        cout << "File could not be opened" << endl;
        exit(1);
    }

    for (int i = 0; i < numIdentifiers - 1; i++)
    {
        outFile << identifiers[i] << endl;
    }
    outFile << identifiers[numIdentifiers - 1];

    outFile.close();

}

bool keyword(char str[])
{
    size_t numKeywords = sizeof(keywords) / 20;
    for (size_t i = 0; i < numKeywords; i++)
        if (strcmp(keywords[i], str) == 0)
            return true;

    return false;
}

bool duplicate(char(*identifiers)[32], int pos)
{
    for (int i = 0; i < pos; i++)
        if (strcmp(identifiers[i], identifiers[pos]) == 0)
            return true;

    return false;
}
