

#include "run_functions.cpp"


int main()
{

    GUI::print("------------------------------- TERMINAL BASED -------------------------------" , "\n\n");
    GUI::print("difficulty : Impossible" , "\n\n");

    //playMultipleMatches();
    

    //may use singleton pattern here
    // Game game;
    
    // game.setNumberOfMatches();
    // game.playMultipleMatches();
    // game.showFinalResult();

    Game &game = Game::getInstance();

    game.setNumberOfMatches();
    game.playMultipleMatches();
    game.showFinalResult();

       

    GUI::print("\n\n" , "THANKS FOR PLAYING!" , "\n\n");

    return EXIT_SUCCESS;
} 















































