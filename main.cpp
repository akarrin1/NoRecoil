#include <windows.h>
#include <iostream>
#include "MouseInput.h"
#include "NoRecoilConfig.h"
#include "NoRecoil.h"

using namespace std;

int main() {
    NoRecoilConfig config("config.json");
    MouseInput mouseInput;
    NoRecoil(config, mouseInput).start();
    return 0;
}