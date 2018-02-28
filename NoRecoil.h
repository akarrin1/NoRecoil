
#include "MouseAndKeyboardInput.h"
#include "AsyncKeyEventListener.h"
#include "NoRecoilConfig.h"
#include "windows.h"
#include <memory>

#ifndef NORECOIL_NORECOIL_H
#define NORECOIL_NORECOIL_H

class NoRecoil {
private:
    NoRecoilConfig *config;
    MouseAndKeyboardInput *mouseInput;
    std::unique_ptr<AsyncKeyEventListener> mouseLeftKeyListener, mouseRightKeyListener;
    std::vector<std::shared_ptr<AsyncKeyEventListener>> activatingKeyListeners;
    Weapon *activeWeapon = nullptr;

    void setupKeyListeners() {
        mouseLeftKeyListener = std::make_unique<AsyncKeyEventListener>(VK_LBUTTON);
        mouseLeftKeyListener->setOnKeyPressedCallback([&]() { leftMouseButtonPressed(); });
        mouseLeftKeyListener->setOnKeyReleasedCallback([&]() { leftMouseButtonReleased(); });
        mouseRightKeyListener = std::make_unique<AsyncKeyEventListener>(VK_RBUTTON);
        mouseRightKeyListener->setOnKeyPressedCallback([&]() { rightMouseButtonPressed(); });
        mouseRightKeyListener->setOnKeyReleasedCallback([&]() { rightMouseButtonReleased(); });
        for (auto &weapon : config->weapons) {
            auto listener = std::make_shared<AsyncKeyEventListener>(weapon.activatingKeyCode);
            listener->setOnKeyPressedCallback([&]() { weaponKeyPressed(weapon); });
            listener->setOnKeyReleasedCallback([&]() { weaponKeyReleased(weapon); });
            activatingKeyListeners.push_back(listener);
        }
    }

    void leftMouseButtonPressed() {
        std::cout << "Left mouse button pressed" << std::endl;
        Weapon *capturedActiveWeapon = activeWeapon;
        if (capturedActiveWeapon != nullptr) shootWithWeapon(*capturedActiveWeapon);
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

    void weaponKeyPressed(Weapon &weapon) {
        std::cout << "Weapon " << weapon.name << " key pressed" << std::endl;
        Weapon* capturedActiveWeapon = activeWeapon;
        if (capturedActiveWeapon == nullptr || *capturedActiveWeapon != weapon) {
            activeWeapon = &weapon;
            std::cout << "Weapon " << weapon.name << " activated!" << std::endl;
        } else {
            activeWeapon = nullptr;
        }
    }

    void weaponKeyReleased(Weapon &weapon) {
        std::cout << "Weapon " << weapon.name << " key released" << std::endl;
    }

    void shootWithWeapon(Weapon &weapon) {
        while (shouldConsiderShooting(weapon)) {
            int currentShotNumber = 0;
            while (shouldShoot(weapon, currentShotNumber)) {
                long timestamp = GetCurrentTime();
                unsigned int smoothedShotInterval = weapon.shotInterval / config->moveSmoothness;
                int smoothedShotX = weapon.recoilCoords[currentShotNumber].first / config->moveSmoothness;
                int smoothedShotY = weapon.recoilCoords[currentShotNumber].second / config->moveSmoothness;
                int remainingX = weapon.recoilCoords[currentShotNumber].first - smoothedShotX*config->moveSmoothness;
                int remainingY = weapon.recoilCoords[currentShotNumber].second - smoothedShotY*config->moveSmoothness;
                int remainingInterval = weapon.shotInterval - smoothedShotInterval*config->moveSmoothness;
                for (int i=0 ; i < config->moveSmoothness ; ++i) {
                    Sleep(smoothedShotInterval);
                    mouseInput->moveMouseRelative(smoothedShotX, smoothedShotY);
                }
                Sleep((DWORD)remainingInterval);
                mouseInput->moveMouseRelative(remainingX, remainingY);
                if (!weapon.isAutomatic) {
                    mouseInput->keyboardButtonClick(config->alternativeShotKeyCode);
                    std::cout << "Pressing shot key" << std::endl;
                }
                ++currentShotNumber;
            }
        }
    }

    bool shouldConsiderShooting(Weapon &weapon) {
        return weapon == *activeWeapon &&
               mouseRightKeyListener->isTheKeyPressed();
    }

    bool shouldShoot(Weapon &weapon, int currentShotNumber) {
        return shouldConsiderShooting(weapon) &&
               currentShotNumber < weapon.shotCount &&
               mouseLeftKeyListener->isTheKeyPressed();
    }

public:
    NoRecoil(NoRecoilConfig* config, MouseAndKeyboardInput &mouseInput) {
        this->config = config;
        this->mouseInput = &mouseInput;
    }

    void start() {
        setupKeyListeners();
    }
};

#endif //NORECOIL_NORECOIL_H
