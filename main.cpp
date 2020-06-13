/*main.cpp*/

// Everardo Gutierrez
// Project Netflix Show and Movie LookUp
//  Program will read in file containing movies and shows from Netflix saved to a dataframe. User is then requested on how to
//  search the datafram based on a particular criteria entered.

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <regex>

#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "hashmap.h"

using namespace std;

//
// TVShow Structure
//
struct TVShow{
    long long int id;
    int release_year;
    string type, title, director, country;
    vector<string> cast;
    string date_added,rating,duration,list_in,description;
    TVShow(){
        id = 0;
    }
};

//
// Movie Structure
//
struct Movie{
    long long int id;
    int release_year;
    string type, title, director, country;
    vector<string> cast;
    string date_added,rating,duration,list_in,description;
    Movie(){
        id = 0;
    }
};

/*
    Function: isNumeric 
    Use regex to determine if string passed as parameter is an integer
    Parameters:
        s - string 
    Returns:
        boolean true | false
*/
bool isNumeric(string s){
    regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}

/*
    Function: displayCommands 
    Display commands available for user to enter
    Parameters:
        none
    Returns:
        void
*/
void displayCommands(){
    cout << "Available commands:" << endl;
    cout << "Enter a show or movie name (e.g. The Runner)" << endl;
    cout << "Enter a country (e.g. cUnited States)" << endl;
    cout << "Enter a rating (e.g rPG-13)" << endl;
    cout << "Enter a genre (e.g. gComedies)" << endl;
    cout << "Find movies by year (e.g. 2019)" << endl;
    cout << "Find movies past year, inclusive (e.g. >2019" << endl;
}

/*
    Function: searchCountry 
    Search for a particular country passed as parameter in the hash table
    for either shows or movies. Displays all the shows or movies that match
    the country passed.
    Parameters:
        command - string
        choice - string 
        movies - hashmap
        shows - hashmap 
    Returns:
        none
*/
void searchCountry(string command, string choice, hashmap<long long int, Movie>& movies, hashmap<long long int, TVShow>& shows){
    command = command.erase(0,1); // remove c from string to gain country
    Movie m;
    TVShow s;
    vector<string> mov; // vector to hold all our shows/movies that meet our criteria
    unordered_set<long long int> keys; // holds all the keys from the hashtable
    if(choice == "movie"){ // determine if we are searching for all movies or if all shows
        keys = movies.getKeys(); // grab all the keys from the hash table
        for(auto itr = keys.begin(); itr != keys.end(); itr++){ // loop through the keys
        bool found = movies.search(*itr, m, HashId); // search for the current key
        if(!found){ // if key not found go to the next key
            continue;
        }
        if(m.country.find(command) != string::npos){ // key found determine if it meets our conditions
            mov.push_back(m.title);
        }
        }
        cout << "Movies at your country request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){ // loop through the vector and display the movie title
            cout << "Movie: " << *i << endl;
        }
    }else{
        keys = shows.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = shows.search(*itr, s, HashId);
        if(!found){
            continue;
        }
        if(s.country.find(command) != string::npos){
            mov.push_back(s.title);
        }
        }
        cout << "Shows at your country request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Show: " << *i << endl;
        }
    }
}

/*
    Function: searchRating 
    Search for a particular rating passed as parameter in the hash table
    for either shows or movies. Displays all the shows or movies that match
    the rating passed.
    Parameters:
        command - string
        choice - string 
        movies - hashmap
        shows - hashmap 
    Returns:
        none
*/
void searchRating(string command, string choice, hashmap<long long int, Movie>& movies, hashmap<long long int, TVShow>& shows){
    command = command.erase(0,1);
    Movie m;
    TVShow s;
    vector<pair<string, string>> mov;
    unordered_set<long long int> keys;
    if(choice == "movie"){
        keys = movies.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = movies.search(*itr, m, HashId);
        if(!found){
            continue;
        }
        if(m.rating.find(command) != string::npos){
            mov.push_back(make_pair(m.title,m.rating));
        }
        }
        cout << "Movies at your rating request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Movie: " << i->first << " RATING: " << i->second << endl;
        }
    }else{
        keys = shows.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = shows.search(*itr, s, HashId);
        if(!found){
            continue;
        }
        if(s.rating.find(command) != string::npos){
            mov.push_back(make_pair(s.title,s.rating));
        }
        }
        cout << "Shows at your rating request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Show: " << i->first << " RATING: " << i->second << endl;
        }
    }
}

