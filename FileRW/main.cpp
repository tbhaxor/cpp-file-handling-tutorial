#include <fstream>
#include <iostream>
#include <limits>
#include <string>

int main(void) {
  std::string opt;
  std::fstream *file = new std::fstream();

  // open file in append and read mode
  file->open("file.txt", std::ios::app | std::ios::in);
  if (!file->is_open()) {
    std::cerr << "Unable to open file\n";

    delete file;
    file = nullptr;
    return 0x0;
  }

  do {
    std::cout << "Menu\n(W)rite\n(R)ead\n(Q)uit\n> ";
    std::getline(std::cin, opt);

    if (opt == "w" || opt == "W") {
      // clear flags and set put cursor at eof
      file->clear();
      file->seekp(std::ios::end);

      std::string data;
      std::cout << "Enter string: ";
      std::getline(std::cin, data);
      *file << data << std::endl;
    } else if (opt == "r" || opt == "R") {
      // clear flag and set get cursor at begining of file
      file->clear();
      file->seekg(std::ios::beg);

      std::string data;

      // read until hit eof and print
      std::getline(*file, data);
      while (!file->eof()) {
        std::cout << data << std::endl;
        std::getline(*file, data);
      }
    }
  } while (opt != "q" || opt == "Q");

  file->close(); // close file handle

  delete file;
  file = nullptr;
  return 0x0;
}