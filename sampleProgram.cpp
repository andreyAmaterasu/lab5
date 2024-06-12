#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string name;
    std::ifstream in;

    std::cout << "Введите имя файла для просмотра: ";
    std::cin >> name;

    in.open(name);
    if (!in) {
        std::cerr << "Файл " << name << " не открыт\n";
    } else {
        char ch;
        while (in.get(ch)) {
            std::cout.put(ch);
        }
        in.close();
    }

    return 0;
}
