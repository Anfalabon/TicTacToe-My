

#pragma once


#include <array>
#include <vector>
#include <list>
#include <unordered_map>


enum Max
{
    board_size = 9,
    total_win_cases = 8
};


enum WINNER
{
    NONE = 0x0,
    FIRST_PLAYER = 0x1,
    SECOND_PLAYER = 0x2,
    BOTH = 0x3 //DRAW = 0x3
};



//may make this enum a std::string
enum DIFFICULTY 
{
    EASY = 0x1,
    NORMAL = 0x2,
    IMPOSSIBLE = 0x3
};

// match_winner = 0x0 when no one has won.
// match_winner = 0x1 means match winner is the firstPlayer
// match_winner = 0x2 means match winner is the secondPlayer
// match_winner = 0x3 means that the last move has been done and no one has won //draw case


template<std::size_t N>
using StrArr = std::array<std::string, N>;
using List_int = std::list<std::size_t>;
using IntArr = std::array<std::size_t, Max::board_size>;
using umap = std::unordered_map<std::size_t, std::size_t>;




// template<typename T, std::size_t N>
// inline T *_alloc()
// {
//     return (T* )malloc(sizeof(T) * N);  
// }


// template<typename T>
// inline void *_dealloc(T *ptr)
// {
//     free(ptr);  
// }


// #define write_line_number() std::cout << "Line number:" << __LINE__ << ": ";

// inline void logger(){}
// template<typename T, typename...Args>
// inline void logger(const T &first_arg, Args...args)
// {
//     write_line_number();
//     std::cout << first_arg << '\n';
//     logger(args...);
// }



#define LOG(debug_message) std::cout << debug_message << " at line: " << __LINE__ << '\n';

















