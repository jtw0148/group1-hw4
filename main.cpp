#include <iostream>
#include "bowling_frame.h"
#include <random>
#include <string>

using namespace std;

std::random_device dev_main;
std::mt19937 rng_main(dev_main());

int current_game_total(Bowling_Frame * first_frame)
{
	Bowling_Frame * temp = first_frame;
	int game_total = 0;
	while(temp)
	{
		game_total += temp->frame_score();
		temp = temp->next_frame();
	}
	return game_total;	
}

int main(int argc, char** argv)
{
  int players;
  if(argc > 2){
    std::cout << "too many arguments\n";
    return 1;
  }

  try {
    players = std::stoi(argv[1]);
  } catch (const std::invalid_argument&) {
    std::cout << "something went wrong. try again\n";
    return 1;
  }

  // create frames for players 
  Bowling_Frame* frames[players];
  for(int i = 0; i< players; i++) {
    frames[i] = new Bowling_Frame(1);
    Bowling_Frame* temp = frames[i];
    Bowling_Frame* prev = nullptr;
    for(int j = 2; j< 11; j++) { // set frames 2 - 10
      temp->next_frame(new Bowling_Frame(j));
      prev = temp;
      temp = temp->next_frame();
    }
  }

  // play the game
  for(int i = 0; i< players; i++) {
    std::cout << "--------------------------NEW PLAYER------------------------------\n";
    Bowling_Frame* temp = frames[i];
    for(int j = 0; j< 10; j++) { // play 10 frames
      temp->update_scores();
      cout << "Frame " << temp->frame_num() << ": " << endl
        << " Score 1: " << temp->score1() << endl
        << " Score 2: " << temp->score2() << endl;
      temp = temp->next_frame();
    }
    cout << "Total Score: " << current_game_total(frames[i]) << endl;
  }
  return 0;
}

