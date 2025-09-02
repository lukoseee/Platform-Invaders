#include "MacUserInputManager.hpp"

#import <Cocoa/Cocoa.h>
#include "AppDelegate.hpp"
#include "Queue.hpp"
#import "InputView.hpp"

MacUserInputManager::MacUserInputManager() {
    // instantiate a buffer for the game layer to fetch key presses from
    mBuff = [[Queue alloc] init];
    
    // get an instance of the running app
    AppDelegate* appDelegate = (AppDelegate*)[NSApplication sharedApplication].delegate;
    
    // create an InputView to catch user input
    InputView* inputView = [[InputView alloc] initWithFrameAndQueue:appDelegate.mFrame :mBuff];
    
    // set the app's inputView as above. Once the window is created the inputView
    // will be added to the 'scene tree' to catch inputs
    appDelegate.mInputView = inputView;
    
    // instantiate the map between NSStrings and the UserInput enum equivalent
    this->mInputMap = new unordered_map<std::string, UserInput>();
    mInputMap->insert({"a_down", A_DOWN});
    mInputMap->insert({"a_up", A_UP});
    mInputMap->insert({"b_down", B_DOWN});
    mInputMap->insert({"b_up", B_UP});
    mInputMap->insert({"c_down", C_DOWN});
    mInputMap->insert({"c_up", C_UP});
    mInputMap->insert({"d_down", D_DOWN});
    mInputMap->insert({"d_up", D_UP});
    mInputMap->insert({"e_down", E_DOWN});
    mInputMap->insert({"e_up", E_UP});
    mInputMap->insert({"f_down", F_DOWN});
    mInputMap->insert({"f_up", F_UP});
    mInputMap->insert({"g_down", G_DOWN});
    mInputMap->insert({"g_up", G_UP});
    mInputMap->insert({"h_down", H_DOWN});
    mInputMap->insert({"h_up", H_UP});
    mInputMap->insert({"i_down", I_DOWN});
    mInputMap->insert({"i_up", I_UP});
    mInputMap->insert({"j_down", J_DOWN});
    mInputMap->insert({"j_up", J_UP});
    mInputMap->insert({"k_down", K_DOWN});
    mInputMap->insert({"k_up", K_UP});
    mInputMap->insert({"l_down", L_DOWN});
    mInputMap->insert({"l_up", L_UP});
    mInputMap->insert({"m_down", M_DOWN});
    mInputMap->insert({"m_up", M_UP});
    mInputMap->insert({"n_down", N_DOWN});
    mInputMap->insert({"n_up", N_UP});
    mInputMap->insert({"o_down", O_DOWN});
    mInputMap->insert({"o_up", O_UP});
    mInputMap->insert({"p_down", P_DOWN});
    mInputMap->insert({"p_up", P_UP});
    mInputMap->insert({"q_down", Q_DOWN});
    mInputMap->insert({"q_up", Q_UP});
    mInputMap->insert({"r_down", R_DOWN});
    mInputMap->insert({"r_up", R_UP});
    mInputMap->insert({"s_down", S_DOWN});
    mInputMap->insert({"s_up", S_UP});
    mInputMap->insert({"t_down", T_DOWN});
    mInputMap->insert({"t_up", T_UP});
    mInputMap->insert({"u_down", U_DOWN});
    mInputMap->insert({"u_up", U_UP});
    mInputMap->insert({"v_down", V_DOWN});
    mInputMap->insert({"v_up", V_UP});
    mInputMap->insert({"w_down", W_DOWN});
    mInputMap->insert({"w_up", W_UP});
    mInputMap->insert({"x_down", X_DOWN});
    mInputMap->insert({"x_up", X_UP});
    mInputMap->insert({"y_down", Y_DOWN});
    mInputMap->insert({"y_up", Y_UP});
    mInputMap->insert({"z_down", Z_DOWN});
    mInputMap->insert({"z_up", Z_UP});
    mInputMap->insert({"1_down", ONE_DOWN});
    mInputMap->insert({"1_up", ONE_UP});
    mInputMap->insert({"2_down", TWO_DOWN});
    mInputMap->insert({"2_up", TWO_UP});
    mInputMap->insert({"3_down", THREE_DOWN});
    mInputMap->insert({"3_up", THREE_UP});
    mInputMap->insert({"4_down", FOUR_DOWN});
    mInputMap->insert({"4_up", FOUR_UP});
    mInputMap->insert({"5_down", FIVE_DOWN});
    mInputMap->insert({"5_up", FIVE_UP});
    mInputMap->insert({"6_down", SIX_DOWN});
    mInputMap->insert({"6_up", SIX_UP});
    mInputMap->insert({"7_down", SEVEN_DOWN});
    mInputMap->insert({"7_up", SEVEN_UP});
    mInputMap->insert({"8_down", EIGHT_DOWN});
    mInputMap->insert({"8_up", EIGHT_UP});
    mInputMap->insert({"9_down", NINE_DOWN});
    mInputMap->insert({"9_up", NINE_UP});
    mInputMap->insert({"0_down", ZERO_DOWN});
    mInputMap->insert({"0_up", ZERO_UP});
    mInputMap->insert({"left_arrow_down", LEFT_ARROW_DOWN});
    mInputMap->insert({"left_arrow_up", LEFT_ARROW_UP});
    mInputMap->insert({"right_arrow_down", RIGHT_ARROW_DOWN});
    mInputMap->insert({"right_arrow_up", RIGHT_ARROW_UP});
    mInputMap->insert({"up_arrow_down", UP_ARROW_DOWN});
    mInputMap->insert({"up_arrow_up", UP_ARROW_UP});
    mInputMap->insert({"down_arrow_down", DOWN_ARROW_DOWN});
    mInputMap->insert({"down_arrow_up", DOWN_ARROW_UP});
    mInputMap->insert({"return_down", RETURN_DOWN});
    mInputMap->insert({"return_up", RETURN_UP});
    mInputMap->insert({" _down", SPACE_DOWN});
    mInputMap->insert({" _up", SPACE_UP});
    mInputMap->insert({"delete_down", DELETE_DOWN});
    mInputMap->insert({"delete_up", DELETE_UP});
}

UserInput MacUserInputManager::getNextInput() {
    // pop the buffer and convert to C data type
    std::string input = [[mBuff pop] UTF8String];
    
    // if we do not have a mapping for the key, return UNDEFINED
    if(mInputMap->find(input) == mInputMap->end())
        return UNDEFINED;
    
    // return the associated User Input enum value
    return mInputMap->at(input);
}

bool MacUserInputManager::isEmpty() {
    // Objective-C BOOL to C++ sbool
    return [mBuff isEmpty] == YES ? true : false;;
}
