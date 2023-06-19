#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./player.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Player::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  int maxValue = -100000, tmp, num = 0;
  auto actions = state->legal_actions;
  for(unsigned long i = 0; i < actions.size(); i++){
    tmp = std::max(maxValue, state->next_state(actions[i])->evaluation);
    if(tmp != maxValue){
      num = i;
      maxValue = tmp;
    }
  }
  return actions[num];
}