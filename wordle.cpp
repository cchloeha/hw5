#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateWords(
  const std::string& pattern,
  const std::string& floating,
  const std::set<std::string>& dict,
  std::string& current,
  size_t idx,
  std::set<std::string>& results
);



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    if(in.size() == 0U) {
      return results;
    }
    std::string current = in;
    generateWords(in, floating, dict, current, 0, results);
    return results;

}

// Recursive generator 
void generateWords(
  const std::string& pattern,
  const std::string& floating,
  const std::set<std::string>& dict, 
  std::string& current,
  size_t idx,
  std::set<std::string>& results
)
{
  // Base case: full-length word built 
  if(idx == pattern.size()) {
    if(!floating.empty()) return;
    if(dict.find(current) != dict.end()) {
      results.insert(current);
    }
    return;
  }
  // If this position is fixed, we must use that character 
  if(pattern[idx] != '-') {
    current[idx] = pattern[idx];
    generateWords(pattern, floating, dict, current, idx + 1, results);
    return;
  }
  size_t slotsLeft = pattern.size() - idx;
  size_t floatsLeft = floating.size();
  if(floatsLeft > slotsLeft) {
    return;
  }
  if(floatsLeft == slotsLeft) {
    for(size_t i = 0; i < floatsLeft; i++) {
      char c = floating[i];
      current[idx] = c;
      std::string newFloating = floating;
      newFloating.erase(i, 1);
      generateWords(pattern, newFloating, dict, current, idx + 1, results);
    }
    return;
  }

  for(size_t i = 0; i < floatsLeft; i++) {
    char c = floating[i];
    current[idx] = c;
    std::string newFloating = floating;
    newFloating.erase(i, 1);
    generateWords(pattern, newFloating, dict, current, idx + 1, results);

  }
  for(char c = 'a'; c <= 'z'; c++) {
    bool isFloating = false;
    for(char f : floating) {
      if(f == c) {
        isFloating = true;
        break;
      }
    }
    if(isFloating) continue;
    current[idx] = c;
    generateWords(pattern, floating, dict, current, idx + 1, results);
  }
}

// Define any helper functions here
