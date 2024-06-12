#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string name;
    
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

    return 0;
}
