#pragma once 

#include <iostream>
#include <fstream>
#include <vector>  
#include <string>

struct Data_struct
{
    std::vector <std::string> command_name; 
    std::vector <int> command_value;
};

class FileConf
{
public: 
    void generateFile(const std::string fileName, std::vector <std::string> content_to_write);
    std::vector <int> readFile(const std::string fileName);
};