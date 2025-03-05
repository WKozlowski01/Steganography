#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <regex>
#include <fmt/core.h>
#include <format>
#include <chrono>
enum class Type {
    BMP, PNG, ER
};
struct FileInfo {
    double fileSize;
    Type fileType;
    std::filesystem::file_time_type fileTIme;

};

auto fileInfo(const std::string &filePath) -> FileInfo {

    FileInfo fileinfo;                                  // https://en.cppreference.com/w/cpp/filesystem/last_write_time

    using namespace std::chrono_literals;
    namespace fs = std::filesystem;

    auto fileSize = fs::file_size(filePath);

    auto ftime = std::filesystem::last_write_time(filePath);

    std::filesystem::last_write_time(filePath, ftime + 2h);
    ftime = std::filesystem::last_write_time(filePath);
    fileinfo.fileTIme = ftime;
    std::filesystem::last_write_time(filePath, ftime - 2h);


    std::regex filetypeBMP(".*\\.(BMP|bmp)");
    std::regex filetypePNG(".*\\.[PNG|png]");
    if (std::regex_search(filePath, filetypeBMP))
        fileinfo.fileType = Type::BMP;
    else if (std::regex_search(filePath, filetypePNG))
        fileinfo.fileType = Type::PNG;
    else {
        fileinfo.fileType = Type::ER;
    }
    fileinfo.fileSize = fileSize;

    return fileinfo;
}

auto fileInfoPrint(const FileInfo &file) -> void {


     fmt::print("{}", std::format("File write time is {}\n", file.fileTIme));

    if (file.fileSize >= 1048576) {
        fmt::print("File size: {:.2f} MB\n", (file.fileSize / 1048576.0));
    } else if (file.fileSize >= 1024) {
        fmt::print("File size: {:.2f} KB\n", (file.fileSize / 1024.0));
    } else {
        fmt::print("File size: {:.2f} B\n", file.fileSize);
    }

    if (file.fileType == Type::BMP) {
        fmt::println("File type is: BMP");
    } else if (file.fileType == Type::PNG) {
        fmt::println("File type is: PNG");
    } else if (file.fileType == Type::ER) {
        fmt::println("Niobsługiwany format pliku");
    }
}


auto binaryToString(const std::string &bin) -> std::string {   // https://cplusplus.com/forum/beginner/154597/
    std::string result;
    std::istringstream input(bin);
    std::bitset<8> bits;
    while (input >> bits) {
        result += char(bits.to_ulong());
    }
    return result;
}

auto msgEncryption(std::string& txt) -> std::vector<char> {

    std::string stopSing = "`";
    std::string startSign = "_^";

    txt += stopSing;
    txt.insert(0,startSign);

    auto result = std::string();
    for (auto x: txt) {
        result += fmt::format("{:08b}", x);
    }
    auto vecZeStr = std::vector<char>(result.begin(), result.end());

    return vecZeStr;


}