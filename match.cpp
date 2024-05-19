

//#pragma once

#include "match.h"
#include "gui.h"

#include "player.cpp" //now


#include <memory>


// #include "match.h"
// #include "gui.h"
// #include "player.h"




auto TicTacToe::setDifficulty()->std::size_t
{

    GUI::clearScreenContent();
    
    std::size_t difficulty;
    
    do
    {
        //GUI::clearScreenContent();
      
        GUI::print('\n', "Choose difficulty level : ", '\n');
        GUI::print("1.EASY", '\n');
        GUI::print("2.HARD", '\n');
        GUI::print("3.IMPOSSIBLE", '\n');

	    GUI::print('\n', "ENTER: ");
  
        User::read_input(difficulty);

	    bool is_valid = difficulty == 1 || difficulty == 2 || difficulty == 3;

	    if(!is_valid) std::cerr << "Please enter valid input!" << '\n';

    }while(difficulty != 1 && difficulty != 2 && difficulty != 3);

    return difficulty;
    
}



//getFirstMover(const std::string &user_name, const std::string &bot_name)
auto TicTacToe::getFirstMover(const std::string &user_name, const std::string &bot_name) -> std::string
{
    std::string first_mover;
    
    GUI::clearScreenContent();

    do{        
      
        GUI::print("Who will play the first move?", "(", user_name, "/", bot_name, ")", ":");
	    User::read_input(first_mover);
	
    }while(first_mover != user_name && first_mover != bot_name); //while(first_mover != user_name && first_mover != bot_name)

    return first_mover;

}




void TicTacToe::showCurrentBoard() 
{  
    GUI::clearScreenContent();

    GUI::print("\e[1;"+m_color_code+"m" + m_Board[0] + "  " + m_Board[1] + "  " + m_Board[2] + "     " + "1  2  3" + "\e[0m" , "\n\n");
    GUI::print("\e[1;"+m_color_code+"m" + m_Board[3] + "  " + m_Board[4] + "  " + m_Board[5] + "     " + "4  5  6" + "\e[0m" , "\n\n");
    GUI::print("\e[1;"+m_color_code+"m" + m_Board[6] + "  " + m_Board[7] + "  " + m_Board[8] + "     " + "7  8  9" + "\e[0m" , "\n\n");
}


void TicTacToe::setWinCases(StrArr<Max::total_win_cases> &win_cases, const StrArr<Max::board_size> &Board)
{
    win_cases[0] = Board[0] + Board[1] + Board[2];
    win_cases[1] = Board[3] + Board[4] + Board[5];
    win_cases[2] = Board[6] + Board[7] + Board[8];

    win_cases[3] = Board[0] + Board[3] + Board[6];
    win_cases[4] = Board[1] + Board[4] + Board[7];
    win_cases[5] = Board[2] + Board[5] + Board[8];

    win_cases[6] = Board[0] + Board[4] + Board[8];
    win_cases[7] = Board[2] + Board[4] + Board[6];	   
}




//this is bad. Returning a reference to the local variable is just bad!

// StrArr<Max::total_win_cases> &TicTacToe::setWinCases(const StrArr<Max::board_size> &Board)
// {

//     StrArr<Max::total_win_cases> win_cases{};
  
//     win_cases[0] = Board[0] + Board[1] + Board[2];
//     win_cases[1] = Board[3] + Board[4] + Board[5];
//     win_cases[2] = Board[6] + Board[7] + Board[8];

//     win_cases[3] = Board[0] + Board[3] + Board[6];
//     win_cases[4] = Board[1] + Board[4] + Board[7];
//     win_cases[5] = Board[2] + Board[5] + Board[8];

//     win_cases[6] = Board[0] + Board[4] + Board[8];
//     win_cases[7] = Board[2] + Board[4] + Board[6];

//     return win_cases;
// }







using WINNER::NONE;
using WINNER::FIRST_PLAYER;
using WINNER::SECOND_PLAYER;
using WINNER::BOTH;


//this->matchEnd(firstPlayer->winStr , secondPlayer->winStr)
// auto TicTacToe::matchEnd(Player *firstPlayer, Player *secondPlayer)->std::uint8_t;
//auto TicTacToe::matchEnd(const std::size_t &firstPlayer_moves , const std::string &firstPlayerWin_str , const std::string &secondPlayerWin_str)->std::uint8_t

auto TicTacToe::matchEnd(const std::string &firstPlayerWin_str , const std::string &secondPlayerWin_str)->std::uint8_t
{    
    //at least 3 moves by the first player(first mover) is needed in order to find the winner or the draw case           
    // if(firstPlayer_moves < 3)
    // {
    //     return WINNER::NONE;
    // }

    //atleast five moves in total (by both players) are needed in order to find the winner or the draw case
    if(TicTacToe::total_moves < 5)
    {
        return WINNER::NONE;
    }
       
    StrArr<Max::total_win_cases> win_cases;

    setWinCases(win_cases , m_Board);

    //win_cases = setWinCases(m_Board);
       
    for(const auto& winner_line : win_cases)
    {
        if(winner_line == firstPlayerWin_str)  m_match_winner = WINNER::FIRST_PLAYER;    
        else if(winner_line == secondPlayerWin_str)  m_match_winner = WINNER::SECOND_PLAYER;
    }

    //we can also use 'if(firstPlayer_moves + secondPlayer_moves == 9 && matchWinner == 0x0)'
    // if(firstPlayer_moves == 5 && m_match_winner == WINNER::NONE) 
    // {
    //     m_match_winner = WINNER::BOTH;
    // }

    if(TicTacToe::total_moves == 9 && m_match_winner == WINNER::NONE)
    {
        m_match_winner = WINNER::BOTH;
    }
            
    return m_match_winner;   
}



