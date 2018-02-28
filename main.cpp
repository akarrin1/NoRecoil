#include <windows.h>
#include <iostream>
#include "MouseAndKeyboardInput.h"
#include "NoRecoilConfig.h"
#include "NoRecoil.h"

using namespace std;

int main() {
    NoRecoilConfig* config = new NoRecoilConfig("config.json");
    MouseAndKeyboardInput mouseInput;
    auto noRecoil = new NoRecoil(config, mouseInput);
    noRecoil->start();
    bool xd = true;
    while (xd) {
        cout << "Press enter to reload config" << endl;
        getchar();
        delete noRecoil;
        delete config;
        config = new NoRecoilConfig("config.json");
        noRecoil = new NoRecoil(config, mouseInput);
        noRecoil->start();
    }
    return 0;
}