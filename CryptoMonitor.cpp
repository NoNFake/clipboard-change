#include "CryptoDetector.h"
#include "CryptoMonitor.h"
#include "ClipboardManager.h"

#include <iostream>
#include <chrono>
#include <algorithm>
#include <thread>

using namespace std;

CryptoMonitor::CryptoMonitor()
{
    detector = make_unique<CryptoDetector>();
    running = true;
    // Удален поток из конструктора, так как используется monitoringLoop в main
}

CryptoMonitor::~CryptoMonitor()
{
    stop();
}

void CryptoMonitor::stop()
{
    running = false;
}

void CryptoMonitor::monitoringLoop()
{
    cout << "Start monitoring..." << endl;
    while (running)
    {
        std::string currentText = ClipboardManager::getClipboardText();

        // Проверка changed и non-empty
        if (!currentText.empty() && currentText != lastClipboardContent)
        {
            lastClipboardContent = currentText; // Сначала обновляем, чтобы избежать повторов
            processClipboardContent(currentText);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void CryptoMonitor::processClipboardContent(const std::string &content)
{
    // Очистка текста
    std::string cleanText = content;
    cleanText.erase(std::remove(cleanText.begin(), cleanText.end(), ' '), cleanText.end());
    cleanText.erase(std::remove(cleanText.begin(), cleanText.end(), '\n'), cleanText.end());
    cleanText.erase(std::remove(cleanText.begin(), cleanText.end(), '\r'), cleanText.end());

    if (detector->isCryptoAddress(cleanText))
    {
        std::string addressType = detector->getAddressType(cleanText);

        std::cout << "\n[Detect" << std::endl;
        std::cout << "Address: " << cleanText << std::endl; // Показываем весь адрес для дебага
        std::cout << "type: " << addressType << std::endl;
        std::cout << "lenght: " << cleanText.length() << " symbols" << std::endl;
    }
}
