// Author: Andy Yang
#include "song.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const int song_artist = 1;
const int song_title = 2;
const int song_album = 3;
const int song_phrase = 4;
const int cmd_exit = 0;

const int sort_artist = 1;
const int sort_title = 2;

void searchBy(int searchType, vector<Song> list,
              vector<Song> &found, string data);
void sortBy(int sortType, vector<Song> &list);
bool isInputGood(int &choice, string &data);
// end of pseudo-header


void searchBy(int searchType, vector<Song> list,
              vector<Song> &found, string data)
{
  for (vector<Song>::iterator itr = list.begin(); itr != list.end();
       itr++)
  {
    bool addSong = false;

    switch(searchType)
    {
      case song_title : addSong = ((*itr).title == data); break;
      case song_artist : addSong = ((*itr).artist == data); break;
      case song_album : addSong = ((*itr).album == data); break;
      case song_phrase : addSong = ((int)(*itr).title.find(data) != -1);
                         break;
    }  // switch on searchType

    if (addSong)
      found.push_back(*itr);
  }  // for all songs in songList
}  // searchBy()

void sortBy(int sortType, vector<Song> &list)
{
  if (list.empty())
    return;

  for (vector<Song>::iterator enditr = list.begin(); enditr != list.end();
       enditr++)
  {
    for (vector<Song>::iterator itr = enditr; itr > list.begin(); itr--)
    {
      bool needSwap = false;

      switch (sortType)
      {
        case sort_artist: needSwap = ((*itr).artist > (*(itr--)).artist);
                                     break;
        case sort_title: needSwap = ((*itr).title > (*(itr--)).title);
                                    break;
      }  // switch on sortType

      vector<Song>::iterator nextitr = itr++;

      if (needSwap)
      {
        (*itr).title.swap((*nextitr).title);	// swaps strings
        (*itr).album.swap((*nextitr).album);	// effectively swapping
        (*itr).artist.swap((*nextitr).artist);	// songs
        needSwap = false;
      }  // swap needed
    }  // from right bound to beginning
  }  // for all elements
}  // sortBy();


bool isInputGood(int &choice, string &data)
{
  cout << endl
       << "Song Menu" << endl
       << "0. Done." << endl
       << "1. Search for Artist." << endl
       << "2. Search for Title." << endl
       << "3. Search for Album." << endl
       << "4. Search for title phrase." << endl
       << endl;
  cout << "Your choice: ";
  cin >> choice;

  if (choice == 0)
    return false;

  if (choice < 0 || choice > 4)
  {
    cout << "Your choice must be between 0 and 4." << endl
         << "Please try again." << endl << endl;
    return false;
  }  // if out of range

  cout << "Please enter the ";

  switch(choice)
  {
    case song_artist : cout << "artist's name: "; break;
    case song_title : cout << "title: "; break;
    case song_album : cout << "album: "; break;
    case song_phrase : cout << "phrase: "; break;
  }  // switch on choie

  cin.ignore(10, '\n');
  getline(cin, data);
  return true;
}  // isInputGood()


int main()
{
  ifstream inf("songs.txt");

  if (!inf)
    return 1;
  vector<Song> songList;

  while (inf.peek() >= 0)
  {
    Song input; inf >> input; input.fixStrings();
    songList.push_back(input);
  }  // while there are more input

  inf.close();
  int choice = 1;
  string data;

  while (choice != 0)
  {
    if (!isInputGood(choice, data))
      continue;
    vector<Song> found;
    searchBy(choice, songList, found, data);

    if (choice == song_title || choice == song_phrase)
      sortBy(sort_artist, found);
    else  // if sort by title needed (song_artist, song_album)
      sortBy(sort_title, found);

    for (vector<Song>::iterator itr = found.begin(); itr != found.end();
         itr++)
      cout << *itr;
  }  // while user wants more info

  return 0;
}  // main()
