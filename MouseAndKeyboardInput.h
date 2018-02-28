
#include <windows.h>
#include <memory>
#include <string>
#include "DialogCreator.h"

#ifndef NORECOIL_MOUSEINPUT_H
#define NORECOIL_MOUSEINPUT_H

class MouseAndKeyboardInput {
public:

    void moveMouseRelative(int x, int y) {
        mouse_event(MOUSEEVENTF_MOVE, (DWORD)x, (DWORD)y, 0, 0);
        std::cout << "Moving by " << x << " " << y << std::endl;
    }

    void keyboardButtonPress(unsigned int keyCode) {
        keybd_event(keyCode, 0, 0, 0);
    }

    void keyboardButtonRelease(unsigned int keyCode) {
        keybd_event(keyCode, 0, KEYEVENTF_KEYUP, 0);
    }

    void keyboardButtonClick(unsigned int keyCode) {
        keyboardButtonPress(keyCode);
        keyboardButtonRelease(keyCode);
    }
};

#endif //NORECOIL_MOUSEINPUT_H
