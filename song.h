// Author: Andy Yang
#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Song
{
protected:
  void fixTitle();
  void fixArtist();
  void fixAlbum();
public:
  string title, artist, album;
  void fixStrings();
  friend ostream& operator<<(ostream& os, const Song &rhs);
  friend istream& operator>>(istream& is, Song &rhs);
};  // class Song()

#endif
