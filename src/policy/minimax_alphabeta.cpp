#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax_alphabeta.hpp"


/*
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move minimax( State s, int depth );
int max(State s, int depth, int a, int b);
int min(State s, int depth, int a, int b);

Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  return minimax(*state, depth);
}

Move minimax( State s, int depth ){    
    State* tmp;
    int max=-2000;
    Move m;
    int a=-2000, b=2000;
    for(auto it : s.legal_actions ){
        tmp = s.next_state(it);
        int v= min(*tmp, depth-1, a, b);
        if(v > max){
            max = v;
            m = it;
        }
    }   
    return m;    
}

int max(State s, int depth, int a, int b){
    if(depth==0) return s.evaluate();
    s.get_legal_actions();
    State* tmp;
    int max=-2000, v=0;
    for(auto it : s.legal_actions ){
        tmp = s.next_state(it);
        v= min(*tmp, depth-1, a, b);
        if(max < v)
            max=v;
        if(a < max)
            a=max;    
        delete tmp;
        if(a>=b) break;
    }   
    return max;
}

int min(State s, int depth, int a, int b){
    if(depth==0) return s.evaluate();
    s.get_legal_actions();
    State* tmp;
    int min=2000, v=0;
    for(auto it : s.legal_actions ){
        tmp = s.next_state(it);
        v= max(*tmp, depth-1, a, b);
        if(min > v)
            min=v;
        if(b > min)
            b=min;
        delete tmp;
        if(b <= a) break;
    }   
    return min;
}