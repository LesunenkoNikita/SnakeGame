#ifndef STATEMANAGE_H
#define STATEMANAGE_H
#include <stack>
#include <memory>
#include "IState.h"
using namespace std;

class StateManage {
public:
    StateManage();
    ~StateManage();
    void push(unique_ptr<IState> state, bool replace = false);
    void pop();
    void popAll();
    void processChanges();
    unique_ptr<IState>& getCur();
    bool isEmpty();
private:
    stack<unique_ptr<IState>> stateStack;
    unique_ptr<IState> newState;
    bool ifAdd;
    bool ifReplace;
    bool ifRemove;
    bool ifRemoveAll;
};


#endif //STATEMANAGE_H
