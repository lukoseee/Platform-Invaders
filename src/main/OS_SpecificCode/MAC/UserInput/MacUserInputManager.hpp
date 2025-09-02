#pragma once

#include "../../../AbstractionLayer/OtherInterfaces/UserInputManagerInterface.hpp"
#include "Queue.hpp"
#include "InputView.hpp"

#include <string>
#include <unordered_map>

using namespace std;

/*
 MacUserInputManager sets up receiving of user input and buffers any key
 presses.
 
 See UserInputManagerInterface.
 */
class MacUserInputManager : public UserInputManagerInterface {
public:
    MacUserInputManager();
    ~MacUserInputManager();
    
    UserInput getNextInput(void) override;
    bool isEmpty(void) override;
    
private:
    Queue* mBuff;
    unordered_map<std::string, UserInput>* mInputMap;
};
