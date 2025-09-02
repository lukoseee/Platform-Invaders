#pragma once
#include  "../Visuals/D2dRenderer.hpp"
#include "WindowsUserInputManager.hpp"


WindowsUserInputManager* WindowsUserInputManager::sInstance = nullptr;

WindowsUserInputManager* WindowsUserInputManager::getInstance() {
    //returns sInstance of singleton
    if (!sInstance) {
        sInstance = new WindowsUserInputManager();
    }
    return sInstance;
}

WindowsUserInputManager::WindowsUserInputManager() {}

WindowsUserInputManager::~WindowsUserInputManager() {}

UserInput WindowsUserInputManager::mapKeyToUserInput(WPARAM wParam, bool isKeyDown) {
    switch (wParam) {

        case 'A': return isKeyDown ? A_DOWN : A_UP;
        case 'B': return isKeyDown ? B_DOWN : B_UP;
        case 'C': return isKeyDown ? C_DOWN : C_UP;
        case 'D': return isKeyDown ? D_DOWN : D_UP;
        case 'E': return isKeyDown ? E_DOWN : E_UP;
        case 'F': return isKeyDown ? F_DOWN : F_UP;
        case 'G': return isKeyDown ? G_DOWN : G_UP;
        case 'H': return isKeyDown ? H_DOWN : H_UP;
        case 'I': return isKeyDown ? I_DOWN : I_UP;
        case 'J': return isKeyDown ? J_DOWN : J_UP;
        case 'K': return isKeyDown ? K_DOWN : K_UP;
        case 'L': return isKeyDown ? L_DOWN : L_UP;
        case 'M': return isKeyDown ? M_DOWN : M_UP;
        case 'N': return isKeyDown ? N_DOWN : N_UP;
        case 'O': return isKeyDown ? O_DOWN : O_UP;
        case 'P': return isKeyDown ? P_DOWN : P_UP;
        case 'Q': return isKeyDown ? Q_DOWN : Q_UP;
        case 'R': return isKeyDown ? R_DOWN : R_UP;
        case 'S': return isKeyDown ? S_DOWN : S_UP;
        case 'T': return isKeyDown ? T_DOWN : T_UP;
        case 'U': return isKeyDown ? U_DOWN : U_UP;
        case 'V': return isKeyDown ? V_DOWN : V_UP;
        case 'W': return isKeyDown ? W_DOWN : W_UP;
        case 'X': return isKeyDown ? X_DOWN : X_UP;
        case 'Y': return isKeyDown ? Y_DOWN : Y_UP;
        case 'Z': return isKeyDown ? Z_DOWN : Z_UP;

        case '1': return isKeyDown ? ONE_DOWN : ONE_UP;
        case '2': return isKeyDown ? TWO_DOWN : TWO_UP;
        case '3': return isKeyDown ? THREE_DOWN : THREE_UP;
        case '4': return isKeyDown ? FOUR_DOWN : FOUR_UP;
        case '5': return isKeyDown ? FIVE_DOWN : FIVE_UP;
        case '6': return isKeyDown ? SIX_DOWN : SIX_UP;
        case '7': return isKeyDown ? SEVEN_DOWN : SEVEN_UP;
        case '8': return isKeyDown ? EIGHT_DOWN : EIGHT_UP;
        case '9': return isKeyDown ? NINE_DOWN : NINE_UP;
        case '0': return isKeyDown ? ZERO_DOWN : ZERO_UP;

        case VK_LEFT:   return isKeyDown ? LEFT_ARROW_DOWN : LEFT_ARROW_UP;
        case VK_RIGHT:  return isKeyDown ? RIGHT_ARROW_DOWN : RIGHT_ARROW_UP;
        case VK_UP:     return isKeyDown ? UP_ARROW_DOWN : UP_ARROW_UP;
        case VK_DOWN:   return isKeyDown ? DOWN_ARROW_DOWN : DOWN_ARROW_UP;

        case VK_RETURN: return isKeyDown ? RETURN_DOWN : RETURN_UP;
        case VK_SPACE:  return isKeyDown ? SPACE_DOWN : SPACE_UP;
        case VK_BACK:   return isKeyDown ? DELETE_DOWN : DELETE_UP;


        default: return UNDEFINED;
    }
}



bool WindowsUserInputManager::isEmpty() {
    return mInputBufferDirect2d.empty();
}

UserInput WindowsUserInputManager:: getNextInput() {
    if (mInputBufferDirect2d.empty()) {
        return UNDEFINED;
    }
    UserInput input = mInputBufferDirect2d.front();
    mInputBufferDirect2d.pop();
    return input;
};

LRESULT CALLBACK WindowsUserInputManager:: WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE) {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        D2dRenderer* ptr = (D2dRenderer*)pcs->lpCreateParams;

        //Setter
        ::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
        result = 1;
    }
    else {
        D2dRenderer* ptr = reinterpret_cast<D2dRenderer*>(static_cast<LONG_PTR>(

            //Getter
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            )));

        bool wasHandled = false;

        if (ptr) {
            switch (message) {
            case WM_SIZE: {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                ptr->resizeWindow(width, height);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_DISPLAYCHANGE: {
                InvalidateRect(hwnd, NULL, FALSE);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_PAINT: {
                    
                ValidateRect(hwnd, NULL);

            }
            result = 0;
            wasHandled = true;
            break;

            case WM_DESTROY: {
				ptr->closeWindow();
            }
            result = 1;
            wasHandled = true;
            break;
            // keyboard input handling
            case WM_KEYDOWN: {
               
				UserInput input = mapKeyToUserInput(wParam, true);

                // push to queue as string
                getInstance()->mInputBufferDirect2d.push(input);

            }
            result = 0;
            wasHandled = true;
            break;

            case WM_KEYUP: {

                UserInput input = mapKeyToUserInput(wParam, false);

                // push to queue as string
                getInstance()->mInputBufferDirect2d.push(input);
            }
            result = 0;
            wasHandled = true;
            break;


            }
        }
        if (!wasHandled) {
            result = DefWindowProc(hwnd, message, wParam, lParam);
        }
    }
    return result;
}


