

#pragma once
 
#include <iostream>
#include <optional>

#include "some_definition.h"



class Player
{

public:  

    //for larger types like std::string using std::move() is a good option
    //don't confuse 'std::move()' with member variable 'm_move'

    Player() = delete;
    Player(std::size_t moves, std::size_t points, bool is_first_mover) noexcept
      : m_moves(moves), m_points(points), m_is_first_mover(is_first_mover){}
  
    //m_win_str(std::move(m_symbol + m_symbol + m_symbol))
    //Player() = default;
    virtual ~Player() = default;
  
    //const std::list<std::size_t> &empty_positions
    virtual void  setCurrentPosition(StrArr<Max::board_size> &Board, const IntArr &empty_positions,
                                     umap &boxes_positions,
                                     const umap &u_even_positions,
                                     const umap &u_odd_positions) = 0;    
  
    inline  bool  findWinPosition(std::size_t box_index_pos, const std::string &symbol, std::size_t &bot_position, StrArr<Max::board_size> &Board) noexcept; //will make it Bot::func()
    inline  void  placeSymbol(StrArr<Max::board_size> &Board){Board[m_position - 1] = m_symbol;} //will name it placeSymbolAtPosition();  
    inline  void  setAsFirstMover(){m_is_first_mover = true;}
    inline  void  setWinStr(){m_win_str = m_symbol + m_symbol + m_symbol;}
    inline  void  setMoves(){m_moves = 0;} //will remove this later
    inline  auto  getPosition()->std::size_t{return m_position;}
    inline  auto  getWinStr()->std::string{return m_win_str;}  
    inline  auto  getSymbol()->std::string{return m_symbol;}  
    inline  auto  getName()->std::string{return m_name;}  
    inline  auto  getMoves()->std::size_t{return m_moves;}  
    inline  auto  getPoints()->std::size_t{return m_points;}  
    inline  void  increasePoints(){++m_points;}  
    inline  void  increaseMoves(){++m_moves;}

protected:

    std::string    m_symbol;
    std::string    m_name;
    std::string    m_win_str; 
    std::size_t    m_position;
    std::size_t    m_moves;    
    std::size_t    m_points;
    bool           m_is_first_mover;
  
};





class User : public Player
{
  
public:

    //User() = delete;
    User() noexcept : Player(0, 0, false){}           //may initalize 'm_name' in the User initializer list
   ~User() = default;

    template<typename T>
    inline static void read_input(T &first_arg) noexcept
    {
        std::cin >> first_arg;
    }


    void setName();
    void setSymbol();      
    void setCurrentPosition(StrArr<Max::board_size> &Board, const IntArr &empty_positions,
                            umap &boxes_positions,
                            const umap &,
                            const umap &) override;
  
};


class Bot : public Player
{
  
public:

    Bot() = delete;
    Bot(std::size_t skill) noexcept : Player(0, 0, false), m_skill(skill){} //will make difficulty std::uint8_t and also may initalize 'm_name' in the User initializer list
   ~Bot() = default;
              
    //for Types less than 16 bytes(in my arcitecture) is better to simply pass by const value than pass by const reference
    [[nodiscard]] static auto generateRandomNumber(const std::size_t lower_range, const std::size_t upper_range,
						                           const std::optional<std::size_t> &&except)->std::size_t;
    
    //once i forgor to catch the return value of this function...
    [[nodiscard]] static auto generateRandomPosition(const std::vector<std::size_t> &positions_data)->std::size_t;
    [[nodiscard]] static auto generateRandomPosition(const umap &positions_data)->std::size_t;

 
    void setName();
    void setSymbol(const std::string &user_symbol);
    void saveUsersSymbol(const std::string &user_symbol);

    // this is the main character
    void setPositionToWinPosition(StrArr<Max::board_size> &Board,		    
                                  umap &boxes_positions,
                                  const umap &u_even_positions,
                                  const umap &u_odd_positions);

    
    void setCurrentPosition(StrArr<Max::board_size> &Board, const IntArr &empty_positions,
                            umap &boxes_positions,
                            const umap &u_even_positions,
                            const umap &u_odd_positions) override;

    //std::string user_symbol;


  //findWinPosition(), SetPositionToWinPosition() are the functions which tests where the user and bot can win the match and then if there any position on the board where after the users next move , the user can win the match or the bot can win the match SetPositionToWinPosition() functions sets the bots position to that win position.

private:
    

    std::size_t m_skill;
    std::string user_symbol;

};



























































































