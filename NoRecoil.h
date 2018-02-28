
#include "MouseInput.h"
#include "AsyncKeyEventListener.h"
#include "NoRecoilConfig.h"
#include "windows.h"
#include <memory>

#ifndef NORECOIL_NORECOIL_H
#define NORECOIL_NORECOIL_H

class NoRecoil {
private:
    NoRecoilConfig* config;
    MouseInput* mouseInput;
    std::unique_ptr<AsyncKeyEventListener> mouseLeftKeyListener, mouseRightKeyListener;
    std::vector<std::shared_ptr<AsyncKeyEventListener>> activatingKeyListeners;
    Weapon* activeWeapon = nullptr;

    void setupKeyListeners() {
        mouseLeftKeyListener = std::make_unique<AsyncKeyEventListener>(VK_LBUTTON);
        mouseLeftKeyListener->setOnKeyPressedCallback([&](){ leftMouseButtonPressed(); });
        mouseLeftKeyListener->setOnKeyReleasedCallback([&](){ leftMouseButtonReleased(); });
        mouseRightKeyListener = std::make_unique<AsyncKeyEventListener>(VK_RBUTTON);
        mouseRightKeyListener->setOnKeyPressedCallback([&](){ rightMouseButtonPressed(); });
        mouseRightKeyListener->setOnKeyReleasedCallback([&](){ rightMouseButtonReleased(); });
        for (auto& weapon : config->weapons) {
            auto listener = std::make_shared<AsyncKeyEventListener>(weapon.activatingKeyCode);
            listener->setOnKeyPressedCallback([&]() { weaponKeyPressed(weapon); });
            listener->setOnKeyReleasedCallback([&]() { weaponKeyReleased(weapon); });
            activatingKeyListeners.push_back(listener);
        }
    }

    void leftMouseButtonPressed() {
        std::cout << "Left mouse button pressed" << std::endl;
    }

    void leftMouseButtonReleased() {
        std::cout << "Left mouse button released" << std::endl;
    }

    void rightMouseButtonPressed() {
        std::cout << "Right mouse button pressed" << std::endl;
    }

    void rightMouseButtonReleased() {
        std::cout << "Right mouse button released" << std::endl;
    }

    void weaponKeyPressed(Weapon& weapon) {
        std::cout << "Weapon " << weapon.name << " key pressed" << std::endl;
    }

    void weaponKeyReleased(Weapon& weapon) {
        std::cout << "Weapon " << weapon.name << " key released" << std::endl;
    }

public:
    NoRecoil(NoRecoilConfig& config, MouseInput& mouseInput) {
        this->config = &config;
        this->mouseInput = &mouseInput;
    }

    void start() {
        setupKeyListeners();
        while (true) Sleep(1);
    }
};

#endif //NORECOIL_NORECOIL_H
