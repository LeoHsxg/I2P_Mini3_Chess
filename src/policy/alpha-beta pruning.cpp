#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int choose_move(State *state, int depth, int alpha, int beta, int isMinimaxPlayer, int f){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  if(depth == 0)
     return state->evaluation * (f ? -1 : 1);
  auto actions = state->legal_actions;
  // player
  if(isMinimaxPlayer){
    int maxValue = -100000;
    for(unsigned long i = 0; i < actions.size(); i++){
      int nextValue = choose_move(state->next_state(actions[i]), depth - 1, alpha, beta, false, f);
      maxValue = std::max(maxValue, nextValue);
      alpha = std::max(alpha, maxValue);
      if(alpha >= beta)
        break;
    }
    return maxValue;
  }
  else{
    int minValue = 100000;
    for(unsigned long i = 0; i < actions.size(); i++){
      int nextValue = choose_move(state->next_state(actions[i]), depth - 1, alpha, beta, true, f);
      minValue = std::min(minValue, nextValue);
      beta = std::min(beta, minValue);
      if(beta <= alpha)
        break;
    }
    return minValue;
  }
}