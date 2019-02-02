/// @file main.cpp
/// @brief Program to view and refresh histograms from disk.
/// @author S. V. Paulauskas
/// @date June 2, 2018
/// @copyright Copyright (c) 2018 S. V. Paulauskas.
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#include "MainFrame.hpp"

#include <iostream>
#include <stdexcept>

int main()
{
  try
    {
      TApplication app("app", nullptr, nullptr);
      new MainFrame(gClient->GetRoot(), &app);
      app.Run();
    }
  catch (std::exception &ex)
    {
      std::cout << "Exception Caught : " << ex.what() << std::endl;
      return 1;
    }
}
