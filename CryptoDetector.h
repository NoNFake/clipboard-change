#ifndef CRYPTO_DETECTOR_H
#define CRYPTO_DETECTOR_H

#include <string>
#include <vector>
#include <regex>

class CryptoDetector
{
private:
    std::vector<std::regex> cryptoPatterns;
    void initPatterns();
    bool hasCryptoLikeStructure(const std::string &text);

public:
    CryptoDetector();
    bool isCryptoAddress(const std::string &text);
    std::string getAddressType(const std::string &address);

    static bool isBitcoinAddress(const std::string &address);
    static bool isEthereumAddress(const std::string &address);
    static bool isLitecoinAddress(const std::string &address);
    static bool isTronAddress(const std::string &address);
    static bool isMoneroAddress(const std::string &address);
};

#endif
