#include <iostream>
#include <string>
using namespace std;
void findString(string stringToSearch, string searchString);
int main()
{

    string stringToSearch, searchString;
    cout << "Give a string from which to search for: ";
    getline(cin, stringToSearch);
    cout << "Give search string: ";
    getline(cin, searchString);
    findString(stringToSearch, searchString);
}

void findString(string stringToSearch, string searchString)
{
    size_t found = stringToSearch.find(searchString);
    if (found!=string::npos)
    {
        cout << "\"" << searchString << "\" found in " << stringToSearch << " at position " << found << "\n";
    }
    else
    {
        cout << "\"" << searchString << "\" NOT found in \"" << stringToSearch << "\"\n";
    }
    return;
}

