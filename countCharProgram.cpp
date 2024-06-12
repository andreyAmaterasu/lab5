#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

void countCharacters(std::ifstream &file, int &emptyCount, int &nonEmptyCount) {
    char ch;
    emptyCount = nonEmptyCount = 0;
    while (file.get(ch)) {
        if (isspace(ch) || iscntrl(ch)) {
            emptyCount++;
        } else {
            nonEmptyCount++;
        }
    }
}

int main() {
    std::string name;
    int emptyCount, nonEmptyCount;

    std::cout << "Введите имя файла для просмотра: ";
    std::cin >> name;

    std::ifstream in(name);
    if (!in.is_open()) {
        std::cerr << "Файл " << name << " не открыт. Т.к. вероятно не существует.\n";
        return 1;
    }

    char ch;
    while (in.get(ch)) {
        std::cout.put(ch);
    }

    in.clear();  // Сброс состояния потока
    in.seekg(0, std::ios::beg);

    countCharacters(in, emptyCount, nonEmptyCount);
    std::cout << "Пустые символы: " << emptyCount << "\n";
    std::cout << "Непустые символы: " << nonEmptyCount << "\n";

    in.close();
    return 0;
}
