#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <iomanip>

using namespace std;

//Struct
struct MovieNode
{
    string title;
    string lead;
    string support;
    string genre;
    string altGenre;
    int year;
    int rating;
    string synopsis;
    MovieNode *next;
};

enum choice {EXIT = 0, OUTPUT = 1, TITLE = 2, GENRE = 3, LEAD = 4, YEAR = 5, RATING = 6};

//functions
// create a list and read the data from a file
MovieNode *Create(MovieNode *head)
{
    //bool found;    // OUT - check to see if the element is in the list
    MovieNode* perPtr; // OUT - pointer to the element
    ifstream inFile;
    inFile.open("InFile.txt");
    perPtr = new MovieNode;
    while (inFile && perPtr != NULL)
        {
            getline(inFile, perPtr->title);
            getline(inFile, perPtr->lead);
            getline(inFile, perPtr->support);
            getline(inFile, perPtr->genre);
            getline(inFile, perPtr->altGenre);
            inFile>>perPtr->year;
            inFile.ignore(1000, '\n');
            inFile>>perPtr->rating;
            inFile.ignore(1000, '\n');
            getline(inFile, perPtr->synopsis);
            inFile.ignore(1000, '\n');
            //cout << perPtr->title << endl;
            perPtr->next = head;
            head = perPtr;
            perPtr = new MovieNode;   
        }
    delete perPtr;
    return head;
}

void Display(MovieNode *head)
{
    cout << "\n\nMovie List:" << endl << endl;
    MovieNode* perPtr = head;
    while (perPtr!= NULL)
    {
        cout << "Title: " << perPtr->title << endl;
        cout << "Actor(Lead): " << perPtr->lead << endl;
        cout << "Actor (Support)" << perPtr->support << endl;    
        cout << "Genre: " << perPtr->genre << endl;
        cout << "Alt Genre: " << perPtr->altGenre << endl;
        cout << "Year: " << perPtr->year << endl;
        cout << "Rating: " << perPtr->rating << endl;
        cout << "Synopsis: " << perPtr->synopsis << endl << endl;
        perPtr = perPtr->next;
    }
}


int main()
{
    MovieNode *head;
    int command; // IN - used to navigate menu and enter the while loop
    ifstream inFile; // IN - input file 
    ofstream outFile; // OUT - output file
    string fileIn; // IN - Name of the input file being used
    string fileOut; // OUT - Name of the output file
    string title;
    string genre;
    string lead;
    int year;
    int rating;
    string synopsis;

    command = -1;
    
    // Open file
    cout << "Which input file would you like (type d for default file)? ";
    getline(cin, fileIn);
    if (fileIn.compare("d") == 0)
    {
        fileIn = "InFile.txt";
        cout << "opening default file: " << fileIn << endl;
    }

    // saving outfile name
    cout << "Which output file would you like to use (type d for default file)? ";
    getline(cin, fileOut);
    if (fileOut.compare("d") == 0)
    {
        fileOut = "OFile.txt";
        cout << "Saving to default file: " << fileOut << endl;
    }
    inFile.open(fileIn);
    outFile.open(fileOut);

    // error checking
    if (!inFile)
    {
        cout << "Error opening file: " << fileIn << endl;
        exit(1); //terminate with error
    }
    head = Create(head); // importing data from file
    while (command!= 0)
        {
            cout << "\n\n\n1 - Output Entire List\n";
            cout << "2 - Title Search\n";
            cout << "3 - Genre Search\n";
            cout << "4 - Actor Search\n";
            cout << "5 - Year Search\n";
            cout << "6 - Rating Search (0-9)\n";
            cout << "0 - EXIT\n";
            cout << "Enter command: ";
            cin >> command;

            switch (command)
                {
                    case EXIT:
                    cout << "Exiting..." << endl;
                    break;

                    case OUTPUT:
                    Display(head);
                    break;
                    
                }
        }
    
    inFile.close();
    outFile.close();    
    return 0;
}