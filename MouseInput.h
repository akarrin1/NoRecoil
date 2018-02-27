
#include <windows.h>
#include <memory>
#include <string>
#include "DialogCreator.h"

#ifndef NORECOIL_MOUSEINPUT_H
#define NORECOIL_MOUSEINPUT_H

class MouseInput {
private:
    const int NUMBER_OF_RETRIES = 5;
    const std::unique_ptr<INPUT> relativeMouseMoveInput = std::make_unique<INPUT>();

    void setupRelativeMouseMoveInput() {
        relativeMouseMoveInput->type = INPUT_MOUSE;
        relativeMouseMoveInput->mi.mouseData = 0;
        relativeMouseMoveInput->mi.dwFlags = MOUSEEVENTF_MOVE;
        relativeMouseMoveInput->mi.time = 0;
        relativeMouseMoveInput->mi.dwExtraInfo = 0;
    }

    void showAddMouseEventErrorAndExit() {
        std::string errorMessage = "Couldn't add mouse event after " + std::to_string(NUMBER_OF_RETRIES) + " retries";
        DialogCreator::showErrorDialogAndExit(errorMessage);
    }

public:

    MouseInput() {
        setupRelativeMouseMoveInput();
    }

    void moveRelative(int x, int y) {
        INPUT input = *relativeMouseMoveInput;
        input.mi.dx = x;
        input.mi.dy = y;
        for(int i=0 ; i<NUMBER_OF_RETRIES ; ++i) {
            if (SendInput(1, &input, sizeof(input))) return;
        }
        showAddMouseEventErrorAndExit();
    }
};

#endif //NORECOIL_MOUSEINPUT_H
