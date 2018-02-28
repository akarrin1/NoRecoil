
#include <windows.h>
#include <thread>
#include <functional>
#include <utility>

#ifndef NORECOIL_KEYEVENTLISTENER_H
#define NORECOIL_KEYEVENTLISTENER_H

class AsyncKeyEventListener {
private:
    int virtualKeyCode;
    bool isListening = true;
    std::thread listenerThread;
    std::function<void()> onKeyPressedCallback;
    std::function<void()> onKeyReleasedCallback;

    void listenerLoop() {
        bool keyWasPressed = isTheKeyPressed();
        while (isListening) {
            if (keyWasPressed != isTheKeyPressed()) {
                keyWasPressed = !keyWasPressed;
                if (keyWasPressed) {
                    onKeyPressedCallback();
                } else {
                    onKeyReleasedCallback();
                }
            }
            Sleep(5);
        }
    }

public:
    explicit AsyncKeyEventListener(int virtualKeyCode) {
        this->virtualKeyCode = virtualKeyCode;
        listenerThread = std::thread(&AsyncKeyEventListener::listenerLoop, this);
    }
    AsyncKeyEventListener(const AsyncKeyEventListener&) = delete;
    AsyncKeyEventListener& operator=(const AsyncKeyEventListener&) = delete;

    ~AsyncKeyEventListener() {
        isListening = false;
        listenerThread.join();
    }

    bool isTheKeyPressed() {
        return GetAsyncKeyState(virtualKeyCode) < 0;
    }

    void setOnKeyPressedCallback(std::function<void()> callback) {
        onKeyPressedCallback = std::move(callback);
    }

    void setOnKeyReleasedCallback(std::function<void()> callback) {
        onKeyReleasedCallback = std::move(callback);
    }
};

#endif //NORECOIL_KEYEVENTLISTENER_H
