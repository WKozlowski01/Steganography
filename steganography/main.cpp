#include <iostream>
#include <fmt/core.h>
#include <string>
#include "BMP.hpp"
#include "PNG.hpp"


auto main(int argc, char *argv[]) -> int {

    auto flag = std::string(argv[1]);

    if (argc == 3) {

        auto inputFilePath = std::string(argv[2]);


        auto file = std::fstream(inputFilePath, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open()) {
            fmt::println("{}", "nie udało sie otworzyć pliku");
            return 1;
        }

        FileInfo fileObject = fileInfo(inputFilePath);

        HeaderBMP headerBmp = BMPgetHeaderInfo(file);

        if (flag == "-i" or (flag.compare("--info") == 0)) {

            switch (fileObject.fileType) {
                case Type::BMP:
                    fileInfoPrint(fileObject);
                    fmt::print("Image size: {} - {} px\n", littleEndiancout(headerBmp.width),
                               littleEndiancout(headerBmp.height));
                    break;
                case Type::PNG:
                    fileInfoPrint(fileObject);
                    getRes(inputFilePath);
                    break;
                case Type::ER:
                    fmt::print("{}", "Nieobsługiwany format pliku");

            }
        } else if (flag == "-d" or (flag.compare("--decrypt") == 0)) {
            std::cout << "DECRYPT\n";

            switch (fileObject.fileType) {
                case Type::BMP:
                    BMPdeszyfrowanie(headerBmp, file);
                    break;
                case Type::PNG:
                    PNGDecryption(inputFilePath);
                    break;
                case Type::ER:
                    fmt::print("{}", "Nieobsługiwany format pliku");
            }

        } else {
            fmt::print("Podano złą flagę lub niepoprwną ilość argumentów, wpisz -h lub --help aby uzyskać pomoc");
        }

    } else if (argc == 4) {

        auto inputFilePath = std::string(argv[2]);


        auto file = std::fstream(inputFilePath, std::ios::binary | std::ios::in | std::ios::out);

        if (!file) {
            fmt::println("{}", "nie udało sie otworzyć pliku, sprawdź poprawność ścieżki lub skorzystaj z --help");
            return 1;
        }
        FileInfo fileObject = fileInfo(inputFilePath);
        HeaderBMP headerBmp = BMPgetHeaderInfo(file);

        auto input = std::string(argv[3]);

        if (flag == "-e" or (flag.compare("--encrypt") == 0)) {
            std::cout << "ENCRYPT\n";

            switch (fileObject.fileType) {
                case Type::BMP:
                    BMPszyfrowanie(msgEncryption(input), headerBmp, file);
                    break;
                case Type::PNG:
                    PNGencryption(msgEncryption(input), inputFilePath);
                    break;
                case Type::ER:
                    fmt::print("{}", "Nieobsługiwany format pliku");
            }

        } else if (flag == "-c" or (flag.compare("--check") == 0)) {
            std::cout << "CHECK\n";

            switch (fileObject.fileType) {
                case Type::BMP:
                    if (msgEncryption(input).size() > headerBmp.msgSpace) {
                        fmt::print("{}", "zbyt mało miejsca na zapisanie wiadomosci\n");
                    } else {
                        fmt::print("{}", "Wiadomość może zostać zapisana\n");
                    }
                    break;
                case Type::PNG:
                    if (msgEncryption(input).size() > PNG_msg_space(inputFilePath)) {
                        fmt::print("{}", "zbyt mało miejsca na zapisanie wiadomosci\n");
                    } else {
                        fmt::print("{}", "Wiadomość może zostać zapisana\n");
                    }
                    break;
                case Type::ER:
                    fmt::print("{}", "Nieobsługiwany format pliku");
            }
        }else {
            fmt::print("Podano złą flagę lub niepoprwną ilość argumentów, wpisz -h lub --help aby uzyskać pomoc");
        }
    }else if (argc == 2 ){
        if (flag.compare("-h") == 0 or (flag.compare("--help") == 0)) {
            fmt::print(
                    "Program służy do ukrywania oraz odczytywania inforamcji w plikach graficznych, Obsługiwane formaty to BMP oraz PNG\n\n"
                    "Aby wyświetlić informacje o pliku należy wprowadzić flagę -i lub --info oraz podać ścieżckę do pliku\n przykładowo: -i C:\\Users\\Jan\\Pulpit\\obraz.PNG\n\n"
                    "Aby ukryć wiadomość w obrazie należy wporwadzić flagę -e lub --encrypt, następnie podać ścieżkę do pliku\n oraz na końcu tekst do zakodowania w cudzysłowiu\n przykładowo: -e C:\\Users\\Jan\\Pulpit\\obraz.PNG \"ssecret MSG\"\n\n"
                    "Aby odczytać ukrytą wiadomość należyt podać flagę -d lub --decrypt oraz podać ścieżkę do pliku\n przykładowo: -d C:\\Users\\Jan\\Pulpit\\obraz.PNG\n\n"
                    "Aby sprawdzić czy wiadomość może zostać zapisana w pliku należy podać flagę -c lub --check oraz ścieżkę do pliku\n przykładowo: -c C:\\Users\\Jan\\Pulpit\\obraz.PNG\n\n"
                    "Aby uzyskać informacje o programie wpisz -h lub --help");
        }else{
            fmt::print("Podano złą flagę lub niepoprwną ilość argumentów, wpisz -h lub --help aby uzyskać pomoc");
        }
    }else{
        fmt::print("Podano złą flagę lub niepoprwną ilość argumentów, wpisz -h lub --help aby uzyskać pomoc");
    }
}



