#include "TokenReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost\tokenizer.hpp>
#include <boost\algorithm\string\case_conv.hpp>

using namespace std;
using namespace boost;

TokenReader::TokenReader(void)
{
}

vector<string> TokenReader::readTokensFromFile(string fileName)
{
  vector<string> tokens;
  ifstream file;
  file.open(fileName);
  if(file.rdstate() == file.failbit)
  {
    cout << "Failed to open file: " << fileName << endl;
    return tokens;
  }
  string line;
  while(std::getline(file, line))
  {
    string token;
    tokenizer<> tok(line);
    for(tokenizer<>::iterator i=tok.begin(); i!=tok.end();++i) {
      tokens.push_back(*i);
    }
  }
  file.close();
  return tokens;
}

vector<string> TokenReader::readAndLowerTokensFromFile(string fileName)
{
  vector<string> tokens = readTokensFromFile(fileName);
  for(vector<string>::iterator i = tokens.begin(); i != tokens.end(); i++)
  {
    to_lower(*i);
    cout << *i << endl;
  }
  return tokens;
}

TokenReader::~TokenReader(void)
{
}