/*
    Function: searchGenre 
    Search for a particular genre passed as parameter in the hash table
    for either shows or movies. Displays all the shows or movies that match
    the genre passed.
    Parameters:
        command - string
        choice - string 
        movies - hashmap
        shows - hashmap 
    Returns:
        none
*/
void searchGenre(string command, string choice, hashmap<long long int, Movie>& movies, hashmap<long long int, TVShow>& shows){
    command = command.erase(0,1);
    Movie m;
    TVShow s;
    vector<string> mov;
    unordered_set<long long int> keys;
    if(choice == "movie"){
        keys = movies.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = movies.search(*itr, m, HashId);
        if(!found){
            continue;
        }
        if(m.list_in.find(command) != string::npos){
            mov.push_back(m.title);
        }
        }
        cout << "Movies at your genre request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Movie: " << *i << endl;
        }
    }else{
        keys = shows.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = shows.search(*itr, s, HashId);
        if(!found){
            continue;
        }
        if(s.list_in.find(command) != string::npos){
            mov.push_back(s.title);
        }
        }
        cout << "Shows at your genre request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Show: " << *i << endl;
        }
    }
}

/*
    Function: searchYear
    Search for a particular year passed as parameter in the hash table
    for either shows or movies. Displays all the shows or movies that match
    the year passed.
    Parameters:
        command - string
        choice - string 
        movies - hashmap
        shows - hashmap 
    Returns:
        none
*/
void searchYear(string command, string choice, hashmap<long long int, Movie>& movies, hashmap<long long int, TVShow>& shows){
    Movie m;
    TVShow s;
    vector<string> mov;
    int year;
    int ourYear = stoi(command);
    unordered_set<long long int> keys;
    if(choice == "movie"){
        keys = movies.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = movies.search(*itr, m, HashId);
        if(!found){
            continue;
        }
        year = m.release_year;
        if(year == ourYear){
            mov.push_back(m.title);
        }
        }
        cout << "Movies at your genre request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Movie: " << *i << endl;
        }
    }else{
        keys = shows.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = shows.search(*itr, s, HashId);
        if(!found){
            continue;
        }
        year = s.release_year;
        if(year == ourYear){
            mov.push_back(s.title);
        }
        }
        cout << "Shows at your genre request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Show: " << *i << endl;
        }
    }
}

/*
    Function: searchGreaterYear 
    Search for all years greater than and equal to the one passed as parameter in the hash table
    for either shows or movies. Displays all the shows or movies that match
    the year passed or are greater than.
    Parameters:
        command - string
        choice - string 
        movies - hashmap
        shows - hashmap 
    Returns:
        none
*/
void searchGreaterYear(string command, string choice, hashmap<long long int, Movie>& movies, hashmap<long long int, TVShow>& shows){
    command = command.erase(0,1);
    Movie m;
    TVShow s;
    vector<string> mov;
    int year;
    int ourYear = stoi(command);
    unordered_set<long long int> keys;
    if(choice == "movie"){
        keys = movies.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = movies.search(*itr, m, HashId);
        if(!found){
            continue;
        }
        year = m.release_year;
        if(year >= ourYear){
            mov.push_back(m.title);
        }
        }
        cout << "Movies at your genre request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Movie: " << *i << endl;
        }
    }else{
        keys = shows.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = shows.search(*itr, s, HashId);
        if(!found){
            continue;
        }
        year = s.release_year;
        if(year >= ourYear){
            mov.push_back(s.title);
        }
        }
        cout << "Shows at your genre request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Show: " << *i << endl;
        }
    }
}

/*
    Function: searchName 
    Search for a particular movei/show title passed as parameter in the hash table
    for either shows or movies. Displays all the shows or movies that match
    the movie/show title passed.
    Parameters:
        command - string
        choice - string 
        movies - hashmap
        shows - hashmap 
    Returns:
        none
*/
void searchName(string command, string choice, hashmap<long long int, Movie>& movies, hashmap<long long int, TVShow>& shows){
    Movie m;
    TVShow s;
    vector<string> mov;
    unordered_set<long long int> keys;
    if(choice == "movie"){
        keys = movies.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = movies.search(*itr, m, HashId);
        if(!found){
            continue;
        }
        if(m.title.find(command) != string::npos){
            mov.push_back(m.title);
        }
        }
        cout << "Movies at your genre request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Movie: " << *i << endl;
        }
    }else{
        keys = shows.getKeys();
        for(auto itr = keys.begin(); itr != keys.end(); itr++){
        bool found = shows.search(*itr, s, HashId);
        if(!found){
            continue;
        }
        if(s.title.find(command) != string::npos){
            mov.push_back(s.title);
        }
        }
        cout << "Shows at your genre request of " << command << endl;
        for(auto i = mov.begin(); i != mov.end();++i){
            cout << "Show: " << *i << endl;
        }
    }
}

