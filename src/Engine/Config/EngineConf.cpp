#include "Engine/Config/EngineConf.h"

void FileConf::generateFile(const std::string fileName, const std::vector <std::string> content_to_write)
{
    std::ifstream file_exists(fileName);
    if(!file_exists)
    {
        std::ofstream outfile (fileName);
        for (int i=0; i < content_to_write.size(); i++)
        {
            outfile << content_to_write[i] << std::endl;
        }
        outfile.close();
    }
    else
    {
        std::cout<<"File already exists"<<std::endl;
    }
    
}

std::vector <int> FileConf::readFile(const std::string fileName)
{
    std::vector <int> data_value; 
    std::ifstream config_file(fileName);
    if(config_file)
    {
        std::string current_line;
        int current_value;
        while(std::getline(config_file, current_line, '=') && config_file >> current_value)
        {
            data_value.push_back(current_value);
        }
    }

    config_file.close();
    
    return data_value;
}