//Author: Joseph Lowman

#include "bird.hh"
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

// The field is 25 lines tall
// and 30 characters wide
std::string field =R"(
         ***                 
         ***                 
         ***                 
         ***                 
         ***                 
         ***                 
         ***                 
                              
                              
                              
                              
                              
                              
                              
                 ***          
                 ***          
                 ***          
                 ***          
                 ***          
                 ***          
                 ***          
                 ***          
                 ***          
                 ***          
                 ***          
------------------------------
    )";

std::string field_bird_ground =R"(
"
         ***                 
         ***                 
         ***                 
         ***                 
         ***                 
         ***                 
         ***                 
                              
                              
                              
                              
                              
                              
                              
                 ***          
                 ***          
                 ***          
                 ***          
                 ***          
                 ***          
                 ***         
                 ***         
<oooo>           ***         
//               ***         
//               ***                  
------------------------------
    )";

// The bird is 3 lines tall
// and 7 characters wide
std::string bird_wing_down = R"(
<oooo>
//
//)";


std::string bird_wing_up = R"(
\\
\\
<oooo>
)";


void draw_bird(int height, bool is_up)
{
    std::string output;

    if (is_up)
    {
        std::cout << bird_wing_up << std::endl;
    }
    else{
        std::cout << bird_wing_down << std::endl;
    }

    for (int i = 0; i < height; i++)
    {
        std::cout << "\n" << std::endl;
    }
}

double get_high_score()
{
    // TODO: Read file
    // filename = "data/high_score.out";
    // read last score from file
    double score = 0;

    std::ifstream in_file;
    double line;
    int num;
    double total;
    
    in_file.open("data/high_score.out");
    if (!in_file) {
        std::cerr << "Problem opening file" << std::endl;
        return 1;
    }
    in_file >> line >> total;
    std::cout << line << std::endl;
    // std::cout << num << std::endl;
    // std::cout << total << std::endl;
    in_file.close();


    return score;
}

void show_menu()
{
    std::cout << "_______________________________" << std::endl;

    std::cout << "\n\nWelcome to Flappy Bird!\n" << std::endl;
    std::cout << "\nHigh Score: " << get_high_score() << std::endl;

    std::cout << "\nSelect an option: " << std::endl;
    std::cout << "\t [n] New Game" << std::endl;
    // std::cout << "\t [2] Show con" << std::endl;
    std::cout << "\t [q] Quit" << std::endl;

}

void start_game()
{
    std::cout << "Starting game..." << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));

    std::string user_choice {" "};

    while (user_choice != std::string("q"))
    {
        draw_bird(0, true);
        std::this_thread::sleep_for (std::chrono::seconds(1));

        draw_bird(0, false);
        std::this_thread::sleep_for (std::chrono::seconds(1));

        user_choice = "q";
    }

    return;
}


int main()
{
    show_menu();

    // Read in
    std::string user_choice {"n"};

    if (user_choice == std::string("n"))
    {
        start_game();
    }

    return 0;
}