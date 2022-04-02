#include <cstring>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " <filename> <text>\n";
    return 0x1;
  }

  std::ofstream *file = new std::ofstream();

  file->open(argv[1], std::ios::out); // open file with out mode

  if (file->is_open()) {
    (*file) << argv[2] << std::endl; // deref the pointer and write into file
  } else {
    std::cerr << "Failed to open file\n";
  }

  file->close(); // close the handle

  delete file;
  file = nullptr;
  return 0x0;
}