#ifndef CLIPBOARD_MANAGER_H
#define CLIPBOARD_MANAGER_H

#include <string>

class ClipboardManager
{
public:
    static std::string getClipboardText();
    static void setClipboardText(const std::string &text);
};

#endif // CLIPBOARD_MANAGER_H