void TicTacToe::eraseBoxPosition(const std::size_t player_position,
                                umap &boxes_positions,
                                umap &even_positions,
                                umap &odd_positions)
{

    boxes_positions.erase(player_position); // this removes the key from the map(the key is the players position)

    
    if(m_difficulty != DIFFICULTY::IMPOSSIBLE) return;
    

    if(player_position % 2 == 0 && !even_positions.empty())
        even_positions.erase(player_position);
    else if(player_position % 2 != 0 && !odd_positions.empty())
        odd_positions.erase(player_position);
    

}



//may name it 'PlayerToMove()'
void TicTacToe::playerTurn(Player *player)
{  

    //will show 'match_no' here GUI::print("Match no: ", match_no, '\n'); instead of the PlayMultipleMatches() function
    this->showCurrentBoard();
    GUI::sleep_millisecs(500 , "");


    //m_boxes_positions.erase(player->getPosition());

    // GUI::print('\n');
    // for(const auto& value : m_boxes_positions)
    // {
    //     GUI::print(value.first, " : ", value.second , '\n'); 
    // }
    
    
    player->setCurrentPosition(m_Board, m_empty_positions, m_boxes_positions,
                               m_even_positions, m_odd_positions);    
    player->placeSymbol(m_Board); 
    player->increaseMoves();


    eraseBoxPosition(player->getPosition(),
                     m_boxes_positions,
                     m_even_positions,
                     m_odd_positions);

    

    // m_boxes_positions.erase(player->getPosition()); // this removes the key from the map(the key is the players position)

    // if(player->getPosition() % 2 == 0 && !m_even_positions.empty())
    //     m_even_positions.erase(player->getPosition());
    // else if(player->getPosition() % 2 != 0 && !m_odd_positions.empty())
    //     m_odd_positions.erase(player->getPosition());

    
    ++TicTacToe::total_moves;

    GUI::print('\n', "player position choosed: ", player->getPosition(), '\n');

    GUI::clearScreenContent();    
   
}



// template<typename T>
// T get_info(T *player)
// {
    
//     return *player;
// }


// Player player_info = get_info(first_player); 



void TicTacToe::play(Player *first_player, Player *second_player) noexcept
{
    //firstPlayer is the Player who will move first meaning place his symbol on board first
    //secondPlayer is the Player who will move after first player has moved OR placed his symbol on board
  
    handleNullPtr(first_player);
    handleNullPtr(second_player);
  
    GUI::clearScreenContent();

    TicTacToe::total_moves = 0;

    #define EVER ;;

    //for(EVER) // using for(;;) instead of while(true)
    for(EVER)
    {
        //first players turn to play
   
        this->playerTurn(first_player);
	    if(this->matchEnd(first_player->getWinStr(), second_player->getWinStr())) break;
        //if(this->matchEnd(first_player->getMoves(), first_player->getWinStr(), second_player->getWinStr())) break;
      
        //second players turn to play
            
        this->playerTurn(second_player);
	    if(this->matchEnd(first_player->getWinStr(), second_player->getWinStr())) break;
        //if(this->matchEnd(first_player->getMoves(), first_player->getWinStr(), second_player->getWinStr())) break;
    }

    this->showMatchResult(first_player, second_player);
    //this->showMatchResult(*first_player, *second_player);
 
}



//will make the function this
//void TicTacToe::showMatchResult(Player &first_player , Player &second_player)
void TicTacToe::showMatchResult(Player *first_player , Player *second_player)
{
      GUI::clearScreenContent();
      showCurrentBoard();

      GUI::print("\n\n");
  
      switch(m_match_winner)
      {
	      case WINNER::FIRST_PLAYER:
	  	  	    
	           GUI::print("\e[1;32m" , first_player->getName() , " won the match!\e[0m" , "\n\n");

	           GUI::print(first_player->getName() , " (" , first_player->getSymbol() , ") " , " gained  : 1 points" , '\n');
	           GUI::print(second_player->getName() , " (" , second_player->getSymbol() , ") " , " gained : 0 points" , '\n');
	    	    
               first_player->increasePoints();
               break;

          case WINNER::SECOND_PLAYER:
	  
               GUI::print("\e[1;32m" , second_player->getName() , " won the match!\e[0m" , "\n\n");

	           GUI::print(first_player->getName() , " (" , first_player->getSymbol() , ") " , " gained  : 0 points" , '\n');
	           GUI::print(second_player->getName() , " (" , second_player->getSymbol() , ") " , " gained : 1 points" , '\n');

	           second_player->increasePoints();
               break;

	     case WINNER::BOTH:         
	  
	          GUI::print("\e[1;34mMatch Draw!\e[0m" , '\n');

	          GUI::print(first_player->getName() , " (" , first_player->getSymbol() , ") " , " gained  : 0 points" , '\n');
	          GUI::print(second_player->getName() , " (" , second_player->getSymbol() , ") " , " gained : 0 points" , '\n');	    	    
              break;	    
      }

      GUI::print('\n');
      GUI::print("Moves by " , first_player->getName() , " : " , first_player->getMoves() , '\n');
      GUI::print("Moves by " , second_player->getName() , " : " , second_player->getMoves() , '\n');

}












































































