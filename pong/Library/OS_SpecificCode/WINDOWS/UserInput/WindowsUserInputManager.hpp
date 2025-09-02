#pragma once
#pragma comment(lib, "d2d1")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "d2d1.lib")
#include "../../../AbstractionLayer/OtherInterfaces/UserInputManagerInterface.hpp"
#include <string>
#include <queue>
#include <windows.h>
#include <wincodec.h>
#include <d2d1.h>
#include <iostream>

class WindowsUserInputManager : public UserInputManagerInterface {
public:
    static WindowsUserInputManager* getInstance();

    UserInput getNextInput(void) override;
    bool isEmpty(void) override;
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam);

private:
    WindowsUserInputManager();
    ~WindowsUserInputManager();

	//prevent copying of singleton
    WindowsUserInputManager(const WindowsUserInputManager&) = delete; 
    WindowsUserInputManager& operator=(const WindowsUserInputManager&) = delete; 

	std::queue<UserInput> mInputBufferDirect2d; //buffer for input

	static UserInput mapKeyToUserInput(WPARAM wParam, bool isKeyDown); //make it static to allow it to be called from WndProc

	static WindowsUserInputManager* sInstance; //singleton instance
};
