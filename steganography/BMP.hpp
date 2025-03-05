#pragma once

#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include <vector>
#include <math.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <regex>
#pragma once
#include <filesystem>
#include <ctime>
#include <chrono>


enum class Type {
    BMP, PNG, ER
};

struct FileInfo {
    double fileSize;
    Type fileType;
    std::filesystem::file_time_type fileTIme;
};

struct HeaderBMP {
    int DataOffset;
    std::vector<unsigned char> width;
    std::vector<unsigned char> height;
    int msgSpace;
};


auto BMPbitSwitch(const char& get,const bool& lsb,const char& msg) -> char;

auto littleEndiancout(const std::vector<unsigned char>& vec) -> int;

auto BMPspaceCount(int x, int y) -> int;

auto BMPszyfrowanie(const std::vector<char>& vec, HeaderBMP& header, std::fstream &file) -> void;

auto BMPdeszyfrowanie(HeaderBMP header, std::fstream &file) -> void;

auto binaryToString(const std::string &bin) -> std::string;

auto msgEncryption(std::string& txt) -> std::vector<char>;

auto fileInfo(const std::string& filePath) -> FileInfo;

auto BMPgetHeaderInfo(std::fstream &file) -> HeaderBMP;

auto fileInfoPrint(const FileInfo& file) -> void;