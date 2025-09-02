#pragma once

#include <string>


/*
 Enum for user input key presses. Used as constants to communicate which keys
 are pressed/released between the library and the game layer.
 
 Contains enums for all letters in the alphabet, all numbers, the RETURN key
 and the arrow keys. Enums are seperated by key presses (KEY_UP) and key
 releases (KEY_DOWN)
 */
enum UserInput {
    A_DOWN,
    A_UP,
    B_DOWN,
    B_UP,
    C_DOWN,
    C_UP,
    D_DOWN,
    D_UP,
    E_DOWN,
    E_UP,
    F_DOWN,
    F_UP,
    G_DOWN,
    G_UP,
    H_DOWN,
    H_UP,
    I_DOWN,
    I_UP,
    J_DOWN,
    J_UP,
    K_DOWN,
    K_UP,
    L_DOWN,
    L_UP,
    M_DOWN,
    M_UP,
    N_DOWN,
    N_UP,
    O_DOWN,
    O_UP,
    P_DOWN,
    P_UP,
    Q_DOWN,
    Q_UP,
    R_DOWN,
    R_UP,
    S_DOWN,
    S_UP,
    T_DOWN,
    T_UP,
    U_DOWN,
    U_UP,
    V_DOWN,
    V_UP,
    W_DOWN,
    W_UP,
    X_DOWN,
    X_UP,
    Y_DOWN,
    Y_UP,
    Z_DOWN,
    Z_UP,
    ONE_DOWN,
    ONE_UP,
    TWO_DOWN,
    TWO_UP,
    THREE_DOWN,
    THREE_UP,
    FOUR_DOWN,
    FOUR_UP,
    FIVE_DOWN,
    FIVE_UP,
    SIX_DOWN,
    SIX_UP,
    SEVEN_DOWN,
    SEVEN_UP,
    EIGHT_DOWN,
    EIGHT_UP,
    NINE_DOWN,
    NINE_UP,
    ZERO_DOWN,
    ZERO_UP,
    LEFT_ARROW_DOWN,
    LEFT_ARROW_UP,
    RIGHT_ARROW_DOWN,
    RIGHT_ARROW_UP,
    UP_ARROW_DOWN,
    UP_ARROW_UP,
    DOWN_ARROW_DOWN,
    DOWN_ARROW_UP,
    RETURN_DOWN,
    RETURN_UP,
    SPACE_DOWN,
    SPACE_UP,
    DELETE_DOWN,
    DELETE_UP,
    UNDEFINED
};

/*
 UserInputManagerInterface provides a platform-agnostic mechanism for the
 game layer to 'fetch' user input.
 
 Implementations of this interface function as a buffer storing any user
 inputs. The game layer can then poll the buffer and process the input as
 needed.
 
 Currently only keypresses are supported, not mouseclicks.
 */
class UserInputManagerInterface {
public:
    // poll the buffer for the next input
    virtual UserInput getNextInput(void) = 0;
    
    // check if there are no inputs in the buffer
    virtual bool isEmpty(void) = 0;
};
