#  Custom JSON-Parser for C++
This is a custom json parser created to read data from json file in C++. Its reads one json-object at a time from the file to create a structure using C++ variant, vector and Map to store the data. So it won't be a problem to open large data files as it will only open a part of it. 
## How to use this
This Json Parser is mainly designed for json data files which provides each data input as element of a json object. The code will pick up one object a time from a file and process and store it. Clone the repository first. The jsonobjects are given in startup.json. There is a file **jsondriver.cpp** which explains how to use this parser. When compiling please use C++17 and compile the jsonparser.cpp along with your file. 
