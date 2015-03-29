// Author: Andy Yang
#include "song.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


void Song::fixTitle()
{
  // if title has "a or the"
  if (title.find("A ") == 0)
  {
    // fix it
    title.erase(0, 2);
    title.append(", A");
    return;
  }  // if title starts with "A"

  if (title.find("THE ") == 0)
  {
    title.erase(0, 4);
    title.append(", THE");
    return;
  }  // if title starts with "THE"
}  // fixTitle()


void Song::fixArtist()
{
  bool cap = true;

  for (string::iterator itr = artist.begin(); itr != artist.end(); itr++)
  {
    if (*itr == ' ')
    {
      cap = true;
      continue;
    }  // if next character should be capitalized

    if (cap)
      cap = false;
    else  // if not
      if (*itr >= 'A' && *itr <= 'Z') // if needs to be lowercase
        *itr += 'z' - 'Z';	// to set to lowercase
  }  // for all characters
}  // fixArtist()


void Song::fixAlbum()	// removes "CD+G"
{
  int loc = album.find(" CD+G");

  if (loc != -1)
    album.erase(loc);
}  // fixAlbum()


void Song::fixStrings()
{
  fixTitle();
  fixArtist();
  fixAlbum();
}  // fixString()


ostream& operator<<(ostream& os, const Song &rhs)
{
  cout << rhs.title << ':' << rhs.artist << ':' << rhs.album << endl;
  return os;
}  // operator<<()

istream& operator>>(istream& is, Song &rhs)
{
  string line;
  int startloc = 0, endloc = 0;
  getline(is, line);

  endloc = line.find("___");
  rhs.title = line.substr(0, endloc);
  endloc += 3;
  startloc = endloc;

  endloc = line.find("___", startloc);
  rhs.artist = line.substr(startloc, endloc - startloc);
  endloc += 3;
  startloc = endloc;

  endloc = line.find("___", startloc) + 3;
  startloc = endloc;

  rhs.album = line.substr(startloc);

  return is;
}  // operator>>()
