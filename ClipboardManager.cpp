#include "ClipboardManager.h"
#include <windows.h>
#include <string>
#include <thread>
#include <chrono>

std::string ClipboardManager::getClipboardText()
{
    for (int i = 0; i < 3; ++i)
    {
        if (OpenClipboard(nullptr))
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (i == 2)
            return ""; // Не удалось открыть буфер обмена
    }

    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr)
    {
        CloseClipboard();
        return "";
    }

    char *pszText = static_cast<char *>(GlobalLock(hData));
    std::string text = pszText ? pszText : "";

    GlobalUnlock(hData);
    CloseClipboard();

    return text;
}

void ClipboardManager::setClipboardText(const std::string &text)
{
    if (!OpenClipboard(nullptr))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (!OpenClipboard(nullptr))
            return;
    }

    EmptyClipboard();
    HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, text.size() + 1);
    if (!hGlob)
    {
        CloseClipboard();
        return;
    }

    memcpy(hGlob, text.c_str(), text.size() + 1);
    SetClipboardData(CF_TEXT, hGlob);
    CloseClipboard();
}
