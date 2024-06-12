#include <iostream>
#include <fstream>
#include <string>

void encryptFile(const std::string &inputFileName, const std::string &outputFileName, const std::string &key) {
    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!inputFile || !outputFile) {
        std::cerr << "Ошибка открытия файла\n";
        exit(EXIT_FAILURE);
    }

    size_t keyLength = key.size();
    size_t keyIndex = 0;
    char ch;

    while (inputFile.get(ch)) {
        outputFile.put(ch ^ key[keyIndex]);
        keyIndex = (keyIndex + 1) % keyLength;
    }
}

bool compareFiles(const std::string &file1, const std::string &file2) {
    std::ifstream f1(file1, std::ios::binary);
    std::ifstream f2(file2, std::ios::binary);

    if (!f1 || !f2) {
        std::cerr << "Ошибка открытия файла для проверки\n";
        return false;
    }

    std::istreambuf_iterator<char> begin1(f1), begin2(f2), end;
    return std::equal(begin1, end, begin2);
}

int main() {
    std::string inputFileName = "text.txt";
    std::string outputFileName = "output.txt";
    std::string key = "key";

    encryptFile(inputFileName, outputFileName, key);

    std::string decryptedFileName = "decrypted_output.txt";
    encryptFile(outputFileName, decryptedFileName, key);

    if (compareFiles(inputFileName, decryptedFileName)) {
        std::cout << "Проверка пройдена: файл успешно зашифрован и расшифрован.\n";
    } else {
        std::cout << "Проверка не пройдена: расшифрованный файл отличается от исходного.\n";
    }

    return EXIT_SUCCESS;
}
