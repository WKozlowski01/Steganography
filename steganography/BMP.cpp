#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include <vector>
#include <math.h>
#include <string>
#include "share.hpp"


struct HeaderBMP {
    int DataOffset;
    std::vector<unsigned char> width;
    std::vector<unsigned char> height;
    int imgSize;
    int msgSpace;
};

auto BMPbitSwitch(const char &get, const bool &lsb, const char &msg) -> char {
    if (lsb == 0 and msg == '0') {
        return get;
    } else if (lsb == 0 and msg == '1') {
        return get + 1;

    } else if (lsb == 1 and msg == '0') {
        return get - 1;

    } else if (lsb == 1 and msg == '1') {
        return get;
    }

}

auto littleEndiancout(const std::vector<unsigned char> &vec) -> int {
    auto sum = int();

    sum = {
            static_cast<int>(vec[0] + pow(256, 1) * vec[1] + pow(256, 2) * vec[2] + pow(256, 3) * vec[3])
    };

    return sum;

}

auto BMPspaceCount(int x, int y) -> int {
    return (x * y) * 3;
}

auto BMPszyfrowanie(const std::vector<char> &vec, HeaderBMP &header, std::fstream &file) -> void {
    file.seekg(header.DataOffset, std::ios::beg); // przeuwam wskaźnik na poczatek informacji o kolorach


    auto bajt = char();                 //odczytanie ostatniego bitu na dlugosci przedstawionego tekstu

    for (int i = 0; i < vec.size(); i++) {
        file.get(bajt);
        bool lsb = bajt & 1;
        bajt = BMPbitSwitch(bajt, lsb, vec[i]);
        auto currentPosition = file.tellg(); // Pobierz aktualną pozycję kursora
        file.seekg(-1, std::ios::cur); // Przesuń kursor o jeden bajt wstecz
        file.put(bajt); // Zapisz bajt na tej samej pozycji
        file.seekg(currentPosition); // Przywróć kursor do jego oryginalnej pozycji
    }
}

auto BMPdeszyfrowanie(HeaderBMP header, std::fstream &file) -> void {


    file.seekg(header.DataOffset, std::ios::beg); // przeuwam wskaźnik na poczatek informacji o kolorach
    const int bufferSize = 8;
    char buffer[bufferSize];
    auto txt = std::string();
    auto tmpstr = std::string();
    auto counter =0;
    auto stop = false;

    while (!(tmpstr == "01100000")) {
        tmpstr = std::string();
        file.read(buffer, bufferSize);
        for (int i = 0; i < bufferSize; i++) {
            bool lsb = buffer[i] & 1;
            if (!lsb) {
                tmpstr += "0";
            } else tmpstr += "1";
            counter++;
        }

       txt += tmpstr;
                       if( counter == 16 and  !(txt == "0101111101011110")){
            fmt::print("W obrazie nie ma ukrytej wiadomośći");
            stop = true;
            break;
        }
    }

    if(!stop) {
        try{
            txt = binaryToString(txt);
            txt = txt.substr(2, txt.size() - 3);
            fmt::print("{}", txt);
        }catch (std::exception const& ex){
            fmt::print("BŁĄD!: Program nie obsługuje polskich znaków");
        }

    }
    file.close();
}



auto BMPgetHeaderInfo(std::fstream &file) -> HeaderBMP {

    HeaderBMP headerBmp; // plik naglowkowy


    file.seekg(10, std::ios::beg); // przeuwam wskaźnik;
    file.read(reinterpret_cast<char *>(&headerBmp.DataOffset), sizeof(headerBmp.DataOffset));


    auto tmpWidth = char();     //pobieranie z naglowka szerokosci do wektora
    file.seekg(18, std::ios::beg);
    for (int i = 0; i < 4; i++) {
        file.get(tmpWidth);
        headerBmp.width.push_back(tmpWidth);
    }

    auto tmpHeight = char();    //pobieranie z naglowka wysokosci do wektora
    file.seekg(22, std::ios::beg);
    for (int i = 0; i < 4; i++) {
        file.get(tmpHeight);
        headerBmp.height.push_back(tmpHeight);
    }

    auto height = littleEndiancout(headerBmp.height); //obliczanie wysokosci w pixelach
    auto width = littleEndiancout(headerBmp.width); //oblicznie szerokosci w pixelach
    headerBmp.msgSpace = BMPspaceCount(width, height); // oblicznie miejsca na wiadomosc
    headerBmp.imgSize = height * width;
    return headerBmp;
}