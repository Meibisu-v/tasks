#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
std::vector<int> prefix_function(std::string str)
{
  std::vector<int> pi(str.length());
  for (size_t i = 1; i < str.length(); ++i)
  {
    size_t k = pi[i - 1];
    while (k > 0 && str[i] != str[k])
    {
      k = pi[k - 1];
    }
    if (str[i] == str[k])
    {
      ++k;
    }
    pi[i] = k;
  }
  return pi;
}

int main(int argc, char *argv[])
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string input;
  //
  FILE *file_in_storage = fopen(argv[1], "rb");
  FILE *some_kind_file = fopen(argv[2], "rb");

  int bufsize = 4096;
  int ch_read_some_kind = 1;
  while (ch_read_some_kind > 0)
  {
    char buf_some_kind[4096];
    ch_read_some_kind = fread(buf_some_kind, 1,
                              bufsize, some_kind_file);
    if (ch_read_some_kind <= 0)
    {
      break;
    }
    input += buf_some_kind;
  }
  //
  std::string pattern;
  char *file_name = argv[2];
  while (1)
  {
    char *buf_storage = NULL;
    size_t ch_read_storage = 0;
    if (getline(&buf_storage, &ch_read_storage, file_in_storage) == -1)
    {
      break;
    }
    pattern += buf_storage;
  }
  std::string pattern_str = pattern + "#" + input;

  std::vector<int> prefix_function_values = prefix_function(pattern_str);
  bool found = false;
  for (size_t i = 0; i < prefix_function_values.size(); ++i)
  {
    if (prefix_function_values[i] == pattern.length())
    {
      std::cout << i - 2 * pattern.length() << '\n';
      found = true;
      break;
    }
  }
  if (!found) {
    std::cout << "pattern not found\n";
  }
  return 0;
}