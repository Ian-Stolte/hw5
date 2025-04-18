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


void wordleHelper(size_t n, string temp, vector<int>& floating, int floatCount,
  const set<string>& dict, set<string>& results);


// Definition of primary wordle function
set<string> wordle(
  const string& in,
  const string& floating,
  const set<string>& dict)
{
    set<string> results;
    /*multiset<char> floatingSet;
    for (size_t i = 0; i < floating.length(); i++)
    {
      floatingSet.insert(floating[i]);
    }*/
    vector<int> floatingCounts(26, 0);
    for (char c : floating) {
        floatingCounts[c - 'a']++;
    }
    int totalFloats = floating.length();
    string temp = in;
    wordleHelper(0, temp, floatingCounts, totalFloats, dict, results);
    return results;
}

void wordleHelper(size_t n, string temp, vector<int>& floating, int floatCount,
  const set<string>& dict, set<string>& results)
{
    if (n > temp.length()) //word is complete
    {
      if (floating == vector<int>(26, 0))
        if (dict.find(temp) != dict.end())
          results.insert(temp);

      return;
    }
    
    if (temp.length()-n < floatCount) //not enough space to use up floating chars
    {
      return;
    }
    
    if (temp[n] != '-') //if given char, just move to next spot
    {
      wordleHelper(n+1, temp, floating, floatCount, dict, results);
    }
    else
    {
      for (char c = 'a'; c <= 'z'; c++)
      {
        temp[n] = c;
        bool usedFloating = false;
        /*multiset<char>::iterator it = floating.find(c);
        if (it != floating.end())
        {
          floating.erase(it);
          erased = true;
        }*/
        if (floating[c - 'a'] > 0)
        {
          floating[c - 'a']--;
          floatCount--;
          usedFloating = true;
        }
        wordleHelper(n+1, temp, floating, floatCount, dict, results);

        if (usedFloating)
        {
          floatCount++;
          floating[c - 'a']++;
          //floating.insert(c);
        }
      }
    }
}
