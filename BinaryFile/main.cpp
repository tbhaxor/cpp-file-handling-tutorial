#include "student.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " <name> <age>\n";
    return 0x0;
  }

  std::ofstream *ofile = new std::ofstream();
  std::ifstream *ifile = new std::ifstream();

  ofile->open("student.dat", std::ios::binary | std::ios::trunc);

  // setup student object
  Student *student = new Student();
  student->setAge((unsigned short)std::stoul(argv[2]));
  student->setName(argv[1]);

  ofile->write(reinterpret_cast<char *>(student), sizeof(*student));
  ofile->close();

  ifile->open("student.dat", std::ios::binary);
  if (ifile->is_open()) {
    Student *s = new Student();
    while (!ifile->eof()) {
      ifile->read(reinterpret_cast<char *>(s), sizeof(Student));
      std::cout << s->whoami() << std::endl;
    }
  } else {
    std::cerr << "Unable to open file\n";
  }

  ifile->close();

  delete ifile;
  delete ofile;
  delete student;
  ifile = nullptr;
  ofile = nullptr;
  student = nullptr;

  return 0x0;
}