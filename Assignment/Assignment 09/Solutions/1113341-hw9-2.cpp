#include <iostream>
#include <fstream>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( string *program, int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( string &sourceLine );

// deletes all string constants from sourceLine
void delStrConsts( string &sourceLine );

// deletes all character constants from sourceLine
void delCharConsts( string &sourceLine );

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers( string &sourceLine, string *identifiers, int &numIdentifiers );

// stores all non-keyword strings in the array identifiers into a text file
void store( string *identifiers, int numIdentifiers );

// return true if and only if "str" is a C++ keyword
bool keyword( string str );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( string *identifiers, int pos );

const string keywords[] = { "auto", "break", "case", "char", "const",
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
   string *program = new string[ 500 ];
   int numLines = 0;

   // reads in a C++ program from a cpp file, and put it to the array program
   load( program, numLines );

   string *identifiers = new string[ 500 ];
   string null;
   int numIdentifiers = 0;

   for( int i = 0; i < numLines; i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      if( program[ i ] != null )
         extractIdentifiers( program[ i ], identifiers, numIdentifiers );
         // extracts all identifiers from program[ i ], and put them into the array identifiers
   }

   // stores all non-keyword strings in the array identifiers into a text file
   store( identifiers, numIdentifiers );

	system( "pause" );
}

void load( string *program, int &numLines )
{
    ifstream inFile("test2.cpp", ios::in);
    if (!inFile) {
        cerr << "File cannot be opened!" << endl;
        exit(0);
    }

    while (!inFile.eof()) {
        getline(inFile, program[numLines++], '\n');
    }

    // cout << "nL:" << numLines << endl; /* show how many sorceLines */

    inFile.close();
}

void delComment( string &sourceLine )
{
   size_t length = sourceLine.size();
   if( length > 1 )
      for( size_t i = 0; i < length - 1; i++ )
         if( sourceLine[ i ] == '/' && sourceLine[ i + 1 ] == '/' )
         {
            sourceLine.erase( i, length );
            break;
         }
}

void delStrConsts( string &sourceLine )
{
    size_t length = sourceLine.size();
    if (length > 1) {
        for (size_t i = 0; i < length - 1; i++) {
            if (sourceLine[i] == '\"') {
                while (true) {
                    if (sourceLine[i] != '\\' && sourceLine[i + 1] == '\"') {
                        sourceLine[i++] = ' ';
                        sourceLine[i++] = ' ';
                        break;
                    }
                    sourceLine[i++] = ' ';
                }
            }
        }
    }
}

void delCharConsts( string &sourceLine )
{
    size_t length = sourceLine.size();
    if (length > 1) {
        for (size_t i = 0; i < length - 1; i++) {
            if (sourceLine[i] == '\'' && sourceLine[i + 1] == '\\') {
                for (int j = 1; j <= 4; j++) {
                    sourceLine[i++] = ' ';
                }
            }
            else if (sourceLine[i] == '\'' && sourceLine[i + 1] != '\\') {
                for (int j = 1; j <= 3; j++) {
                    sourceLine[i++] = ' ';
                }
            }
        }
    }


}

void extractIdentifiers( string &sourceLine, string *identifiers, int &numIdentifiers )
{
    string symbols = "#(){}<>[]!&=.%+,;";
    size_t length = sourceLine.size();
    size_t lenSymbols = symbols.size();
   
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < lenSymbols; j++) {
            if (sourceLine[i] == symbols[j])// && sourceLine[i + 1] != '\0'
                sourceLine[i] = ' ';
        }
    }

    /*以下結果會出錯
    for (int i = 0; i < length; i++) { //if the soureceLine has a character of symbols, set it to space (delimeter)
        for (int j = 0; j < lenSymbols; j++) {
            if (sourceLine[i] == symbols[j] && sourceLine[i + 1] != '\0') {
                sourceLine[i] = ' ';
            }
            else if (sourceLine[i] == symbols[j] && sourceLine[i + 1] == '\0') {
                sourceLine[i] = '\0';
            }
        }
    }
    */

    size_t pos = 0;
    string token;
    string delimiter = " ";

    while ((pos = sourceLine.find(delimiter)) != string::npos)
    {
        token = sourceLine.substr(0, pos);

        if (isdigit(token[0]))
        {
            sourceLine.erase(0, pos + delimiter.length());
            continue;
        }
        if (!keyword(token))
        {
            identifiers[numIdentifiers++] = token;
        }
        if (duplicate(identifiers, numIdentifiers - 1))
        {
            identifiers[numIdentifiers - 1].erase(0, identifiers[numIdentifiers].size());
            numIdentifiers--;
        }

        sourceLine.erase(0, pos + delimiter.length()); /*next token*/
    }
}

void store( string *identifiers, int numIdentifiers )
{
    ofstream outFile("identifiers(9-2).txt", ios::out);

    if (!outFile) {
        cerr << "File could not be opened!" << endl;
        exit(1);
    }

    for (int i = 0; i < numIdentifiers - 1; i++) {
        outFile << identifiers[i] << endl;
    }
    outFile << identifiers[numIdentifiers - 1];

    outFile.close();
}

bool keyword( string str )
{
   const int numKeywords = sizeof( keywords ) / 20;
   for( int i = 0; i < numKeywords; i++ )
      if( keywords[ i ] == str )
         return true;

   return false;
}

bool duplicate( string *identifiers, int pos )
{
   for( int i = 0; i < pos; i++ )
      if( identifiers[ i ] == identifiers[ pos ] )
         return true;

   return false;
}
