#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>


struct Arguments
{
    bool lineNumbers = false;
    bool occurences = false;
    bool reverse = false;
    bool caseInsensitive = false;
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
    setlocale(LC_ALL, "fi-FI");
    string searchString;
    string stringToSearch;
    bool argsInUse = false;
    try
    {
        // Vain yht‰ argumenttia ei voi k‰ytt‰‰
        if (argc == 2)
        {
            throw std::invalid_argument("Too few arguments");
        }
        // Jos k‰ytet‰‰n jotain argumentteja
        if (argc > 1)
        {
            Arguments args;
            int length = strlen(argv[1]);
            // Jos k‰ytet‰‰n -o argumentteja, mit‰ k‰ytet‰‰n. Pelkk‰ -o ei tee mit‰‰n
            if (static_cast<string>(argv[1]).substr(0, 2) == "-o")
            {
                argsInUse = true;
                for (int i = 0; i < length - 2; i++)
                {
                    switch (argv[1][i + 2])
                    {
                    case 'l':
                        args.lineNumbers = true;
                        break;
                    case 'o':
                        args.occurences = true;
                        break;
                    case 'r':
                        args.reverse = true;
                        break;
                    case 'i':
                        args.caseInsensitive = true;
                        break;
                    default:
                        throw std::invalid_argument("Invalid arguments");
                    }
                }
            }

            // Jos -o argumentteja ei k‰ytˆss‰, haettava string ja mist‰ haetaan lˆytyy 1 aikaisemmin
            if (!argsInUse)
            {
                searchString = argv[1];
                stringToSearch = argv[2];
                if (argc > 3)
                {
                    throw std::invalid_argument("Too many or invalid arguments");
                }
            }
            else if (argsInUse)
            {
                searchString = argv[2];
                stringToSearch = argv[3];
                if (argc > 4)
                {
                    throw std::invalid_argument("Too many or invalid arguments");
                }
            }

            // Annettiin tekstitiedosto.
            if (findString(stringToSearch, ".txt"))
            {
                findStringFromFile(stringToSearch, searchString, args);
            }

            // Annettiin teksti‰ eik‰ tekstitiedostoa
            // Argumentit ei k‰ytˆss‰ koska ei tarvinnut toimia t‰lle
            else
            {
                findStringFromText(stringToSearch, searchString);
            }
        }
        // Ei annettu mit‰‰n argumentteja, kysyt‰‰n siis mit‰ haetaan ja mist‰
        else
        {
            cout << "Give a string from which to search for: ";
            getline(cin, stringToSearch);
            cout << "Give search string: ";
            getline(cin, searchString);
            findStringFromText(stringToSearch, searchString);
        }
    }
    // Virheenk‰sittely
    catch (const exception& e)
    {
        cout << "An error occured: " << e.what() << "\n";
    }
}

void findStringFromFile(string fileToSearch, string searchString, Arguments args)
{
    
    string line;
    ifstream inputfile;
    inputfile.open(fileToSearch);
    // Tarkistetaan, ett‰ tiedosto on olemassa
    try 
    {
        if (!inputfile.good())
        {
            throw std::ios_base::failure("Specified file does not exist or cannot be opened.");
        }
    }
    catch (const exception& e)
    {
        cout << "An error occured: " << e.what() << "\n";
    }
    vector<FoundLine> foundStringLines;
    int lineNumber = 1;
    while (getline(inputfile, line))
    {
        // Normaali haku
        if (line.find(searchString) != string::npos && !args.caseInsensitive && !args.reverse)
        {
            FoundLine foundLine = { line, lineNumber };
            foundStringLines.emplace_back(foundLine);
        }
        // -r, normaali k‰‰nteinen haku
        else if (line.find(searchString) == string::npos && !args.caseInsensitive && args.reverse)
        {
            FoundLine foundLine = { line, lineNumber };
            foundStringLines.emplace_back(foundLine);
        }
        // -i, merkkikokoriippumaton haku
        else if (args.caseInsensitive)
        {
            string lowerLine = line;
            string lowerSearch = searchString;
            ranges::transform(lowerLine, lowerLine.begin(), tolower);
            ranges::transform(lowerSearch, lowerSearch.begin(), tolower);

            // normaali merkkikokoriippumaton haku
            if (lowerLine.find(lowerSearch) != string::npos && !args.reverse)
            {
                FoundLine foundLine = { line, lineNumber };
                foundStringLines.emplace_back(foundLine);
            }   
            // -r, k‰‰nteinen merkkikokoriippumaton haku
            else if (lowerLine.find(lowerSearch) == string::npos && args.reverse)
            {
                FoundLine foundLine = { line, lineNumber };
                foundStringLines.emplace_back(foundLine);
            }
        }         
        lineNumber++;
    }
    if (foundStringLines.empty())
    {
        cout << "No matches found.";
        return;
    }
    
    // Rivien tulostus
    // -l, rivinumerot
    if (args.lineNumbers)
    {
        for (const FoundLine& line : foundStringLines)
        {
            cout << line.lineNumber << ": " << line.text << "\n";
        }
    }
    // Ei rivinumeroita
    else
    {
        for (const FoundLine& line : foundStringLines)
        {
            cout << line.text << "\n";
        }
    }

    // -o
    if (args.occurences)
    {
        if (!args.reverse)
        {
            cout << "Occurrences of lines containing \"" << searchString << "\": " << foundStringLines.size();
        }
        // -o, -i
        else
        {
            cout << "Occurrences of lines NOT containing \"" << searchString << "\": " << foundStringLines.size();
        }
        
    }
}

bool findString(string stringToSearch, string searchString)
{
    size_t found = stringToSearch.find(searchString);
    return (found != string::npos);
}
// Jos ei annettu tiedostoa vaan teksti‰
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
