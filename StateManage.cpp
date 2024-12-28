#include "StateManage.h"

StateManage::StateManage(): ifAdd(false), ifRemove(false), ifReplace(false) {}
StateManage::~StateManage() = default;

void StateManage::push(unique_ptr<IState> state, bool replace) {
    ifAdd = true;
    newState = std::move(state);
    ifReplace = replace;
}

void StateManage::pop() {
    ifRemove = true;
}

void StateManage::processChanges() {
    if (ifRemoveAll)
    {
        while (!stateStack.empty())
        {
            stateStack.pop();
        }
        ifRemoveAll = false;
    }
    if (ifAdd) {
        if (ifReplace && (!stateStack.empty())) {
            stateStack.pop();
            ifReplace = false;
        }
        stateStack.push(std::move(newState));
        stateStack.top()->init();
        ifAdd = false;
    }
}

void StateManage::popAll() {
    ifRemoveAll = true;
    ifRemove = false;
}


unique_ptr<IState>& StateManage::getCur() {
    return stateStack.top();
}

bool StateManage::isEmpty() {
    return stateStack.empty();
}