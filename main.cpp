#include <windows.h>
#include "MouseInput.h"

using namespace std;

int main() {
    Sleep(5000);
    MouseInput().moveRelative(50, 50);
    return 0;
}