/*
    Function: insertData 
    Read data from the file passed and create an instance of movie or show structure type.
    Instance is then inserted into the hash table based on the id that gets hashed.
    Parameters:
        fileName - string
        movies - hashmap
        shows - hashmap 
    Returns:
        boolean - true | false
*/
bool insertData(string fileName, hashmap<long long int, Movie>& movies, hashmap<long long int, TVShow>& shows){
    ifstream infile(fileName);
    string show_id, type, title, director, country;
    string cast;
    int movieCount = 0, showCount = 0;
    string date_added,release_year,rating,duration,list_in,description;
    if(!infile.good()){ // file could not be opened return false
        cout << "**Error: unable to open '" << fileName << "'..." << endl;
        return false;
    }
    char * pEnd;
    string line;
    getline(infile, line); // skip first line (column names)
    while(getline(infile, line)){ // read each line from the line
        stringstream s(line);
        getline(s, show_id, ',');
        getline(s, type, ',');
        getline(s, title, ',');
        getline(s, director, ',');
        getline(s, cast, ',');
        getline(s, country, ',');
        getline(s, date_added, ',');
        getline(s, release_year, ',');
        getline(s, rating, ',');
        getline(s, duration, ',');
        getline(s, list_in, ',');
        getline(s, description, ',');
        
        const char* arr = show_id.c_str();
        long long int lid = strtoll(arr, &pEnd, 10); // conversion to id
        if(type == "Movie"){ // movie 
            // create instance of movie and set its values to the ones read
            Movie m; 
            m.id = lid;
            m.type = type;
            m.title = title;
            m.director = director;
            m.cast.push_back(cast);
            m.country = country;
            m.date_added = date_added;
            m.release_year = stoi(release_year);
            m.rating = rating;
            m.duration = duration;
            m.list_in = list_in;
            m.description = description;
            // insert movie into the hash table 
            movies.insert(m.id, m, HashId);
            //update number of movies read
            movieCount++;
        }else{ // tv show
            // create instance of tv show and set its values to the ones read
            TVShow t;
            t.id = lid;
            t.type = type;
            t.title = title;
            t.director = director;
            t.cast.push_back(cast);
            t.country = country;
            t.date_added = date_added;
            t.release_year = stoi(release_year);
            t.rating = rating;
            t.duration = duration;
            t.list_in = list_in;
            t.description = description;
            // insert tv show into the hash table 
            shows.insert(t.id, t, HashId);
            showCount++; //update number of shows read
        }
    }
    // Display the number of movies and shows read from the file
    cout << "# of movies: " << movieCount << endl;
    cout << "# of TV Shows: " << showCount << endl;
    return true;
}

int main(){
    const int N = 5000;
    hashmap<long long int, Movie> movies(N);
    hashmap<long long int, TVShow> shows(N);
    string fileName = "netflix_titles.csv"; 
    cout << "**Netflix Movie and TV Show Lookup**" << endl;
    cout << "Reading " << fileName << endl;
    
    bool success = insertData(fileName, movies, shows);
    if(!success){ // determine if file can be read 
        cout << "No Data, file not found" << endl;
        return 0;
    }

    string command;
    string choice;
    cout << "What you feeling? Show or movie?";
    getline(cin, choice); // read in users decision on rather show or movie
    cout << "Please enter a command, help, or #> ";
    getline(cin, command); // read in users desired command
    while(command != "#"){ // determine if user has asked to quit searching
        if(command[0] == 'c'){ // user wants to search based on country
            searchCountry(command, choice, movies, shows);
        }else if(command[0] == 'r'){ // user wants to search based on a particular rating
            searchRating(command, choice, movies, shows);
        }else if(command[0] == 'g'){ // user wants to search based on genre
            searchGenre(command, choice, movies, shows);
        }else if(isNumeric(command)){ // user wants to search by year
            searchYear(command, choice, movies, shows);
        }else if(command[0] == '>'){ // user wants to search for years greater than or equal to the one entered
            searchGreaterYear(command, choice, movies, shows);
        }else if(command.substr(0,4) == "help"){ // display commands available
            displayCommands();
        }else{ // default will look for movie | show title 
            searchName(command, choice, movies, shows);
        }
        // request users input once again
        cout << endl;
        cout << "What you feeling? Show or movie?";
        getline(cin, choice);
        cout << "Please enter a command, help, or #> ";
        getline(cin, command);
    }
    return 0;
}