#ifndef CRYPTO_MONITOR_H
#define CRYPTO_MONITOR_H

#include <string>
#include <memory>
#include <atomic>

// using namespace std; // Убрано, чтобы не конфликтовать с windows.h

class CryptoDetector;

class CryptoMonitor
{
private:
    std::unique_ptr<CryptoDetector> detector;
    std::string lastClipboardContent;
    std::atomic<bool> running;

    void processClipboardContent(const std::string &text);

public:
    CryptoMonitor();
    ~CryptoMonitor();

    void monitoringLoop();
    void stop();
};

#endif
