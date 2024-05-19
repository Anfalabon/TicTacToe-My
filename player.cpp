
#pragma once


#include <random>
#include <vector>
#include <optional>
#include <algorithm>
#include <ranges>
#include <functional>
#include <iterator>
#include <ctime>
#include <cstdlib>

#include "gui.h"
#include "match.h"

#include "player.h"

//#include "complexAttackDefend.h"
//#include "match.cpp"


void User::setName()
{
    // GUI::print("Enter Your name: ", m_name);
    // read_input(m_name);
    
    m_name = "user";
}

void Bot::setName()
{
    m_name = "bot";
}


void User::setSymbol()
{
  
    std::string temp_user_symbol;
    GUI::print('\n');
        
    do{

        GUI::print("\e[1;38mChoose any Symbol: \e[0m");
	User::read_input(temp_user_symbol);

    }while(temp_user_symbol.size() != 1);

    m_symbol = temp_user_symbol;
    
}



//will let the bot choose any other symbol(length of 1) rather than only "X" and "O"
void Bot::setSymbol(const std::string &user_symbol) //here otherSymbol means humanSymbol
{
  
    const char *user_char_ptr = user_symbol.c_str(); //this is a single length string 
    const char user_char = user_char_ptr[0];
    
    const auto user_symbol_ascii_number = static_cast<std::size_t>(user_char); //'std::optional<std::size_t>'

    const std::size_t random_ascii_number = Bot::generateRandomNumber(33, 126, std::move(user_symbol_ascii_number)); // will remove this std::move 
    
    const char random_char = static_cast<char>(random_ascii_number);
       
    const std::string random_symbol = std::string(1, random_char);
       
    m_symbol = random_symbol;
    
}


void Bot::saveUsersSymbol(const std::string &user_symbol)
{
    this->user_symbol = user_symbol;
}


   



void User::setCurrentPosition(StrArr<Max::board_size> &Board, const IntArr &empty_positions,
                              umap &boxes_positions,
                              const umap &,
                              const umap &)  
{  

    //maybe use empty_positions here
    //while(empty_positions[position - 1] != 0)

    //here to prevent user entering invalid inputs  
    bool invalid_position;

    do{

        std::string temp_user_pos;
	
	    GUI::print("\e[1;36mPlace your Symbol(" + m_symbol+ ") (as shown in the side board):\e[0m");
	    User::read_input(temp_user_pos);
                	
	    if(temp_user_pos.size() > 1)
	    {
	        temp_user_pos = "c"; // here any character is valid but i have used "c"
	    }
	
        m_position = std::atoi(temp_user_pos.c_str());
			
        invalid_position = (m_position < 1) || (m_position > Max::board_size); //here this variable is kindof useless maybe. will see it later

    }while(Board[m_position - 1] != "□"); //while(position != empty_positions{value1, value2, value3...})

}


//'except' means maybe from lower_range to upper_range there is a value which we don't want to generate
auto Bot::generateRandomNumber(const std::size_t lower_range, const std::size_t upper_range, const std::optional<std::size_t> &&except)->std::size_t
{

    if(lower_range > upper_range) throw std::runtime_error("lower_range is greater than upper_range!");
    
    if(lower_range == upper_range)
    {
        return lower_range;
    }
				     
    std::random_device rd;
    std::mt19937 gen(rd());
         
    std::size_t random_number;

    if(except.has_value())
    {      	
        const std::size_t random_size = upper_range - lower_range - 1;
	    std::uniform_int_distribution<> dis(0, random_size);
	
	    if(random_number = dis(gen); random_number >= except.value() - lower_range) 
	    {
	       ++random_number;
	    }

	    random_number += lower_range;
	    //return random_number;
    }
    else
    {
        std::uniform_int_distribution<> dis(lower_range, upper_range);
        random_number = dis(gen);
	    //return dis(gen);
    }
    
    return random_number;    
}




