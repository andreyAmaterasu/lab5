#include <iostream>
#include <fstream>
#include <string>

void findString(std::ifstream &in, const std::string &substring, std::ofstream &out) {
    std::string line;
    int lineNumber = 0;
    bool found = false;

    while (std::getline(in, line)) {
        lineNumber++;
        if (line.find(substring) != std::string::npos) {
            found = true;
            out << "Строка " << lineNumber << ": " << line << "\n";
        }
    }

    if (!found) {
        out << "Строка \"" << substring << "\" не найдена в файле.\n";
    }
}

int main() {
    std::string name, substring, outputFile;

    std::cout << "Введите имя файла для просмотра: ";
    std::cin >> name;

    std::ifstream in(name);
    if (!in) {
        std::cerr << "Файл " << name << " не открыт. Т.к. вероятно не существует.\n";
        return 1;
    }

    std::cout << "Введите строку для поиска в файле: ";
    std::cin >> substring;

    std::cout << "Введите имя файла для записи результатов: ";
    std::cin >> outputFile;

    std::ofstream out(outputFile);
    if (!out) {
        std::cerr << "Файл " << outputFile << " не может быть открыт для записи.\n";
        in.close();
        return 1;
    }

    char ch;
    while (in.get(ch)) {
        std::cout.put(ch);
    }

    in.clear();
    in.seekg(0, std::ios::beg);

    findString(in, substring, out);

    std::cout << "\nРезультат поиска записан в файл " << outputFile << "\n";

    in.close();
    out.close();

    std::ifstream result(outputFile);
    if (!result) {
        std::cerr << "Файл " << outputFile << " не может быть открыт для чтения.\n";
        return 1;
    }

    std::cout << "\n=================================================\n";
    std::cout << "Содержимое файла с результатами:\n\n";
    while (result.get(ch)) {
        std::cout.put(ch);
    }
    std::cout << "\n=================================================\n";

    result.close();

    return 0;
}
