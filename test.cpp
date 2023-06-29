#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>


int main(int argc, char** argv)
{
  std::string token;
  std::vector<std::string> tokens;
  std::vector<std::string> sylabells;
 
  std::string l("(C)V(C)|(C)CV|VC(C)");
  std::stringstream   line(l);

  // (1) get list of rules.
  while(getline(line, token, '|'))
  {
	tokens.push_back(token);
  }

  // (2) process each rule
  while(tokens.size() > 0)
  {
	std::string::size_type loc = -1;
	
	std::string first = tokens.at(0);                                  // get the first token
	tokens.erase(tokens.begin());                                      // erase first token

	if(std::string::npos != (loc = first.find('(')))
	{
	  std::string::size_type loc1 = -1;
	  loc1 = first.find(')');

	  std::string optVal = first.substr(loc+1, loc1-loc-1);            // get optional part

	  std::string p = first; p.replace(loc, loc1 - loc + 1, optVal);   // gen rule with opt part present
	  std::string a = first; a.replace(loc, loc1 - loc + 1, "");       // gen rule with opt part absent

	  // place in appropriate list...
	  p.find('(') == std::string::npos ? sylabells.push_back(p) : tokens.push_back(p);
	  a.find('(') == std::string::npos ? sylabells.push_back(a) : tokens.push_back(a);

	}
	else                                   // if there are no opts push onto rules
	{	
	  sylabells.push_back(first);

	}
  }

  // (3) trim each sylabel of white space....
  for (auto s : sylabells) {s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end()); }

  // (4) print out list of sylabell definitions....
  for (auto s : sylabells) {std::cout << "***"<< s << "***" << std::endl;}



	return 0;
}