auto Bot::generateRandomPosition(const std::vector<std::size_t> &positions_data)->std::size_t
{
    GUI::print('\n', "random position running!" , '\n');
    const std::size_t random_index = Bot::generateRandomNumber(0, positions_data.size() - 1, std::nullopt);
    return positions_data[random_index];
}


auto Bot::generateRandomPosition(const umap &positions_data)->std::size_t
{
    std::size_t random_number = Bot::generateRandomNumber(0, positions_data.size() - 1, std::nullopt);
    auto random_iterator = std::next(positions_data.begin(), random_number);

    return random_iterator->second;
}








//TODO : replace the function name to 'findEndPosition'
//TODO : replace a good algorithm with this
bool Player::findWinPosition(std::size_t box_index_pos, const std::string &symbol, std::size_t &bot_position, StrArr<Max::board_size> &Board) noexcept
{    
    StrArr<Max::total_win_cases> temp_win_cases;
	
    Board[box_index_pos - 1] = symbol;                          
    TicTacToe::setWinCases(temp_win_cases , Board);    //this is bad for using here. Need to change this later
    Board[box_index_pos - 1] = "□";            
    
    auto player_win_case = symbol + symbol + symbol;   //player->win_str
    
    bool win_position_found = false;
    
    for(const auto& winner_line : temp_win_cases)
    {
        if(winner_line == player_win_case)
        {	 
            //bot_position = box_index_pos + 1; // for 'Boxes_index_positions'
            bot_position = box_index_pos; 
	        win_position_found = true;
	        break;
        }       
    }

    return win_position_found;
}



//will use this class and the functions of the class in another file.(complexAttackDefend.h and complexAttackDefend.cpp)
typedef struct AttackDefendPosition
{

public:

  
    //may use singleton pattern

    // AttackDefendPosition() = default;
    AttackDefendPosition() = delete; // deleting the default constructor cause i don't want anyone to use this!
   ~AttackDefendPosition() = default;

    

    //may use std::move here for the strings if the orginal one is not needed anymore
    explicit AttackDefendPosition(std::size_t bot_position,
				                  StrArr<Max::board_size> &Board,
                                  const umap &u_even_positions, const umap &u_odd_positions,
				                  std::size_t user_moves, std::size_t bot_moves,
				                  const std::string &user_symbol, const std::string &bot_symbol,
				                  bool is_bot_first_mover)
	
	: m_position(bot_position),
	  found(false), box("□"),
	  Board(Board),
	  u_even_positions(u_even_positions), u_odd_positions(u_odd_positions),
	  user_moves(user_moves), m_moves(bot_moves),
	  user_symbol(user_symbol), m_symbol(bot_symbol),
	  m_is_first_mover(is_bot_first_mover){}
    

    //will change the functions names. (there suffixs from '1 2 3...' to something meaningful)
  
    void find1();  //findOposite()
    void find2();  //...
    void find3();
    void find4();
    void find5();
    void find6();
    void find7();
    void find8();
    void find9();
    void find10();
    void find11();
    void find12();
    void find13();
    void find14();


    // void findCross();
    // void 

    auto FIND()->std::size_t; // may make it a static function
    bool isFound(){return found;}
        

    //bool found;

    
private:

    bool found;

    std::size_t m_position;

    std::string box;
    
    StrArr<Max::board_size> Board;

    umap u_even_positions{};
    umap u_odd_positions{};

    
    std::size_t user_moves;
    std::size_t m_moves;          // m_bot_moves;
    std::string user_symbol;
    std::string m_symbol;         // m_bot_symbol;
    bool        m_is_first_mover; // m_bot_is_first_mover;


       

}AttackDefendPosition;






