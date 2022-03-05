// File name: PA#2
// Author: Michael Johnson
// Collaborators: Carson Holland, Mon Villafuerte Langford
// Date: 09/23/2020
// Assignment Number: 2
// C S 2308 Fall 2020

// This program allows a user to interact with a movie database that contains
// the name, date of release, and user rating of each movie. The user has the
// ability to sort the movies by date of release and rating, by ID number, and
// looking up a release date given a movie name.

#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;
const int NUM_MAX = 100; // max number of movies
struct Movie {
    int id;
    string  name;
    string releaseDate;
    double rating; };

// readMovies is a function that reads the movies from the input file into the
// movie struct.

void readMovies(ifstream& inputFile, Movie movies[], int& size)// ifstream has an & because it is modifying stuff within the file.
 {
    string releaseDate, name;
    size = 0;

    while (inputFile >> movies[size].id)
    {
        inputFile >> ws;// skips ws
        getline(inputFile, movies[size].name); // getline does not skip ws
        inputFile >> ws;
        getline(inputFile,movies[size].releaseDate);
        inputFile >> ws;
        inputFile >> movies[size].rating;
        size++;
    }
}

// sortByDateRating sorts the movie list from older to newer and if two movies
// have the same release date they will be sorted by rating in descending order.

 void sortByDateRating (Movie movies[], int size)
    {
        bool swapped;
        Movie temporary;
        do {
            swapped = false;
            for (int i = 0; i <(size-1); i++)
                {

                 if (movies[i].releaseDate == movies[i+1].releaseDate &&
                     movies[i].rating < movies[i+1].rating)
                 {
                     temporary = movies[i];
                     movies[i] = movies[i+1];
                     movies[i+1] = temporary;
                     swapped = true;
                 }

                 else if (movies[i].releaseDate > movies[i+1].releaseDate)
                    {
                    temporary = movies[i];
                    movies[i] = movies[i+1];
                    movies[i+1] = temporary;
                    swapped = true;
                    }

                 }}while (swapped);

        cout << left
             << setw(3) << "ID"
             << setw(26) << "Name"
             << setw(12) << "Date"
             << "Rating"
             << endl;

        for (int i = 0; i< size; i++)
            {
         cout << fixed << setprecision(1);
         cout << left
              << setw(3) << movies[i].id
              << setw(26) << movies[i].name
              << setw(12) << movies[i].releaseDate
              << movies[i].rating
              << endl;
            }
        }
// linearSearchByName allows the user to input a name(targetName) and search
// the movie data base for it where the function will return the movie's release
// date. position is the index location when starting the search.

int linearSearchByName(Movie movies[], int size, string targetName)
    {
           int position = -1;
           int index = 0;
           bool found = false;

           while (index < 6 && !found)
           {
               if (movies[index].name == targetName)
               {
                   found = true;
                   position = index;
               }
               index++;
           }

        return position;
    }

// sortById allows the user to sort the movies by id in ascending order.

void sortById(Movie movies[], int size)
{
    int middle, mid;
    for (int start = 0; start <size; start ++)
    {
        middle = start;
        mid = movies[middle].id;

        for (int i = start + 1; i < size; i++)
        {
            if (movies[i].id < mid)
            {
                mid = movies[i].id;
                middle = i;
            }
        }
        swap(movies[middle], movies[start]);
    }
    cout << left
         << setw(3) << "ID"
         << setw(26) << "Name"
         << setw(12) << "Date"
         << "Rating"
         << endl;
     for (int i =0; i < size; i++)
     {
         cout << left <<
         fixed << setprecision(1)
         << setw(3) << movies[i].id
         << setw(26) << movies[i].name
         << setw(12) << movies[i].releaseDate
         << movies[i].rating
         << endl;
     }
}

// sorts the resets the order of movies for the sort by search by id function.

void sortById2(Movie movies[], int size)
{
    int middle, mid;
    for (int start = 0; start <size; start ++)
    {
        middle = start;
        mid = movies[middle].id;

        for (int i = start + 1; i < size; i++)
        {
           if (movies[i].id < mid)
            {
                mid = movies[i].id;
                middle = i;
            }
        }
        swap(movies[middle], movies[start]);
   }}

// displayMovies outputs the movies to the console.

void displayMovies(Movie movies[], int size)
{

    cout << left
         << setw(3) << "ID"
         << setw(26) << "Name"
         << setw(12) << "Date"
         << "Rating"
         << endl;
     for (int i =0; i < size; i++)
     {
         cout << left <<
         fixed << setprecision(1)
         << setw(3) << movies[i].id
         << setw(26) << movies[i].name
         << setw(12) << movies[i].releaseDate
         << movies[i].rating
         << endl;
}    }

// binarySearchById locates and indexes a movie. If the movie does not exist
// the function will return a -1. target id is the user inputed integer.

int binarySearchById(Movie movies[], int size, int targetid)
{
    int first = 0,
        last = size -1,
        middle,
        position = -1;
    bool found = false;

    while (!found && first <= last)
    {
        middle = (first + last ) / 2;
        if (movies[middle].id == targetid)
        {
            found = true;
            position = middle;
        }
        else if (movies[middle].id > targetid)
            last = middle -1;
        else
            first = middle +1;
    }
    return position;
}

// displayMenu prints the menu to the console.

void displayMenu(Movie movies[], int choice, int size, string targetName,
                  int start, int targetid){
    do {
    cout << "\nMenu\n"
         << "1. Display movies sorted by id\n"
         << "2. Display movies sorted by release date, then rating\n"
         << "3. Lookup a release date given a name\n"
         << "4. Lookup a movie by id\n"
         << "5. Quit the Program\n"
         << "Enter your choice:\n";
    cin >> choice;

    while (choice <1 || choice > 5)
    {
        cout << "Please enter 1, 2, 3, 4, or 5:" << endl;
        cin >> choice;
    }
         switch (choice)
        {
            case 1:
                sortById (movies, size);
                break;

            case 2:
                sortByDateRating (movies, size);
                break;

            case 3:
                {
                cout << "Please enter a movie name:" << endl;
                cin >> ws;
                getline (cin, targetName);

                int res = linearSearchByName (movies, size, targetName);

                if (res == -1)
                    cout << "No movie found with name: " << targetName << endl;

                else
                    cout << "Release date of '" << targetName << "'"
                         << " is " << movies[res].releaseDate << endl;
                }
                break;

            case 4:
                {
                    sortById2(movies, size);
                    cout << "Please enter a movie id:" << endl;
                    cin >> targetid;
                    int res;
                    res = binarySearchById( movies, size, targetid);

                    if (res == -1)
                        cout << "No movie found with id: " << targetid << endl;
                    else
                    {
                        cout << left
                             << setw(3) << "ID"
                             << setw(26) << "Name"
                             << setw(12) << "Date"
                             << "Rating"
                             << endl;

                        cout << fixed << setprecision(1)
                             << left
                             << setw(3) << movies[res].id
                             << setw(26) << movies[res].name
                             << setw(12) << movies[res].releaseDate
                             << movies[res].rating << endl;
                    }
                }
                break;
            case 5:
                cout << "Exiting the program..." << endl;
        }

    } while(choice !=5);

}

int main()
{
    ifstream inputFile;
    inputFile.open("movies.txt");
    int choice;
    int size;
    string targetName;
    int start = 0;
    int targetid;

    Movie movies[NUM_MAX];

    readMovies (inputFile, movies, size);

    displayMenu (movies, choice, size, targetName, start, targetid);

    inputFile.close();
    return 0;
}




