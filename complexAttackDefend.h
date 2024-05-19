

//#include "player.h"

#include <vector>

#include "some_definition.h"



typedef struct AttackDefendPosition
{

public:

    AttackDefendPosition() = default;
    ~AttackDefendPosition() = default;

    //may use std::move here for the strings if the orginal one is not needed anymore
    explicit AttackDefendPosition(std::size_t bot_position,
				  StrArr<Max::board_size> &Board,
				  const std::vector<std::size_t> &even_positions, const std::vector<std::size_t> &odd_positions, 
				  std::size_t user_moves, std::size_t bot_moves,
				  std::string user_symbol, std::string bot_symbol,
				  bool bot_is_first_mover)
	
	: m_position(bot_position),
	  found(false), box("□"),
	  Board(Board), even_positions(even_positions), odd_positions(odd_positions),
	  user_moves(user_moves), m_moves(bot_moves),
	  user_symbol(user_symbol), m_symbol(bot_symbol),
	  m_is_first_mover(bot_is_first_mover){}


    void find1();
    void find2();
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

    auto FIND()->std::size_t; // may make it a static function

    //bool found(){return found;}

    bool found;

    
private:

    //bool found;

    std::size_t m_position;

    std::string box;
    StrArr<Max::board_size> Board;

    std::vector<std::size_t> even_positions{};
    std::vector<std::size_t> odd_positions{};
    
    
    std::size_t user_moves;
    std::size_t m_moves;          // m_bot_moves;
    std::string user_symbol;
    std::string m_symbol;         // m_bot_symbol;
    bool        m_is_first_mover; // m_bot_is_first_mover;
       

}AttackDefendPosition;























































