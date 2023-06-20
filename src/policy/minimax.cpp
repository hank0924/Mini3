#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/*
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move minimax1( State s, int depth );
int max1(State s, int depth);
int min1(State s, int depth);

Move minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  return minimax1(*state, depth);
}

Move minimax1( State s, int depth ){    
    State* tmp;
    int max=-2000;
    Move m;
    for(auto it : s.legal_actions ){
        tmp = s.next_state(it);
        int v= min1(*tmp, depth-1);
        if(v > max){
            max = v;
            m = it;
        }
    }   
    return m;    
}

int max1(State s, int depth){
    if(depth==0) return s.evaluate();
    s.get_legal_actions();
    State* tmp;
    int max=-2000, v=0;
    for(auto it : s.legal_actions ){
        tmp = s.next_state(it);
        v= min1(*tmp, depth-1);
        if(max < v)
            max=v;
        delete tmp;
    }   
    return max;
}

int min1(State s, int depth){
    if(depth==0) return s.evaluate() * (-1);
    s.get_legal_actions();
    State* tmp;
    int min=2000, v=0;
    for(auto it : s.legal_actions ){
        tmp = s.next_state(it);
        v= max1(*tmp, depth-1);
        if(min > v)
            min=v;
        delete tmp;
    }   
    return min;
}