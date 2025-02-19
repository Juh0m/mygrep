#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct Arguments
{
    bool lineNumbers = false;
    bool occurences = false;
};

struct FoundLine
{
    std::string text;
    int lineNumber;
};

using namespace std;
bool findString(string stringToSearch, string searchString);
void findStringFromText(string stringToSearch, string searchString);
void findStringFromFile(string fileToSearch, string searchString, Arguments args);

int main(int argc, char* argv[])
{
    string searchString;
    string stringToSearch;
    bool lineNumbers = false;
    bool occurences = false;
    if (argc > 1)
    {
        Arguments args;
        int length = strlen(argv[1]);
        if (length < 2)
        {
            // TODO: heitä error
        }

        for (int i = 0; i < length-2; i++)
        {
            if (argv[1][i + 2] == 'l')
            {
                args.lineNumbers = true;
            }
            else if (argv[1][i + 2] == 'o')
            {
                args.occurences = true;
            }
        }
        // Jos argumentteja on kolme -> Ei ole käytössä argumentit (-o) joten haettava teksti löytyy yhden aiemmasta
        if (argc == 3)
        {
            searchString = argv[1];
            stringToSearch = argv[2];
        }
        // Käytössä argumentit (-o)
        else
        {
            searchString = argv[2];
            stringToSearch = argv[3];
        }
        
        if (findString(argv[3], ".txt"))
        {
            findStringFromFile(stringToSearch, searchString, args);
        }

        // Annettiin tekstiä eikä tekstitiedostoa
        // Argumentit ei käytössä koska ei tarvinnut toimia tälle
        else
        {
            findStringFromText(stringToSearch, searchString);
        }
    }
    // Ei annettu mitään argumentteja, kysytään siis mitä haetaan ja mistä
    else
    {
        cout << "Give a string from which to search for: ";
        getline(cin, stringToSearch);
        cout << "Give search string: ";
        getline(cin, searchString);
        findStringFromText(stringToSearch, searchString);
    } 
}

void findStringFromFile(string fileToSearch, string searchString, Arguments args)
{
    string line;
    ifstream inputfile;
    inputfile.open(fileToSearch);
    vector<FoundLine> foundStringLines;
    int lineNumber = 1;
    while (getline(inputfile, line))
    {
        if (line.find(searchString) != string::npos)
        {
            FoundLine foundLine = { line, lineNumber };
            foundStringLines.emplace_back(foundLine);
        } 
        lineNumber++;
    }
    
    if (args.lineNumbers)
    {
        for (const FoundLine& line : foundStringLines)
        {
            cout << line.lineNumber << ": " << line.text << "\n";
        }
    }
    else
    {
        for (const FoundLine& line : foundStringLines)
        {
            cout << line.text << "\n";
        }
    }
 
    if (args.occurences)
    {
        cout << "Occurrences of lines containing \"" << searchString << "\": " << foundStringLines.size();
    }
}

bool findString(string stringToSearch, string searchString)
{
    size_t found = stringToSearch.find(searchString);
    return (found != string::npos);
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
