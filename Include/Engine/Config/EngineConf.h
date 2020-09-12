#pragma once 

#include <iostream>
#include <fstream>
#include <vector>  

class FileConf
{
public: 
    void generateFile(const std::string fileName, std::vector <std::string> content_to_write);
    std::vector <std::string> readFile(const std::string fileName);
};