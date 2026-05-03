//
//  TextIO.h
//  Core
//
//  Created by Rasmus Anthin on 2024-05-24.
//

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>


namespace TextIO
{

  // verbosity = 0 : No messages.
  // verbosity = 1 : Only most severe error messages.
  // verbosity = 2 : + not so severe error messages.
  // verbosity = 3 : + "File does not exist" error message.
  inline bool read_file(const std::string& file_path, std::vector<std::string>& lines, int verbosity = 0)
  {
    if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path))
    {
      if (verbosity >= 3)
        std::cerr << "Error: File does not exist" << std::endl;
      return false;
    }
    
    std::ifstream file(file_path);
    
    if (!file.is_open())
    {
      if (verbosity >= 1)
        std::cerr << "Error: Unable to open file \"" << file_path << "\"!" << std::endl;
      file.close();
      return false;
    }
    
    if (file.eof())
    {
      if (verbosity >= 2)
        std::cout << "Error: End of file reached." << std::endl;
      file.close();
      return false;
    }
    if (file.fail())
    {
      if (verbosity >= 2)
        std::cerr << "Error: Non-fatal I/O error occurred." << std::endl;
      file.close();
      return false;
    }
    if (file.bad())
    {
      if (verbosity >= 1)
        std::cerr << "Error: Fatal I/O error occurred." << std::endl;
      file.close();
      return false;
    }
    
    std::string l;
    
    while (std::getline(file, l))
      lines.emplace_back(l);

    file.close();
    
    return true;
  }
  
  // verbosity = 0 : No messages.
  // verbosity = 1 : Only most severe error messages.
  // verbosity = 2 : + not so severe error messages.
  // verbosity = 3 : + "File does not exist" error message.
  inline bool write_file(const std::string& file_path, const std::vector<std::string>& lines, int verbosity = 0)
  {
    std::ofstream file(file_path);
    
    if (!file.is_open())
    {
      if (verbosity >= 3)
        std::cerr << "Error: Unable to open file \"" << file_path << "\"!" << std::endl;
      file.close();
      return false;
    }
    
    if (file.eof())
    {
      if (verbosity >= 2)
        std::cout << "Error: End of file reached." << std::endl;
      file.close();
      return false;
    }
    if (file.fail())
    {
      if (verbosity >= 2)
        std::cerr << "Error: Non-fatal I/O error occurred." << std::endl;
      file.close();
      return false;
    }
    if (file.bad())
    {
      if (verbosity >= 1)
        std::cerr << "Error: Fatal I/O error occurred." << std::endl;
      file.close();
      return false;
    }
    
    for (const auto& l : lines)
      file << l << '\n';
    
    file.close();
    
    return true;
  }

}
