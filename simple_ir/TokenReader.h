#include <string>
#include <vector>

#pragma once
class TokenReader
{
public:
  TokenReader();
  static std::vector<std::string> readTokensFromFile(std::string fileName);
  static std::vector<std::string> readAndLowerTokensFromFile(std::string fileName);
  ~TokenReader(void);
};

