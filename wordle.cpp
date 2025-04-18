#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <vector>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


void wordleHelper(size_t n, string temp, multiset<char>& floating,
  const set<string>& dict, set<string>& results);


// Definition of primary wordle function
set<string> wordle(
  const string& in,
  const string& floating,
  const set<string>& dict)
{
    set<string> results;
    multiset<char> floatingSet;
    for (size_t i = 0; i < floating.length(); i++)
    {
      floatingSet.insert(floating[i]);
    }
    string temp = in;
    wordleHelper(0, temp, floatingSet, dict, results);
    return results;
}

void wordleHelper(size_t n, string temp, multiset<char>& floating,
  const set<string>& dict, set<string>& results)
{
    if (n > temp.length()) //word is complete
    {
      if (floating.size() == 0 && dict.find(temp) != dict.end())
        results.insert(temp);

      return;
    }
    else if (temp.length()-n < floating.size()) //not enough space to use up floating chars
    {
      return;
    }
    
    if (temp[n] != '-') //if given char, just move to next spot
    {
      wordleHelper(n+1, temp, floating, dict, results);
    }
    else
    {
      for (char c = 'a'; c <= 'z'; c++)
      {
        temp[n] = c;

        bool erased = false;
        multiset<char>::iterator it = floating.find(c);
        if (it != floating.end())
        {
          floating.erase(it);
          erased = true;
        }
        wordleHelper(n+1, temp, floating, dict, results);

        if (erased)
          floating.insert(c);
      }
    }
}
