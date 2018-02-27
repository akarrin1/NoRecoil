#include <windows.h>
#include <string>

using namespace std;

void showErrorDialog(const string& message) {
    MessageBoxA(nullptr, "Error", message.c_str(), MB_OK);
}

void showErrorDialogAndExit(const string& message) {
    showErrorDialog(message);
    exit(-1);
}

int main() {
    HDESK activeDesktop = OpenInputDesktop(0, false, GENERIC_ALL);
    Sleep(10000);
    if (activeDesktop == nullptr) showErrorDialogAndExit("OpenInputDesktop returned nullptr");
    if (!SetThreadDesktop(activeDesktop)) showErrorDialogAndExit("SetThreadDesktop failed");
    if (!SetCursorPos(10, 10)) showErrorDialogAndExit("SetCursorPos failed");
    return 0;
}