#include <fmt/core.h>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "BMP.hpp"



auto PNGbitSwitch(const char &get, const bool &lsb, const char &msg) -> char {
    if (lsb == 0 and msg == '0') {
        return get;
    } else if (lsb == 0 and msg == '1') {
        return get + 1;

    } else if (lsb == 1 and msg == '0') {
        return get - 1;

    } else if (lsb == 1 and msg == '1') {
        return get;
    } else {
        return get;
    }

}

auto PNG_msg_space(const std::string &filePath) {

    sf::Image image;
    image.loadFromFile(filePath);
    auto vec = std::vector<int>();
    auto imRes = image.getSize();
    auto width = imRes.x;
    auto height = imRes.y;
    auto space = (width * height) * 3;
    return space;
}


auto uzupelnienie(const std::vector<char> &vec) {   //?
    auto ExVec = vec;
    auto addVc = (3 - ExVec.size() % 3) % 3; // obliczanie iloma 2 należy dopełnić vector by był podzielny przez 3
    for (int i = 0; i < addVc; i++) {
        ExVec.push_back('2');
    }
    return ExVec;
}

auto PNGencryption(const std::vector<char> &vec, const std::string &filePath) {

    if (vec.size() > PNG_msg_space(filePath)) {
        fmt::println("Wiadomosć jest za długa, nie zmieści się w pliku");
        return 1;
    } else {

        auto input = uzupelnienie(vec);
        auto width = int();
        auto height = int();

        sf::Image image;
        image.loadFromFile(filePath);
        sf::Color pixelColor = image.getPixel(width, height);
        auto imageSize = image.getSize();


        auto pixelCount = 0;
        std::vector<char> pixels;
        for (int j = 0; j < imageSize.y && pixelCount < vec.size(); j++) {    //pobranie kolorów do wektora pixels
            for (int i = 0; i < imageSize.x && pixelCount < vec.size(); i++) {
                sf::Color color = image.getPixel(i, j);
                pixels.push_back(color.r);
                pixels.push_back(color.g);
                pixels.push_back(color.b);
                pixelCount++;
            }
        }
        pixelCount = 0;

        auto tmpPixel = char();
        std::vector<unsigned char> newPixels;

        for (int i = 0; i <
            vec.size(); i++) {                    //zamiana kolorów na takie z zapisaną wiadomością do wektora newPixels
            bool lsb = pixels[i] & 1;
            tmpPixel = PNGbitSwitch(pixels[i], lsb, vec[i]);
            newPixels.push_back(tmpPixel);
        }

        auto pixelOutput = std::vector<sf::Color>();      //zcalenie kolorów RGB do zmiennej typu sf::Colors
        for (int i = 0; i < newPixels.size(); i += 3) {
            auto red = newPixels[i];
            auto green = newPixels[i + 1];
            auto blue = newPixels[i + 2];
            sf::Color newColor(red, green, blue);
            pixelOutput.push_back(newColor);

        }
        for (auto i = 0; i < pixelOutput.size(); i++) {   //zapisanie nowych kolorów do obrazu
            auto x = i % imageSize.x;       //obliczanie współrzędnych do ponownego zapisu
            auto y = i / imageSize.x;

            if (y >= imageSize.y) {
                break;
            }
            image.setPixel(x, y, pixelOutput[i]);
        }


        if (!image.saveToFile(filePath)) {
            fmt::print("Błąd zapisu do pliku\n");
            return 1;
        };

    }
}


auto PNGDecryption(const std::string &filePath) {
    auto width = int();
    auto height = int();

    sf::Image image;
    image.loadFromFile(filePath);
    sf::Color pixelColor = image.getPixel(width, height);
    auto imageSize = image.getSize();

    auto stop = false;
    auto lastBits = std::vector<int>();
    auto stopSign = std::vector<int>{0, 1, 1, 0, 0, 0, 0, 0};
    auto startSign = std::vector<int>{0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0};

    for (int j = 0; j < imageSize.y && !stop; j++) {
        for (int i = 0; i < imageSize.x && !stop; i++) {
            sf::Color color = image.getPixel(i, j);
            lastBits.push_back((int) color.r & 1);              // pobieranie ostatich bitów kolorów
            lastBits.push_back((int) color.g & 1);
            lastBits.push_back((int) color.b & 1);



            if(lastBits.size()==18){
                auto it_start = std::search(lastBits.begin(), lastBits.end(),startSign.begin(),startSign.end());
                if(it_start == lastBits.end()){
                    fmt::print("Obraz nie zawiera ukrytej wiadomości");
                    return 1;
                }
            }


            if (lastBits.size() >= stopSign.size()) {

                auto it = std::search(lastBits.begin(), lastBits.end(), stopSign.begin(), stopSign.end());
                if (it != lastBits.end()) {
                    lastBits.erase(it, lastBits.end());
                    lastBits.erase(lastBits.begin(),lastBits.begin()+16);
                    stop = true;
                }
            }

        }


    }
    //przekształcenie wektora int na ciąg std::string()
       auto txt = std::string();

       for (auto x: lastBits) {
           txt += std::to_string(x);
       } try {
        fmt::print("{}", binaryToString(txt));
    }catch (std::exception const& ex){
        fmt::println("BŁĄD!: Program nie obsługuje polskich znaków");
    }


}

auto getRes(const std::string &filePath) {
    sf::Image image;
    image.loadFromFile(filePath);
    auto vec = std::vector<int>();
    auto imRes = image.getSize();
    auto width = imRes.x;
    auto height = imRes.y;


    fmt::println("Image size {} - {} px ", width, height);


}


