#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <filesystem>
#include <fstream> 

namespace fs = std::filesystem;
using namespace std;
using namespace cv;

struct ImageDimensions {
    int width;
    int height;
};

ImageDimensions saveImageFilenames(const string& imagePath, const string& outputFile) {
    ImageDimensions dimensions = { 0, 0 };

    // Перевіряємо, чи є файл звичайним файлом
    if (!fs::exists(imagePath) || !fs::is_regular_file(imagePath)) {
        cerr << "Помилка: Файл не існує або це не файл." << std::endl;
        return dimensions;
    }

    // Завантажуємо зображення за допомогою OpenCV
    Mat image = imread(imagePath);
    if (image.empty()) {
        cerr << "Помилка: Неможливо відкрити зображення " << imagePath << std::endl;
        return dimensions;
    }

    dimensions.width = image.cols;
    dimensions.height = image.rows;
    // Виводимо розміри на екран

    std::cout << "Зображення: " << imagePath << ", Ширина: " << dimensions.width << ", Висота: " << dimensions.height << std::endl;

    // Відкриваємо файл для дозапису (append) і записуємо інформацію
    std::ofstream outFile(outputFile, std::ios_base::app);
    if (!outFile) {
        std::cerr << "Помилка: Неможливо відкрити файл для запису." << std::endl;
        return dimensions;
    }

    // Записуємо інформацію про зображення в .txt файл
    outFile << "Зображення: " << imagePath << ", Ширина: " << dimensions.width << ", Висота: " << dimensions.height << std::endl;

   // return dimensions;(outputFile, std::ios_base::app);
    if (!outFile) {
        std::cerr << "Помилка: Неможливо відкрити файл для запису." << std::endl;
        return dimensions;
    }

    // Записуємо інформацію про зображення в .txt файл
    outFile << "Зображення: " << imagePath << ", Ширина: " << dimensions.width << ", Висота: " << dimensions.height << std::endl;

    return dimensions;
}

int main(int argc, char* argv[])
{
 //   if (argc != 3) {
 //       std::cerr << "Need to enter 3 args. 1.Name program; 2. DirectoryPath; 3. OutputFile" << std::endl;
 //       return 1;
 //   }

  // argv[1] = "C:\\MULTIMEDIA\\StudyPROGRAMMING\\T_OpenCVProj\\IMG_DIR";

    string directoryPath = "C:\\MULTIMEDIA\\StudyPROGRAMMING\\T_OpenCVProj\\IMG_DIR"; //argv[1];   
    string outputFile = "C:\\MULTIMEDIA\\StudyPROGRAMMING\\T_OpenCVProj\\IMG_DIR\\111txt.txt";//argv[2];      

    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
        cerr << "Your arg:directoryPath: " << directoryPath << ". Directory does not exist or is not a directory." << endl;
        return false;
    }



    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::string fileExtension = entry.path().extension().string();
            if (fileExtension == ".jpg" || fileExtension == ".png" || fileExtension == ".jpeg") {
                // Отримуємо інформацію про зображення
                ImageDimensions dims = saveImageFilenames(entry.path().string(), outputFile);
                // Тут можна додатково обробляти структуру `dims`, наприклад записати в файл або вивести на екран
            }
        }
    }

    cout << "-----------" << endl << "End program. Thanks!" << endl;

    this_thread::sleep_for(chrono::milliseconds(10000));

    return 0;
}
