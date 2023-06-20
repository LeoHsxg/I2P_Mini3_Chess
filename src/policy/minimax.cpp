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

//這個東西是minimax
Move get_move(State *state, int depth){
    if(!state->legal_actions.size())
    state->get_legal_actions();
    int num = 0;
    auto actions = state->legal_actions;
    int maxValue = -100000;
    int minValue = 100000;
    if((state->player == 0)){
      for(unsigned long i = 0; i < actions.size(); i++){
        int nextValue = state->next_state(actions[i])->evaluation;
        if(nextValue > maxValue){  // tmp > maxValue
          num = i;
          maxValue = nextValue;
        }
      }
    }
    else if(state->player == 1){
      for(unsigned long i = 0; i < actions.size(); i++){
        int nextValue = state->next_state(actions[i])->evaluation;
        if(nextValue < minValue){  // tmp > maxValue
          num = i;
          minValue = nextValue;
        }
      }
    }
    return actions[num];
}