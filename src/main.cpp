#include "scanner.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cerr << "pascalc - \033[31merror\033[0m: no input file\n";
    return 1;
  }

  if (argc > 2) {
    std::cerr << "pascalc - \033[31merror\033[0m: too many arguments\n";
    return 1;
  }

  std::ifstream file(argv[1]);

  if (!file.is_open()) {
    std::cerr << "pascalc - \033[31merror\033[0m: failed to open input file\n";
    return 1;
  }

  // Reads the source code file into a string using an input stream buffer iterator,
  // which automatically closes when reaching EOF
  std::string src{(std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>()};

  file.close();

  Scanner scanner = Scanner(src);
  scanner.get_tokens();
  scanner.print_token_stream();

  return 0;
}
