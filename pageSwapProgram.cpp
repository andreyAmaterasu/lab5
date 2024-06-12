#include <iostream>
#include <fstream>
#include <string>

void processFile(std::ifstream &in, std::ofstream &out) {
    std::string line;
    std::string pageNumber;
    bool isFirstLine = true;
    bool firstLineOfFile = true;

    while (std::getline(in, line)) {
        // Проверка на начало новой страницы
        if (line.size() > 2 && line[0] == '-' && line[1] == ' ') {
            if (!firstLineOfFile) {
                // Добавляем номер страницы в конец предыдущей страницы
                out << pageNumber << "\n";
            }
            // Извлекаем номер страницы из первой строки
            pageNumber = line.substr(2, line.size() - 4); // Извлечение номера страницы
            isFirstLine = true;
            firstLineOfFile = false;
        } else {
            // Обычные строки копируем в выходной файл
            out << line << "\n";
            isFirstLine = false;
        }
    }

    // Добавляем номер последней страницы, если он есть
    if (!firstLineOfFile) {
        out << pageNumber << "\n";
    }
}

int main() {
    std::string inputFile, outputFile;

    std::cout << "Введите имя исходного файла: ";
    std::cin >> inputFile;

    std::cout << "Введите имя выходного файла: ";
    std::cin >> outputFile;

    std::ifstream in(inputFile);
    if (!in) {
        std::cerr << "Файл " << inputFile << " не может быть открыт.\n";
        return 1;
    }

    std::ofstream out(outputFile);
    if (!out) {
        std::cerr << "Файл " << outputFile << " не может быть открыт для записи.\n";
        return 1;
    }

    processFile(in, out);

    std::cout << "Обработка завершена. Результаты сохранены в " << outputFile << "\n";

    in.close();
    out.close();

    // Снова открываем файл для чтения и вывода результатов в консоль
    std::ifstream result(outputFile);
    if (!result) {
        std::cerr << "Файл " << outputFile << " не может быть открыт для чтения.\n";
        return 1;
    }

    std::cout << "\n=================================================\n";
    std::cout << "Содержимое файла с результатами:\n\n";
    std::cout << result.rdbuf();
    std::cout << "\n=================================================\n";

    result.close();

    return 0;
}
