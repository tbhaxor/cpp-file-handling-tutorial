# File Handling in C++

You have been working with data in the program and struggling with saving its states across multiple restarts. Yeah, I know that is temporary and will be gone as the program exists. In this post, I will teach you how you can use C++ file handling and save not only text data into it but also binary data like Class or Struct.

You can clone the repository for all the snippets and source code used in this tutorial https://github.com/tbhaxor/cpp-file-handling-tutorial.


## Why do you need File Handling Anyway?

The program state gets vanished when it is exited or the functions go out of scope during execution. Sometimes it's required to have the states for future execution.

Take the example of a game, you don't play it continuously. Saving the same and loading it later is very basic. I had first seen this in the Project IGI game and then Age of Empires. Nowadays multiplayer games are getting popular and they use databases to store this information.

That's a great idea to use databases. So why not use the database, it can be shared easily. Let me tell you that there is no different magic going on there, DBMS uses files to store the data. So it boils down to file handling.


## Getting Started with File Handling

There are and will be 2 types of operation in the file: Read file will allow you to retrieve the content and write file will allow you to put the content into the file using the current stream. A stream is basically a channel that carries your data from/to the file.

[`std::ifstream`](https://www.cplusplus.com/reference/fstream/ifstream/) class is used to open the file in reading mode and [`std::ofstream`](https://www.cplusplus.com/reference/fstream/ofstream/) is used to open the file in the write mode.

These classes provide different methods and properties as an abstraction to deal with files, or I would say even the large files.

### Text File vs Binary File

There are two types of files: Human readable (or text) and human non-readable (binary).

It is easy to determine whether a file is a text or binary: If you open a file in a text editor (let's assume notepad or vscode), it will show all the characters and you can pronounce them. They might or might not make sense, but it's not required here. This file is a **text file**. If you are unable to pronounce any character, then that file is a **binary file**.


> **Note** A binary file can contain a few readable characters as well, and that is ok.

|Text File|Binary File|
|:----:|:----:|
|![Text File](https://i.imgur.com/styO2fJ.png)|![Binary File](https://i.imgur.com/lqVstpt.png)|

### What is EOF

While seeing the file format and the number of total bytes, we can determine that there are {% katex inline %} n {% endkatex %} bytes in the file that can be read, but how does an opened stream will know in general? EOF is also known as [End-of-File](https://en.wikipedia.org/wiki/End-of-file) in computing. It is a condition or a notification to the file reader that tells no more retrieve more information from the file and seems like it is ended. 

When you try to read a file and it is failed, both _failed_ and _eof_ bits are set in the error flags. You can use [`.eof()`](https://www.cplusplus.com/reference/ios/ios/eof/) method to get this information.

So when does this bit set? An EOF bit is set after the ifstream reader tried to read the contents from the file and fails while the stream is still good (there is no error while performing I/O operations). So at least in the case of an ifstream, it waits for the OS to tell it that there's no more data <sup>[read more](https://www.reddit.com/r/cpp_questions/comments/ty1hiz/comment/i3ppceo/?utm_source=share&utm_medium=web2x&context=3)</sup>

> This is not only used for files but also streams and sockets

Programmatically, it will look like the following

```cpp
std::cout << ifile->bad() << " " << ifile->eof() << " " 
          << ifile->fail();

// 0 1 1
```

## Writing into the File

Enough talking, let's start by writing a text content into the file using `std::ofstream`. Before all of that, you need to instantiate the ofstream and open the file:

```cpp
std::ofstream *file = new std::ofstream();
file->open("file.txt", std::ios::out); 
```

> You can use `std::ofstream file; // w/o pointer` as well, but I prefer pointers. 

The [`.open()`](https://www.cplusplus.com/reference/fstream/ifstream/open/) function, as it says, open the file with name (_first argument_) and the mode (_second argument_). 

I will discuss different modes with you as we proceed, `std::ios::out` mode is used to tell the function, that opens the file in write mode, overwrite the contents of it if it exists or create a new one.

Now it's time to write into the file stream using the left shift operator [`<<`](https://www.cplusplus.com/reference/ostream/ostream/operator%3C%3C/). This will format all your data into `char*` before writing.

```cpp
(*file) << "Hello World" << std::endl;
```

Since we are using a pointer variable, therefore it is required to dereference the file handle to access the `<<` operator from the `std::ofstream` object stored.

## Reading from the File

Reading is pretty simple and uses `std::ifstream` and `>>` operator with `std::ios::in` mode.

```cpp
std::ifstream *file = new std::ifstream();
file->open(argv[1], std::ios::in);
```

For reading files in text mode, there is only one option [`std::ios::in`](https://www.cplusplus.com/reference/ios/ios_base/openmode/?kw=openmode)

```cpp
std::string data;
(*file) >> data;
std::cout << data << std::endl; // Hello\n
```


### Reading until line end (eol)

When you write a file with `<<` it formats whitespaces and streams that to the file, but while reading the content, it will stop at either EOF or the first whitespace character hit. 

EOL or End-of-line is defined by the character `\n` or `\r\n` and is considered as the whitespace. So if there are multiple lines, you can use the [`std::getline()`](https://www.cplusplus.com/reference/string/string/getline/) function.

```cpp
std::getline(*file, data);
std::cout << data << std::endl; // Hello World\n
```

## Check Whether the File is Open or Not

Till now we are believing that the file exists and is ready for any I/O operation, but what if the condition is otherwise? What if it failed to open? Will it throw an error?

The answer to the question is, **NO**. It will not throw error but the RW will not work. You can use [`std::ifstream::is_open()`](https://www.cplusplus.com/reference/fstream/ifstream/is_open/) or [`std::ofstream::is_open()`](https://www.cplusplus.com/reference/fstream/ofstream/is_open/). The functions returns boolean value, so if the file is actually opened successfully, it will return true.

```cpp
if (file->is_open()) {
     // do the rest actions here
} else {
    std::cout << "Unable to open file\n";
}
```

## Closing file handle

When you are done with the file operations, it is recommended to close the file handle which will dispose of the file stream after writing any pending sequence of characters and clearing the buffer for both input and output streams.

For this you can use [`std::ofstream::close()`](https://www.cplusplus.com/reference/fstream/ofstream/close/) or [`std::ifstream::close`](https://www.cplusplus.com/reference/fstream/ifstream/close/).

```cpp
file->close();
```

If the file is not successfully opened, the function will fail and set the `failbit` flag.

## Appending into the Existing File

What if you want to append the data into the file without losing old content. In the `ios::out`, it overwrites the file and reading the content of files, appending in memory and then writing to a file doesn't seem to be a space and time-efficient solution. 

There is another mode of opening the file that you can use in place of `ios::out`, which is append mode `ios::app`. This will allow you to write from the end of the file to the size of the data. 

When you choose to open the file with append mode, the put cursor of the handle is set at the end of the file.

```cpp
file->open(argv[1], std::ios::app);
```

## Storing Class Object in the File

So far you have seen me dealing with the text file, but in the real world, there are more than binary files with the custom format, like Zip archives, PDF files and other document files. 

To open the file in binary mode, you need to specify `std::ios::binary` mode in the `open()` method of `std::ifstream` or `std::ofstream`.

```cpp
in_file->open("file.bin", std::ios::binary | std::ios::in);

out_file->open("file.bin", std::ios::binary | std::ios::out);
```

For reading and writing, you must use [`std::ifstream::read()`](https://www.cplusplus.com/reference/istream/istream/read/) and [`std::ofstream::write()`](https://www.cplusplus.com/reference/ostream/ostream/write/) because the binary file saves the raw bytes and does not perform any kind of formatting.

With this, you can now store the object of structs or classes directly into the file without serializing it into the textual format. It will be then automatically deserialized when the file is read.

Let's create a simple class called `Student` that will have _name_ and _age_ fields and a _whoami()_ method to return a std::string object.

```cpp
class Student {
  private:
    std::string name;
    unsigned short age;
  public:
    Student() {
      this->name = ""
      this->age = 0;
    }

    Student(const char * name, unsigned short age) {
      this->name = std::string(name);
      this->age = age;
    }

  std::string whoami() const {
    std::stringstream s;
    s << "I am " << this->name << " and " << this->age << " years old";
    return s.str();
  }

};

Student student("Gurkirat Singh", 20);
```

You can save this to a file using the following snippet by casing it to `char*` because of its definition in the stdc++. <sup>[read more](https://stackoverflow.com/a/45202852/10362396)</sup>

```cpp
out_file->write(reinterpret_cast<char*>&student, sizeof(student));
```

Once this is successfully saved into the file, you will verify that there are some weird characters present in the file and that is normal, because the string data also stores the information of deserializing the object.

```cpp
Student mystudent;
in_file->read(reinterpret_cast<char*>&mystudent, sizeof(mystudent));

std::cout << mystudent.whoami() << std::endl; // I am Gurkirat Singh and 20 years old
```

Now as a beginner, you must be thinking that the `Student` type is different from the `char` type. So why does the casting pointer not affect serialization? I would like to tell you that, you are getting confused between pointer type and other data types. For any data type, the pointer type would be 8 bytes or 4 bytes based on the CPU architecture, because it stores the starting address of the memory where that actual data of a type is stored. If the type of data is char, then it will consume 1 byte in the memory otherwise `sizeof(T)`.

## Using I/O Streams of the File

It is not like you can open a file only in one mode (that is either read or write), using `std::fstream` you can perform both input/output operations on the file with the same file handle.

### Read/Write Cursors

There are two types of cursors in the file **`g`**et and **`p`**ut. The get cursor is responsible for handling reading from the file which is known as **input operation** and the put cursor is responsible for handling writing into the file which is known as **output operation**.

To **get** the current position of the cursors, use the [`std::fstream::tellp()`](https://www.cplusplus.com/reference/ostream/ostream/tellp/?kw=tellp) or [`std::fstream::tellg()`](https://www.cplusplus.com/reference/istream/istream/tellg/?kw=tellg). You can also set the position of these cursors making (either forward or backward) while the file is open using [`std::fstream::seekp()`](https://www.cplusplus.com/reference/ostream/ostream/seekp/?kw=seekp) or [`std::fstream::seekg()`](https://www.cplusplus.com/reference/istream/istream/seekg/?kw=seekg) functions.

You can also seek the cursor relatively based on the three types of the [seek directions](https://www.cplusplus.com/reference/ios/ios_base/seekdir/)

+ `std::ios::beg` &mdash; from the beginning of file
+ `std::ios::cur` &mdash; from the current position of the cursor
+ `std::ios::end` &mdash; from the ending of the file or where the reader hits EOF

> **Note** You must clear the flags using [`std::fstream::clear()`](https://www.cplusplus.com/reference/ios/ios/clear/) to clear all the error bits before using `seekg()` or `seekp()`. <sup>[read more](https://stackoverflow.com/questions/16364301/whats-wrong-with-the-ifstream-seekg)</sup>


## Contact Details

Email: tbhaxor _at_ proton _dot_ me

Twitter: @tbhaxor

LinkedIn: @tbhaxor