//void AttackDefendPosition::find1(std::size_t &m_position)
//findOposite();
void AttackDefendPosition::find1()
{
    if(user_moves >= 1)
    {
          
        // if(Board[0] == user_symbol && Board[8] == box) m_position = 9, found = true;
        // else if(Board[2] == user_symbol && Board[6] == box) m_position = 7, found = true;
        // else if(Board[6] == user_symbol && Board[2] == box) m_position = 3, found = true;
        // else if(Board[8] == user_symbol && Board[0] == box) m_position = 1, found = true;

        //will do the same in every other 'find' functions(this maybe increases the randomness of the moves)
        std::vector<std::size_t> vec{};
	
	    if(Board[0] == user_symbol && Board[8] == box) vec.push_back(9);
        else if(Board[2] == user_symbol && Board[6] == box) vec.push_back(7);
        else if(Board[6] == user_symbol && Board[2] == box) vec.push_back(3);
        else if(Board[8] == user_symbol && Board[0] == box) vec.push_back(1);

	    if(vec.empty()) return;

	    found = true;
	    // this was the first time i forgot to catch the return value and i understood the value of [[nodiscard]].
	    m_position = Bot::generateRandomPosition(std::move(vec)); 
    }
}

//void AttackDefendPosition::find2(std::size_t &m_position)
void AttackDefendPosition::find2()
{
    
    if(user_moves >= 2 && Board[4] == m_symbol && !u_odd_positions.empty())
    {

        if(Board[0] == user_symbol && Board[5] == user_symbol && Board[8] == box) m_position = 9, found = true;
	    else if(Board[2] == user_symbol && Board[3] == user_symbol && Board[6] == box) m_position = 7, found = true;
	
	    else if(Board[2] == user_symbol && Board[7] == user_symbol && Board[6] == box) m_position = 7, found = true;
	    else if(Board[8] == user_symbol && Board[1] == user_symbol && Board[0] == box) m_position = 1, found = true;

	    else if(Board[8] == user_symbol && Board[3] == user_symbol && Board[0] == box) m_position = 1, found = true;
	    else if(Board[6] == user_symbol && Board[5] == user_symbol && Board[2] == box) m_position = 3, found = true;

	    else if(Board[6] == user_symbol && Board[1] == user_symbol && Board[2] == box) m_position = 3, found = true;
	    else if(Board[0] == user_symbol && Board[7] == user_symbol && Board[8] == box) m_position = 9, found = true;     
    }

}


// void AttackDefendPosition::find3(std::size_t &m_position)
void AttackDefendPosition::find3()
{

    if(m_moves >= 2 && Board[4] == box) // _|
    {
        if(Board[1] == m_symbol && Board[3] == m_symbol) m_position = 5, found = true;
        else if(Board[1] == m_symbol && Board[5] == m_symbol) m_position = 5, found = true;
        else if(Board[3] == m_symbol && Board[7] == m_symbol) m_position = 5, found = true;
        else if(Board[5] == m_symbol && Board[7] == m_symbol) m_position = 5, found = true;
    }
    
}


// void AttackDefendPosition::find4(std::size_t &m_position)
void AttackDefendPosition::find4()
{

    if(m_moves >= 1 && user_moves >= 1 && !u_odd_positions.empty())
    {
        if(Board[0] == m_symbol && Board[1] == user_symbol && Board[6] == box) m_position = 7, found = true;
	    else if(Board[0] == m_symbol && Board[3] == user_symbol && Board[2] == box) m_position = 3, found = true;

	    else if(Board[2] == m_symbol && Board[5] == user_symbol && Board[0] == box) m_position = 1, found = true;
	    else if(Board[2] == m_symbol && Board[1] == user_symbol && Board[8] == box) m_position = 9, found = true;

	    else if(Board[6] == m_symbol && Board[7] == user_symbol && Board[0] == box) m_position = 1, found = true;
	    else if(Board[6] == m_symbol && Board[3] == user_symbol && Board[8] == box) m_position = 9, found = true;

	    else if(Board[8] == m_symbol && Board[5] == user_symbol && Board[6] == box) m_position = 7, found = true;
	    else if(Board[8] == m_symbol && Board[7] == user_symbol && Board[2] == box) m_position = 3, found = true;
    }

}


