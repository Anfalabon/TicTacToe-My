
//#pragma once

#include "complexAttackDefend.h"

#include "match.h"


static auto Bot::setRandomPosition(const std::vector<std::size_t> &positions_data)->std::size_t
{
    std::size_t random_index = Bot::generateRandomNumber(0, positions_data.size() - 1, std::nullopt);
    return data_set[random_index];
    
}

//void AttackDefendPosition::find1(std::size_t &m_position)
void AttackDefendPosition::find1()
{
    if(user_moves >= 1)
    {
        // if(Board[0] == user_symbol && Board[8] == box) m_position = 9, found = true;
        // else if(Board[2] == user_symbol && Board[6] == box) m_position = 7, found = true;
        // else if(Board[6] == user_symbol && Board[2] == box) m_position = 3, found = true;
        // else if(Board[8] == user_symbol && Board[0] == box) m_position = 1, found = true;


        std::vector<std::size_t> vec;
	
	if(Board[0] == user_symbol && Board[8] == box) vec.push_back(9);
        else if(Board[2] == user_symbol && Board[6] == box) vec.push_back(7);
        else if(Board[6] == user_symbol && Board[2] == box) vec.push_back(3);
        else if(Board[8] == user_symbol && Board[0] == box) vec.push_back(1);

	if(vec.empty()) return;

	found = true;
	Bot::setRandomPosition(vec);	      	
    }
}

//void AttackDefendPosition::find2(std::size_t &m_position)
void AttackDefendPosition::find2()
{
    
    if(user_moves >= 2 && Board[4] == m_symbol && !odd_positions.empty())
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

    if(m_moves >= 1 && user_moves >= 1 && !odd_positions.empty())
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

    std::size_t number_of_even_positions = even_positions.size();
    // may remove '!m_is_first_mover' cause the case could also work if the bot is the first mover
    if(!m_is_first_mover && user_moves >= 2 && !even_positions.empty()) 
    {
	std::size_t random_index = Bot::generateRandomNumber(0, number_of_even_positions - 1, std::nullopt);
	std::size_t random_position = even_positions[random_index];
	
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

    if(m_moves >= 2 && Board[4] == m_symbol && !even_positions.empty()) // && !even_positions.empty() // _| OR |_ case
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
    
    if(m_moves >= 2 && !odd_positions.empty()) // |_ case
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







































































