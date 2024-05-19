

#pragma once

#include <iostream>
#include <thread>
#include <chrono>

#include "player.h"

//this namespace handles all the graphical functions like: displaying(showing) ,pausing execution, clearing content of the terminal, asking user to select the Board theme, sleeping etc.
namespace GUI
{

void print(){}

template<typename T, typename...Args>
void print(T firstArg, Args...args)
{
    std::cout << firstArg;
    print(args...);
}

  
inline void  clearScreenContent()
{
    print("\033[H\033[2J");
}

  
inline void sleep_millisecs(const std::size_t &delay , const std::string& text)
{   
    print("\e[1;35m" + text + "\e[0m" , '\n');
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

  
inline void pauseExecution(const std::string& text)
{
    std::cout << text;
    std::cin.ignore();
    std::cin.get();      
}

  
inline auto selectBoardTheme()->std::string
{
    std::string colorCode = " ";
    
    print("Choose Board theme(red:31 , green:32 , soft brown:33 , magenta:35): ");
    User::read_input(colorCode);    
        	
    return colorCode;
}
  
  

}//end of namespace GUI














































