//void AttackDefendPosition::find5(std::size_t &m_position)
void AttackDefendPosition::find5()
{

    if(m_moves >= 2)  // L case
    {
        if((Board[0] == m_symbol && Board[2] == m_symbol) && Board[6] == box) m_position = 7, found = true;
        else if((Board[0] == m_symbol && Board[6] == m_symbol) && Board[2] == box) m_position = 3, found = true;

        else if((Board[2] == m_symbol && Board[0] == m_symbol) && Board[8] == box) m_position = 9, found = true;
        else if((Board[2] == m_symbol && Board[8] == m_symbol) && Board[0] == box) m_position = 1, found = true;

        else if((Board[6] == m_symbol && Board[0] == m_symbol) && Board[8] == box) m_position = 9, found = true;
        else if((Board[6] == m_symbol && Board[8] == m_symbol) && Board[0] == box) m_position = 1, found = true;

        else if((Board[8] == m_symbol && Board[2] == m_symbol) && Board[6] == box) m_position = 7, found = true;
        else if((Board[8] == m_symbol && Board[6] == m_symbol) && Board[2] == box) m_position = 3, found = true;		
    }

}



// void AttackDefendPosition::find6(std::size_t &m_position)
void AttackDefendPosition::find6()
{
    
    if(m_moves >= 1 && user_moves >= 1) // && !odd_positions.empty()
    {
        if(Board[0] == m_symbol && Board[5] == user_symbol && Board[2] == box) m_position = 3, found = true;
	    else if(Board[2] == m_symbol && Board[3] == user_symbol && Board[0] == box) m_position = 1, found = true;
	
	    else if(Board[6] == m_symbol && Board[5] == user_symbol && Board[8] == box) m_position = 9, found = true;
	    else if(Board[8] == m_symbol && Board[3] == user_symbol && Board[6] == box) m_position = 7, found = true;

        else if(Board[0] == m_symbol && Board[7] == user_symbol && Board[6] == box) m_position = 7, found = true;
	    else if(Board[6] == m_symbol && Board[1] == user_symbol && Board[0] == box) m_position = 1, found = true;

	    else if(Board[2] == m_symbol && Board[7] == user_symbol && Board[8] == box) m_position = 9, found = true;
	    else if(Board[8] == m_symbol && Board[1] == user_symbol && Board[2] == box) m_position = 3, found = true;
    }

}



//void AttackDefendPosition::find7(std::size_t &m_position)
void AttackDefendPosition::find7()    
{
    
    if(user_moves >= 2 && Board[4] == m_symbol) // V case  // pelvis case
    {
        if(Board[0] == m_symbol && Board[2] == box) m_position = 3, found = true;
        else if(Board[2] == m_symbol && Board[0] == box) m_position = 1, found = true;

	    else if(Board[2] == m_symbol && Board[8] == box) m_position = 9, found = true;
	    else if(Board[8] == m_symbol && Board[2] == box) m_position = 3, found = true;

	    else if(Board[8] == m_symbol && Board[6] == box) m_position = 7, found = true;
	    else if(Board[6] == m_symbol && Board[8] == box) m_position = 9, found = true;

	    else if(Board[6] == m_symbol && Board[0] == box) m_position = 1, found = true;
	    else if(Board[0] == m_symbol && Board[6] == box) m_position = 7, found = true;        
    }

}



//void AttackDefendPosition::find8(std::size_t &m_position)
void AttackDefendPosition::find8()
{

    std::size_t number_of_even_positions = u_even_positions.size();
    
    // may remove '!m_is_first_mover' cause the case could also work if the bot is the first mover
    if(!m_is_first_mover && user_moves >= 2 && !u_even_positions.empty()) 
    {      
	    std::size_t random_position = Bot::generateRandomPosition(u_even_positions); //std::generateRandomPosition(u_even_positions);
	
	    if(Board[0] == user_symbol && Board[8] == user_symbol && Board[4] == m_symbol) m_position = random_position, found = true;       
	    else if(Board[2] == user_symbol && Board[6] == user_symbol && Board[4] == m_symbol) m_position = random_position, found = true;
    }
    
}



