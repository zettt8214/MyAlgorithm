#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

vector<int> NaiveStringMatch(string text, string pattern);
vector<int> RabinKarpMatch(string text, string pattern);
vector<int> KmpMatch(string text, string pattern);