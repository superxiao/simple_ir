#include <iostream>
#include "TokenReader.h"

using namespace std;

int main(int argc, char** argv)
{
  
  
  TokenReader::readAndLowerTokensFromFile("../Reuters/10.html");

  int i;
  cin >> i;
  return 0;
}