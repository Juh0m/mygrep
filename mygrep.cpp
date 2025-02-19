#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
bool findString(string stringToSearch, string searchString);
void findStringFromText(string stringToSearch, string searchString);
void findStringFromFile(string fileToSearch, string searchString);
int main(int argc, char* argv[])
{
    string searchString;
    string stringToSearch;
    if (argc > 1)
    {
        searchString = argv[1];
        stringToSearch = argv[2];

        if (findString(argv[2], ".txt"))
        {
            findStringFromFile(stringToSearch, searchString);
        }
        else
        {
            findStringFromText(stringToSearch, searchString);
        }
    }
    else
    {
        cout << "Give a string from which to search for: ";
        getline(cin, stringToSearch);
        cout << "Give search string: ";
        getline(cin, searchString);
        findStringFromText(stringToSearch, searchString);
    } 
}

void findStringFromFile(string fileToSearch, string searchString)
{
    string line;
    ifstream inputfile;
    inputfile.open(fileToSearch);
    vector<string> foundStringLines;
    while (getline(inputfile, line))
    {
        if (findString(line, searchString))
        {
            foundStringLines.emplace_back(line);
        } 
    }
    
    for (string line : foundStringLines)
    {
        cout << line << "\n";
    }
}

bool findString(string stringToSearch, string searchString)
{
    size_t found = stringToSearch.find(searchString);
    if (found!=string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
   
}
// Jos ei annettu tiedostoa vaan tekstiä
void findStringFromText(string stringToSearch, string searchString)
{
    size_t found = stringToSearch.find(searchString);
    if (found != string::npos)
    {
        cout << "\"" << searchString << "\" found in \"" << stringToSearch << "\" at position " << found << "\n";
    }
    else
    {
        cout << "\"" << searchString << "\" NOT found in \"" << stringToSearch << "\"\n";
    }
    return;
}



