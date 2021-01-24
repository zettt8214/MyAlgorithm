/**
* @file			graph.h
* @author		tanghf
* @date			2021-01-24
* @version		V1.0
* @copyright    Copyright (c) 2021
*/

#ifndef STR_MATCH_H_
#define STR_MATCH_H_
#include <string>
#include <vector>
using std::string;
using std::vector;

vector<int> NaiveStringMatch(string text, string pattern);
vector<int> RabinKarpMatch(string text, string pattern);
vector<int> KmpMatch(string text, string pattern);

#endif