
//WILL MAKE A N*N grid TICTACTOE , where N is chosed by the user

//currently it's 3*3 grid TICTACTOE

//#pragma once


// #include "player.h"
// #include "match.h"
// #include "gui.h"


#include "match.cpp"
//#include "player.h"



//may get all of these functions into one single namespace or class called "Game"


class Game
{
public:

    static Game &getInstance()
    {
        static Game game;
        return game;
    }

    
    void setNumberOfMatches();
    void playMultipleMatches();
    void showFinalResult();
    
        
private:

    Game()
        : total_matches(0), total_user_points(0), total_bot_points(0){}


    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    

    std::size_t total_matches;
    std::size_t total_user_points;
    std::size_t total_bot_points;

};







// void Game::showFinalResult(const std::size_t &total_matches, const std::size_t &user_points, const std::size_t &bot_points)
void Game::showFinalResult()   
{

    GUI::pauseExecution("\nPress [ENTER] to see the final result\n");
    
    GUI::print("\n\n\n\n\n\n\n\n\n\n\n\n" , "Final Result: " , "\n\n");
    
    GUI::print("Total Matches : " , total_matches , "\n\n");
    
    GUI::print("Your total points : " , total_user_points , "\n");
    GUI::print("Bots total points : " , total_bot_points , "\n\n");

    //may use human.name instead of "You"
    if(total_user_points > total_bot_points)
    {            
	    GUI::print("You won the game buddy, Take this 🍪 !" , '\n');
        //system("aplay ~/Downloads/game-win-sound1.wav > /dev/null 2>&1 ");
    }
    else if(total_user_points < total_bot_points)
    {      
	    GUI::print("You lost the game! Better try next time!" , '\n');
        //system("aplay ~/Downloads/game-lose-sound1.wav > /dev/null 2>&1 ");
    }
    else if(total_user_points == total_bot_points)
    {	
	    GUI::print("You both deserve 🍪" , '\n');
        //system("aplay ~/Downloads/game-draw-sound1.wav > /dev/null 2>&1");
    }

    GUI::print("\n\n" , "_______________________________________" , "\n\n");
    GUI::print("[Scroll up to check the game history]" , '\n');

}
 


// auto Game::getNumberOfMatches()->std::size_t
// {
//     GUI::clearScreenContent();

//     std::size_t total_matches = 0;
    
//     GUI::print("How many matches You want to go with? : ");
//     User::read_input(total_matches);
    
//     if(total_matches < 0) std::cerr << "Please enter an valid match number!" << '\n'; //may need to update this or remove this

//     return total_matches;
   
// }



void Game::setNumberOfMatches()
{
    GUI::clearScreenContent();    
    
    GUI::print("How many matches You want to go with? : ");
    User::read_input(total_matches);
    
    if(total_matches < 0) std::cerr << "Please enter an valid match number!" << '\n'; //may need to update this or remove this       
}

  




// void playMatch()
// {


// }



void Game::playMultipleMatches()
{
    //std::size_t total_matches = io::getNumberOfMatches();
  
    if(total_matches <= 0) 
    {
       return;
    }
    
    std::string theme = GUI::selectBoardTheme();
    //std::size_t difficulty = TicTacToe::setDifficulty();

    
    // std::size_t total_user_points = 0;
    // std::size_t total_bot_points = 0;

    

    std::size_t match_no = 0;
    //from here will create a another function called 'playMatch(parameters)'
    for(;;)
    {              
      //will show 'match_no' in the showCurrentBoard() function 
	    GUI::print("Match : " , ++match_no , '\n'); 

	    std::size_t difficulty = TicTacToe::setDifficulty();
	
	    TicTacToe match(theme, difficulty);

	    User  user;
        Bot   bot(match.getDifficulty());

	    user.setName();
	    bot.setName();
		
	    std::string first_mover = match.getFirstMover(user.getName(), bot.getName());
		
	    user.setSymbol();
	    bot.setSymbol(user.getSymbol()); //saves the users symbol for further operations

        //bot.user_symbol = user.getSymbol(); // will use bot.setOtherSymbol(user.getSymbol());
        bot.saveUsersSymbol(user.getSymbol());
			
	    GUI::print("bot choosed: ", bot.getSymbol(), '\n');
	    GUI::pauseExecution("\nPress [Enter] to start the match...\n");

	    user.setWinStr();
	    bot.setWinStr();
	
        if(first_mover == user.getName())
        {
	        user.setAsFirstMover();	   
	        match.play(&user, &bot);
        }
        else if(first_mover == bot.getName())
        {
	        bot.setAsFirstMover();	   
	        match.play(&bot, &user);
	    }
	
	    total_user_points += user.getPoints(); 
	    total_bot_points += bot.getPoints();
	        
	    if(match_no == total_matches) break; //total_matches

	    //GUI::pauseExecution("\n\n", "Press [Enter] to play the next match...", '\n');
        GUI::pauseExecution("\n\nPress [Enter] to play the next match...\n");
    }
    

    //showFinalResult(total_matches, total_user_points, total_bot_points);
    
}

































































































