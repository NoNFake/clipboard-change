#include "CryptoMonitor.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    // Установка кодировки консоли для корректного вывода русского текста
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    CryptoMonitor monitor;

    // Запускаем цикл в основном потоке.
    // Это блокирующий вызов, программа будет работать здесь, пока running == true
    monitor.monitoringLoop();

    return 0;
}
