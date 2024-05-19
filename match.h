

#pragma once

#include "player.h"

//#include <list>
#include <cstdint>
//#include <unordered_map>


class TicTacToe
{

public:

    explicit TicTacToe(std::string theme, std::size_t difficulty) // will make 'difficulty' std::uint8_t
      : m_match_winner(WINNER::NONE), m_color_code(theme), m_difficulty(difficulty){} 
  
    void play(Player *first_player, Player *second_player) noexcept;
  
    inline static auto getFirstMover(const std::string &user_name, const std::string &bot_name)->std::string;
  
    inline static void setWinCases(StrArr<Max::total_win_cases> &win_cases, const StrArr<Max::board_size> &Board);
  //inline static StrArr<Max::total_win_cases> &TicTacToe::setWinCases(const StrArr<Max::board_size> &Board); // will use auto here
      
    inline static void handleNullPtr(Player *player)
    {
        if(!player) throw std::runtime_error("Pointer is Null!");
    }


    //will remove this
    IntArr m_empty_positions{1, 2, 3, 4, 5, 6, 7, 8, 9};    

    
    umap m_boxes_positions =                                  {

                                                                   {1, 1},
                                                                   {2, 2},
                                                                   {3, 3},  
                                                                   {4, 4},
                                                                   {5, 5},
                                                                   {6, 6},
                                                                   {7, 7},
                                                                   {8, 8},
                                                                   {9, 9},
                                                                  
                                                              };
    
    //these even and odd positions unordered_map are just for 'Impossible mode'. For easy and hard mode 'm_boxes_position' is just enough

    umap m_even_positions = {

        {2, 2},
        {4, 4},
        {6, 6},
        {8, 8}

    };

    //without the position 5(excluding 5 from here cause for bot this number can be a trouble in Impossible mode)
    umap m_odd_positions = {

        {1, 1},
        {3, 3},
        {7, 7},
        {9, 9}
        
    };


    static std::size_t total_moves; // moves done by the user and the bot
  
        
    void    showCurrentBoard();    
    void    playerTurn(Player *player);            
    auto    matchEnd(const std::string &firstPlayerWin_str , const std::string &secondPlayerWin_str)->std::uint8_t;
    void    showMatchResult(Player *first_player ,Player *second_player);
    auto    getBoardTheme()->std::string; // same as GUI::selectBoardTheme()
    void    eraseBoxPosition(const std::size_t player_position,
                             umap &boxes_positions,
                             umap &even_positions,
                             umap &odd_positions);

  
    static auto setDifficulty()->std::size_t;

    auto    getDifficulty()->std::size_t{return m_difficulty;}

private:
  
    std::string  m_color_code; //will make it const  
    std::uint8_t m_match_winner;
    std::size_t  m_difficulty;

    StrArr<Max::board_size>  m_Board = {
                                              "□" , "□" , "□" ,
                                              "□" , "□" , "□" ,
                                              "□" , "□" , "□"
                                       };
  

};//end of TicTacToe class


std::size_t TicTacToe::total_moves = 0;






































































