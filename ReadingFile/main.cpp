#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <filename>\n";
    return 0x1;
  }

  std::ifstream *file = new std::ifstream();

  file->open(argv[1], std::ios::in); // open file with in mode

  if (file->is_open()) {
    std::string data;

    // read file until eof is hit
    while (!file->eof()) {
      std::getline(*file, data);
      std::cout << data << std::endl;
    }
  } else {
    std::cerr << "Unable to open file \n";
  }

  file->close(); // close handle

  delete file;
  file = nullptr;
  return 0x0;
}