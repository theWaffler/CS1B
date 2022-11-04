#include <iostream>
#include <fstream>
#include <limits>
#include <string>
//#include <iomanip>
//#include functions.h
//#include myheader.h

/*****************************************************************
* Searching Linked List
* Program that allows a yser to track/search their DVD collection. 
* Uses an input file that contains the list of DVD with the following attributs:
* Title, Leading actor/actress, supporting actor, alternate genre, year rating and synopsis
* _______________________________________________________________
* INPUT:
* fileIn; // IN - Name of the input file being used
* sTitle; // IN - used to search based on title
* sGenre; // IN - used to search based on genre
* sLead; // IN - used to search based on lead
* sYear; // IN - used to search based on year
* rating; // IN - used to search based on rating
* OUTPUT:
* fileOut; // OUT - Name of the output file
*
******************************************************************/

//original is in replit CS1B_AS03
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

enum command {EXIT = 0, OUTPUT = 1, TITLE = 2, GENRE = 3, LEAD = 4, YEAR = 5, RATING = 6};

//functions

/*
 * This function will load the default file (inFile.txt) that contains the movie details
 * it will place the data in the apporiate fields:
 * Title, lead, support, genre, altGenre, year, rating and the synopsis 
 */
MovieNode *Create(MovieNode *head)
{
    //bool found;    // OUT - check to see if the element is in the list
    MovieNode* perPtr; // OUT - pointer to the element
    ifstream inFile;
    inFile.open("InFile.txt");
    perPtr = new MovieNode; // Makes new node

    while (inFile && perPtr != NULL)
    {
        getline(inFile, perPtr->title);
        getline(inFile, perPtr->lead);
        getline(inFile, perPtr->support);
        getline(inFile, perPtr->genre);
        getline(inFile, perPtr->altGenre);
        inFile>>perPtr->year;
        inFile.ignore(1000, '\n'); // clears buffer
        inFile>>perPtr->rating;
        inFile.ignore(1000, '\n'); // clears buffer
        getline(inFile, perPtr->synopsis);
        inFile.ignore(1000, '\n'); // clears buffer
        perPtr->next = head; // advances the pointer and assigns it to head
        head = perPtr; // pointer is now at the front of the node
        perPtr = new MovieNode; // makes new node
    }

    delete perPtr; // deletes the pointer
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
    delete perPtr; // deletes pointer
}

/**
 * This function is to search the list of movies included in the inFile.txt
 * function does not return anything to main 
 */
void Search(MovieNode *head, ostream &outFile)
{
  string searchTitle; // INPUT - the name to be searched - INPUT
  MovieNode *search; // OUTPUT - the pointer to search the list - OUTPUT
  search = head; // pointer to the first node

  if (search == NULL)
  {
      cout << "Can't search an empty list! " << endl;
  }
  else 
  {
    search = head;
    cout << "What movie would you like to search for? " << endl;
    cin.ignore(1000, '\n');
    getline(cin, searchTitle);

    cout << "Searching for " << searchTitle << "..." << endl << endl;
    while (search != NULL) 
    {
      if (search->title.compare(searchTitle) == 0) 
      {
          cout << "Found the movie " << searchTitle << " !" << endl;
          outFile << "Movie: "<< search->title << endl;
          outFile << "Leading Actor/Actress:" << search->lead << endl;
          outFile << "Supporting Actor/Actress: " << search->support << endl;
          outFile << "Genre " << search->genre << endl;
          outFile << "Sub Genre: " << search->altGenre << endl;
          outFile << "Release date: " << search->year << endl;
          outFile << "Rating: " << search->rating << endl;
          outFile << "Synopsis: " << endl << search->synopsis << endl;
          break;
      } else
      {
        search = search->next;
      }
      if (search == NULL)
        cout << "Sorry, the movie " << searchTitle << " was not found." << endl;
    }
    search = NULL;
    delete search;
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
    bool titleCheck; // OUT - used to check if movie title is in the list
    string stitle; // IN - the movie title the user inputed
    string sGenre; // IN - used to search based on genre
    string sLead; // IN - used to search based on lead
    int sYear; // IN - used to search based on year
    int rating; // IN - used to search based on rating

    command = -1;
    
    // Open file
    cout << "Which input file would you like (type d for default file)? ";
    getline(cin, fileIn);
    if (fileIn.compare("d") == 0)
    {
        fileIn = "InFile.txt";
        cout << "opening default file: " << fileIn << endl;
        head = Create(head); // calling create function to importing data from file
    }

    // saving outfile name
    cout << "Which output file would you like to use (type d for default file)? ";
    getline(cin, fileOut);
    if (fileOut.compare("d") == 0)
    {
        fileOut = "OFile.txt";
        cout << "Saving to default file: " << fileOut << endl;
    }

    // opening fileIn and fileOut
    inFile.open(fileIn);
    outFile.open(fileOut);

    // error checking
    if (!inFile)
    {
        cout << "Error opening file: " << fileIn << endl;
        exit(1); //terminate with error
    }

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
                    /*
                     * Will exit the program 
                    */
                    case EXIT:
                    cout << "Exiting..." << endl;
                    break;

                    case OUTPUT:
                    /*
                     * Calls on the function Display(MovieNode *head) 
                     * function will display the loaded inFile.txt for the user
                    */
                    Display(head);
                    break;

                    case TITLE:
                    /*
                     * If title of the movie is found - output move to Ofile.txt
                     * cout << "Found the movie " << title << " !"
                     * If title of the movie is NOT found
                     * cout << "Sorry, the movie " << title << " was not found." 
                     */ 
                    Search(head, outFile);
                    break;

                    case GENRE:
                    /*
                     * bool function (T/F)
                     * return true - if GENRE of movie is found - output movie to Ofile.txt
                     *             - cout how many movies that match the genre searched for
                     * return false - if GENRE of movie is NOT found 
                     *              - cout << "Sorry, no movies for the genre " << genre << were found
                     *  
                    */
                    break;

                    case YEAR:
                    /**
                     * bool function (T/F)
                     * return true - YEAR of movie is found - output movie to Ofile.txt
                     *             - cout how many movie that match the year searched for
                     *             - cout << "Found " << year << " for the year " << 
                     *  return false - YEAR of movie NOT found
                     */
                    break;

                    
                }
        }
    
    inFile.close();
    outFile.close();    
    return 0;
}