//void AttackDefendPosition::find9(std::size_t &m_position)
void AttackDefendPosition::find9()    
{    
    if(!m_is_first_mover && TicTacToe::total_moves == 1 && Board[4] == box) m_position = 5, found = true;
}



// void AttackDefendPosition::find10(std::size_t &m_position)
void AttackDefendPosition::find10()
{
    //these cases below are only true when the middle position '5' is empty    
    if(Board[4] == box && user_moves >= 2)
    {
        if(Board[1] == user_symbol && Board[3] == user_symbol) m_position = 5, found = true;
        else if(Board[1] == user_symbol && Board[5] == user_symbol) m_position = 5, found = true;
        else if(Board[3] == user_symbol && Board[7] == user_symbol) m_position = 5, found = true;
        else if(Board[5] == user_symbol && Board[7] == user_symbol) m_position = 5, found = true;
    }    

}



//void AttackDefendPosition::find11(std::size_t &m_position)
void AttackDefendPosition::find11()    
{
    //these cases are only true when the odd positions are empty   
    if(user_moves >= 2 && Board[4] == m_symbol)
    {
        if(Board[1] == user_symbol && Board[3] == user_symbol && Board[0] == box) m_position = 1, found = true;
        else if(Board[1] == user_symbol && Board[5] == user_symbol && Board[2] == box) m_position = 3, found = true;
        else if(Board[3] == user_symbol && Board[7] == user_symbol && Board[6] == box) m_position = 7, found = true;
        else if(Board[5] == user_symbol && Board[7] == user_symbol && Board[8] == box) m_position = 9, found = true;
    }
    
}



//void AttackDefendPosition::find12(std::size_t &m_position)
void AttackDefendPosition::find12()
{
    
    if(user_moves >= 1 && m_moves >= 1 && Board[4] == user_symbol)
    {
        if(Board[0] == m_symbol && Board[8] == box) m_position = 9, found = true;
        else if(Board[2] == m_symbol && Board[6] == box) m_position = 7, found = true;
        else if(Board[6] == m_symbol && Board[2] == box) m_position = 3, found = true;
        else if(Board[8] == m_symbol && Board[0] == box) m_position = 1, found = true;
    }

}



//void AttackDefendPosition::find13(std::size_t &m_position)
void AttackDefendPosition::find13()
{

    if(m_moves >= 2 && Board[4] == m_symbol && !u_even_positions.empty()) // && !even_positions.empty() // _| OR |_ case
    {
        if(Board[1] == m_symbol && Board[3] == box) m_position = 4, found = true;
	    else if(Board[1] == m_symbol && Board[5] == box) m_position = 6, found = true;

	    else if(Board[5] == m_symbol && Board[1] == box) m_position = 2, found = true;
   	    else if(Board[5] == m_symbol && Board[7] == box) m_position = 8, found = true;

	    else if(Board[7] == m_symbol && Board[3] == box) m_position = 4, found = true;
	    else if(Board[7] == m_symbol && Board[5] == box) m_position = 6, found = true;

	    else if(Board[3] == m_symbol && Board[1] == box) m_position = 2, found = true;
	    else if(Board[3] == m_symbol && Board[7] == box) m_position = 8, found = true;
    }

}



// void AttackDefendPosition::find14(std::size_t &m_position)
void AttackDefendPosition::find14()
{
    
    if(m_moves >= 2 && !u_odd_positions.empty()) // |_ case
    {
        if(Board[1] == m_symbol && Board[3] == m_symbol && Board[0] == box) m_position = 1, found = true;
        else if(Board[1] == m_symbol && Board[5] == m_symbol && Board[2] == box) m_position = 3, found = true;
        else if(Board[3] == m_symbol && Board[7] == m_symbol && Board[6] == box) m_position = 7, found = true;
        else if(Board[5] == m_symbol && Board[7] == m_symbol && Board[8] == box) m_position = 9, found = true;
    }

}

    
   

