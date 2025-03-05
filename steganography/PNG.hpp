#pragma once
#include <vector>


auto PNGbitSwitch(const char& get,const bool& lsb, const char& msg) -> char;

auto uzupelnienie(const std::vector<char> &vec)->void;

auto PNGencryption(const std::vector<char>& vec,const std::string& filePath)->void;

auto PNGDecryption(const std::string& filePath)->void;

auto getRes(const std::string& filePath)->void;

auto PNG_msg_space(const std::string &filePath)->int;
