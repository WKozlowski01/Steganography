#pragma once
#include <iostream>

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <regex>
#include <fmt/core.h>

enum class Type {
    BMP, PNG, ER
};
struct FileInfo {
    double fileSize;
    Type fileType;
    std::filesystem::file_time_type fileTIme;

};



auto fileInfo(const std::string &filePath) -> FileInfo;
auto fileInfoPrint(const FileInfo &file) -> void;
auto binaryToString(const std::string &bin) -> std::string;
auto msgEncryption(std::string& txt) -> std::vector<char>;