auto AttackDefendPosition::FIND()->std::size_t
{
    
    find1();
    find2();
    find3();
    find4();
    find5();
    find6();
    find7();
    find8();
    find9();
    find10();
    find11();
    find12();
    find13();
    find14();

    return m_position;         
}






//need to improve the algorithm a lot!
//tests who can win the game on the next move

//void Bot::SetPositionToWinPosition(StrArr<Max::board_size> &Board, const std::list<std::size_t> &empty_positions)
void Bot::setPositionToWinPosition(StrArr<Max::board_size> &Board,
                                   umap &boxes_positions,
                                   const umap &u_even_positions,
                                   const umap &u_odd_positions)
{
    //Impossible mode
                      
    std::size_t number_of_boxes = Max::board_size - TicTacToe::total_moves; //number_of_boxes == Boxes_positions.size() + 1 // number_of_boxes - 1;
    std::size_t user_moves = Max::board_size - number_of_boxes - m_moves;

    GUI::print('\n', "Max board size: ", Max::board_size, '\n');
    GUI::print('\n', "total moves: ", TicTacToe::total_moves, '\n');

    

    //GUI::print('\n', "number of boxes: ", number_of_boxes, '\n');
    // logger('\n', "number of boxes: ", number_of_boxes, '\n');
    

    //std::size_t number_of_even_positions = even_positions.size();
    //std::size_t number_of_odd_positions  = odd_positions.size();

    std::string box = "□";

    m_position = 0;
        
    GUI::print('\n', "current choosed position: ", m_position, '\n');
    GUI::print('\n', "users symbol: ", user_symbol, '\n');


    switch(m_skill)
    {

        case DIFFICULTY::EASY:

            m_position = Bot::generateRandomPosition(boxes_positions);  //std::generateRandomPosition(boxes_positions);

             GUI::print('\n', m_position, '\n');
             
             //m_position = Bot::generateRandomPosition(Boxes_index_positions) + 1;
	         return;
             break;

        case DIFFICULTY::NORMAL:

             m_position = Bot::generateRandomPosition(boxes_positions);  //std::generateRandomPosition(boxes_positions);

             GUI::print('\n', m_position, '\n');
	  
             //m_position = Bot::generateRandomPosition(Boxes_index_positions) + 1;            
             break;

        case DIFFICULTY::IMPOSSIBLE:


             // std::size_t random_number = Bot::generateRandomNumber(0, boxes_positions.size(), std::nullopt);
             // auto random_iterator = std::next(boxes_positions.begin(), random_number);

             //executing this is just useless if the odd positions are empty!
             //we could just use even_positions but using maybe using 'boxes_positions' just increases randomness
             std::size_t middle_position = 5;
             auto it = boxes_positions.find(middle_position);
             if(it != boxes_positions.end()) // if(it != boxes_positions.end() && u_odd_positions.empty())
             {
                 boxes_positions.erase(middle_position);
                 m_position = Bot::generateRandomPosition(boxes_positions); //std::generateRandomPosition(boxes_positions);
                 boxes_positions[middle_position] = middle_position;
             }


             GUI::print('\n', "without middle position:", m_position, '\n');
                 

             //m_position = Bot::generateRandomPosition(without_middle_position);

             //if(TicTacToe::total_moves < 2) return;


             // AttackDefendPosition &attackDefendPosition = AttackDefendPosition::getInstance();
             // m_position = object.Find();

             
                 
             //singleton pattern
             AttackDefendPosition attackDefendPosition(m_position,
					                                   Board,
                                                       u_even_positions, u_odd_positions,
					                                   user_moves, m_moves,
					                                   user_symbol, m_symbol,
					                                   m_is_first_mover);

	     
             m_position = attackDefendPosition.FIND();

	     
             bool any_win_position_found = attackDefendPosition.isFound(); 

             GUI::print('\n', "any position found: ", any_win_position_found, '\n');
             GUI::print('\n', "position: ", m_position, '\n');

             
             if(!any_win_position_found && !u_odd_positions.empty())
             {	
	             m_position = Bot::generateRandomPosition(u_odd_positions); //std::generateRandomPosition(u_odd_positions);
             }

             break;

    }

        
    GUI::print('\n', "random position: ", m_position, '\n');

      
    GUI::print('\n', "user moves: ", user_moves, '\n');
    GUI::print('\n', "bot moves: ", m_moves, '\n');


    //may merge these two same loops together later.    
    for(const auto& box_index_pos : boxes_positions) //Boxes_index_positions
    {      
        if(user_moves < 2)
            break;    //atleast 2 moves are needed to find the win position of each player
	  
        GUI::print('\n', "running1", '\n');        
        if(this->findWinPosition(box_index_pos.second, user_symbol, m_position, Board))
            break;        
    }

    for(const auto& box_index_pos : boxes_positions) //Boxes_index_positions
    {             
        if(m_moves < 2)
            break;    //atleast 2 moves are needed to find the win position of each player
	
        GUI::print('\n', "running2", '\n');
	    if(this->findWinPosition(box_index_pos.second, m_symbol, m_position, Board))
            break;        
    }


    GUI::print('\n', "final position: ", m_position, '\n');

}






