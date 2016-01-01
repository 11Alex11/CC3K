#include "utilities.h"

int string_to_int(const std::string& s)
{
  int i;
  std::stringstream ss(s);
  ss >> i;
  return i;
}

std::string int_to_string(int i)
{
  std::stringstream ss;
  ss << i;
  return ss.str();
}
