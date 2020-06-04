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

bool isNumeric(string s){
    regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}

void displayCommands(){
    cout << "Available commands:" << endl;
    cout << "Enter a show or movie name (e.g. The Runner)" << endl;
    cout << "Enter a country (e.g. cUnited States)" << endl;
    cout << "Enter a rating (e.g rPG-13)" << endl;
    cout << "Enter a genre (e.g. gComedies)" << endl;
    cout << "Find movies by year (e.g. 2019)" << endl;
    cout << "Find movies past year, inclusive (e.g. >2019" << endl;
}

void searchCountry(string command, string choice, hashmap<long long int, Movie>& movies, hashmap<long long int, TVShow>& shows){
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
        if(m.country.find(command) != string::npos){
            mov.push_back(m.title);
        }
        }
        cout << "Movies at your country request of " << command << endl;
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

bool insertData(string fileName, hashmap<long long int, Movie>& movies, hashmap<long long int, TVShow>& shows){
    ifstream infile(fileName);
    string show_id, type, title, director, country;
    string cast;
    int movieCount = 0, showCount = 0;
    string date_added,release_year,rating,duration,list_in,description;
    if(!infile.good()){
        cout << "**Error: unable to open '" << fileName << "'..." << endl;
        return false;
    }
    char * pEnd;
    string line;
    getline(infile, line);
    while(getline(infile, line)){
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
        long long int lid = strtoll(arr, &pEnd, 10);
        if(type == "Movie"){ // movie 
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
            movies.insert(m.id, m, HashId);
            movieCount++;
        }else{ // tv show
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
            shows.insert(t.id, t, HashId);
            showCount++;
        }
    }
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
    if(!success){
        cout << "No Data, file not found" << endl;
        return 0;
    }
    string command;
    string choice;
    cout << "What you feeling? Show or movie?";
    getline(cin, choice);
    cout << "Please enter a command, help, or #> ";
    getline(cin, command);
    while(command != "#"){
        if(command[0] == 'c'){
            searchCountry(command, choice, movies, shows);
        }else if(command[0] == 'r'){
            searchRating(command, choice, movies, shows);
        }else if(command[0] == 'g'){
            searchGenre(command, choice, movies, shows);
        }else if(isNumeric(command)){
            searchYear(command, choice, movies, shows);
        }else if(command[0] == '>'){
            searchGreaterYear(command, choice, movies, shows);
        }else if(command.substr(0,4) == "help"){
            displayCommands();
        }else{ // default will look for name 
            searchName(command, choice, movies, shows);
        }
        cout << endl;
        cout << "What you feeling? Show or movie?";
        getline(cin, choice);
        cout << "Please enter a command, help, or #> ";
        getline(cin, command);
    }
    return 0;
}