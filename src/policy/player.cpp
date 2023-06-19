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
  // if(depth == 0 || state->game_state == DRAW || state->game_state == WIN)
  //   return num;
  for(unsigned long i = 0; i < actions.size(); i++){
    int nextValue = choose_move(state->next_state(actions[i]), depth, false);
    tmp = std::max(maxValue, nextValue);
    if(tmp != maxValue){
      num = i;
      maxValue = tmp;
    }
  }
  return actions[num];
}

int Player::choose_move(State *state, int depth, int isMinimaxPlayer){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  if(depth == 0 || state->game_state == DRAW || state->game_state == WIN)
     return state->evaluation;
  int tmp;
  auto actions = state->legal_actions;
  if(isMinimaxPlayer){
    int maxValue = -100000;
    for(unsigned long i = 0; i < actions.size(); i++){
      int nextValue = choose_move(state->next_state(actions[i]), depth - 1, false);
      tmp = std::max(maxValue, nextValue);
    }
    return maxValue;
  }
  else{
    int minValue = 100000;
    for(unsigned long i = 0; i < actions.size(); i++){
      int nextValue = choose_move(state->next_state(actions[i]), depth - 1, true);
      tmp = std::min(minValue, nextValue);
    }
    return minValue;
  }
}

/*
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
*/