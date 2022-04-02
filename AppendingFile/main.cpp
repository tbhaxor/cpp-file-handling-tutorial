#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " <filename> <text>\n";
    return 0x0;
  }

  // instantiate input and output file streams
  std::ofstream *ofile = new std::ofstream();
  std::ifstream *ifile = new std::ifstream();

  ofile->open(argv[1], std::ios::app); // open with append mode

  // safely write data into file
  if (ofile->is_open()) {
    *ofile << argv[2] << std::endl;
  } else {
    std::cerr << "Unable to open the file \n";
    ofile->close();
    return 0x0;
  }

  ofile->close(); // close output file handle

  ifile->open(argv[1], std::ios::in); // open file in read mode

  // safely read data from the file
  if (ifile->is_open()) {
    std::string data;
    while (!ifile->eof()) {
      std::getline(*ifile, data);
      std::cout << data << std::endl;
    }
  } else {
    std::cerr << "Unable to open the file \n";
  }

  ifile->close(); // close input file handle

  delete ofile;
  delete ifile;
  ofile = nullptr;
  ifile = nullptr;
  return 0x0;
}