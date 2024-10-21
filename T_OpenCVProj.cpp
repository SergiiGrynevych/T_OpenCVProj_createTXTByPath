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

    // ����������, �� � ���� ��������� ������
    if (!fs::exists(imagePath) || !fs::is_regular_file(imagePath)) {
        cerr << "�������: ���� �� ���� ��� �� �� ����." << std::endl;
        return dimensions;
    }

    // ����������� ���������� �� ��������� OpenCV
    Mat image = imread(imagePath);
    if (image.empty()) {
        cerr << "�������: ��������� ������� ���������� " << imagePath << std::endl;
        return dimensions;
    }

    dimensions.width = image.cols;
    dimensions.height = image.rows;
    // �������� ������ �� �����

    std::cout << "����������: " << imagePath << ", ������: " << dimensions.width << ", ������: " << dimensions.height << std::endl;

    // ³�������� ���� ��� �������� (append) � �������� ����������
    std::ofstream outFile(outputFile, std::ios_base::app);
    if (!outFile) {
        std::cerr << "�������: ��������� ������� ���� ��� ������." << std::endl;
        return dimensions;
    }

    // �������� ���������� ��� ���������� � .txt ����
    outFile << "����������: " << imagePath << ", ������: " << dimensions.width << ", ������: " << dimensions.height << std::endl;

   // return dimensions;(outputFile, std::ios_base::app);
    if (!outFile) {
        std::cerr << "�������: ��������� ������� ���� ��� ������." << std::endl;
        return dimensions;
    }

    // �������� ���������� ��� ���������� � .txt ����
    outFile << "����������: " << imagePath << ", ������: " << dimensions.width << ", ������: " << dimensions.height << std::endl;

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
                // �������� ���������� ��� ����������
                ImageDimensions dims = saveImageFilenames(entry.path().string(), outputFile);
                // ��� ����� ��������� ��������� ��������� `dims`, ��������� �������� � ���� ��� ������� �� �����
            }
        }
    }

    cout << "-----------" << endl << "End program. Thanks!" << endl;

    this_thread::sleep_for(chrono::milliseconds(10000));

    return 0;
}
