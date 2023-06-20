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
  int maxValue = -100000, num = 0;
  auto actions = state->legal_actions;
  for(unsigned long i = 0; i < actions.size(); i++){
    int nextValue = choose_move(state->next_state(actions[i]), depth, -10000, 10000, false);
    if(nextValue > maxValue){  // tmp > maxValue
      num = i;
      maxValue = nextValue;
    }
  }
  return actions[num];
}

int Player::choose_move(State *state, int depth, int alpha, int beta, int isMinimaxPlayer){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  if(depth == 0 || state->game_state == DRAW || state->game_state == WIN)
     return state->evaluation;
  auto actions = state->legal_actions;
  // player
  if(isMinimaxPlayer){
    int maxValue = -100000;
    for(unsigned long i = 0; i < actions.size(); i++){
      int nextValue = choose_move(state->next_state(actions[i]), depth - 1, alpha, beta, false);
      maxValue = std::max(maxValue, nextValue);
      // parameter(參數) can be modify!!!
      alpha = std::max(alpha, maxValue);
      // opponent will choose thier best way, that is, our worst way.
      // (When move was too good, opponent will avoid it)
      // We choose the best way only if it is root. And that is get_move's job.
      // Hence we can, and we should cut the better way.
      if(alpha >= beta)
        break;
    }
    return maxValue;
  }
  else{
    int minValue = 100000;
    for(unsigned long i = 0; i < actions.size(); i++){
      int nextValue = choose_move(state->next_state(actions[i]), depth - 1, alpha, beta, true);
      minValue = std::min(minValue, nextValue);
      beta = std::min(beta, minValue);
      if(beta <= alpha)
        break;
    }
    return minValue;
  }
}

// minimax
/*
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
      maxValue = std::max(maxValue, nextValue);
    }
    return maxValue;
  }
  else{
    int minValue = 100000;
    for(unsigned long i = 0; i < actions.size(); i++){
      int nextValue = choose_move(state->next_state(actions[i]), depth - 1, true);
      minValue = std::min(minValue, nextValue);
    }
    return minValue;
  }
}

*/

// evaluate
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