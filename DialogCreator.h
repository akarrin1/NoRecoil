
#include <string>
#include <windows.h>

#ifndef NORECOIL_DIALOGCREATOR_H
#define NORECOIL_DIALOGCREATOR_H

class DialogCreator {
public:
    static void showErrorDialog(const std::string& message) {
        MessageBoxA(nullptr, "Error", message.c_str(), MB_OK);
    }

    static void showErrorDialogAndExit(const std::string& message) {
        showErrorDialog(message);
        exit(-1);
    }
};

#endif //NORECOIL_DIALOGCREATOR_H