void Bot::setCurrentPosition(StrArr<Max::board_size> &Board, const IntArr &empty_positions,
                             umap &boxes_positions,
                             const umap &u_even_positions,
                             const umap &u_odd_positions)  
{

    
    //const std::size_t number_of_boxes = Max::board_size - TicTacToe::total_moves; // may remove this

    //will use this algorithm outside the function (it will decrease the number of loops)
    //meaning something like : Boxes_position.push_back(player->getPosition());


    
    // std::vector<std::size_t> Boxes_index_positions{};
    // Boxes_index_positions.reserve(number_of_boxes);

    // std::vector<std::size_t> even_boxes_positions{}; // Boxes_even_positions{};
    // std::vector<std::size_t> odd_boxes_positions{};  // Boxes_odd_positions{};

    // std::vector<std::size_t> without_middle_position{};
    // without_middle_position.reserve(number_of_boxes - 1);


    //will find an another good way to get the users symbol(may get the users symbol as a parameter)
    // for(const auto& symbol : Board)
    // {
    //     if(symbol != "□" && symbol != m_symbol)
    //         user_symbol = symbol;
    // }



    //collects all box positions or empty positions on Board inside the vector
    //this also takes the Symbol of the user. will find another good way to get the users symbol
    //will use 'memoization' algorithm rather than this

    // bool is_middle_position_present = true;
    
    // for(std::size_t i=0 ; i<Max::board_size ; ++i) 
    // {        
    //     if(Board[i] == "□") // if(Board[i] == "□" && box_pos != 5)
 	//     {
    //         std::size_t box_pos = i+1;
            
    //         // if(box_pos == 5)
    //         //     is_middle_position_present = true, continue;
                        
    //         Boxes_index_positions.push_back(i);


    //         //using bitwise operator instead of '%' operator to find even or odd number
	//         if((box_pos & 1) == 0) even_boxes_positions.push_back(box_pos);	    
	//         else if((box_pos & 1) != 0 && box_pos != 5) odd_boxes_positions.push_back(box_pos); //will remove '&& box_pos != 5

	//         if(box_pos != 5) without_middle_position.push_back(box_pos);
	//     } 
    //     else if(Board[i] != m_symbol && user_symbol == " ")
	//     {
	//         user_symbol = Board[i];
	//     }        
    // }
    
     
    
    this->setPositionToWinPosition(Board,                                   
                                   boxes_positions,
                                   u_even_positions,
                                   u_odd_positions);	    

      
}































































