#include <Windows.h>
#include <commdlg.h>
#include <iostream>
#include <opencv2/opencv.hpp>

// Blur iþlemi yapan iþlev
void applyBlur(const std::wstring& filePath)
{
    // Resmi yükle
    cv::Mat image = cv::imread(cv::String(filePath.begin(), filePath.end()), cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cout << "Resim yüklenemedi." << std::endl;
        return;
    }

    // Blur iþlemi uygula
    cv::Mat blurredImage;
    cv::blur(image, blurredImage, cv::Size(15, 15)); // Blur filtresi boyutunu belirle

    // Orijinal ve blur uygulanmýþ fotoðraflarý göster
    cv::imshow("Orijinal Fotoðraf", image);
    cv::imshow("Blur Uygulanmýþ Fotoðraf", blurredImage);
    cv::waitKey(0);

    // Blur iþlemi uygulanan resmi kaydet
    std::wstring outputFilePath = filePath.substr(0, filePath.find_last_of(L".")) + L"_blur.jpg";
    cv::imwrite(cv::String(outputFilePath.begin(), outputFilePath.end()), blurredImage);

    std::wcout << L"Blur islemi tamamlandý. Sonuc: " << outputFilePath << std::endl;
}

// Fotoðraf boyutunu deðiþtiren iþlev
void applyResize(const std::wstring& filePath, int width, int height)
{
    // Resmi yükle
    cv::Mat image = cv::imread(cv::String(filePath.begin(), filePath.end()), cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cout << "Resim yüklenemedi." << std::endl;
        return;
    }

    // Boyutu deðiþtir
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(width, height)); // Yeni boyutu belirle

    // Orijinal ve boyutu deðiþtirilmiþ fotoðraflarý göster
    cv::imshow("Orijinal Fotoðraf", image);
    cv::imshow("Boyutu Deðiþtirilmiþ Fotoðraf", resizedImage);
    cv::waitKey(0);

    // Boyutu deðiþtirilmiþ resmi kaydet
    std::wstring outputFilePath = filePath.substr(0, filePath.find_last_of(L".")) + L"_imresize.jpg";
    cv::imwrite(cv::String(outputFilePath.begin(), outputFilePath.end()), resizedImage);

    std::wcout << L"Boyutu degiþtirme islemi tamamlandý. Sonuc: " << outputFilePath << std::endl;
}

// Kenar algýlama iþlemi yapan fonksiyon
void applyEdgeDetection(const std::wstring& filePath)
{
    // Resmi yükle
    cv::Mat image = cv::imread(cv::String(filePath.begin(), filePath.end()), cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cout << "Resim yüklenemedi." << std::endl;
        return;
    }

    // Kenar algýlama iþlemi uygula
    cv::Mat edges;
    cv::Canny(image, edges, 50, 150, 3);

    // Kenarlarý göster
    cv::imshow("Orijinal Fotoðraf", image);
    cv::imshow("Kenarlar", edges);
    cv::waitKey(0);

    // Kenarlý resmi kaydet
    std::wstring outputFilePath = filePath.substr(0, filePath.find_last_of(L".")) + L"_kenaralg.jpg";
    cv::imwrite(cv::String(outputFilePath.begin(), outputFilePath.end()), edges);

    std::wcout << L"Kenar algýlama islemi tamamlandý. Sonuc: " << outputFilePath << std::endl;
}


// Keskinleþtirme iþlemi yapan fonksiyon
void applySharpening(const std::wstring& filePath)
{
    // Resmi yükle
    cv::Mat image = cv::imread(cv::String(filePath.begin(), filePath.end()), cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cout << "Resim yuklenemedi." << std::endl;
        return;
    }

    // Keskinleþtirme filtresini tanýmla
    cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0);

    // Keskinleþtirme iþlemini uygula
    cv::Mat sharpened;
    cv::filter2D(image, sharpened, -1, kernel);

    // Orijinal ve keskinleþtirilmiþ fotoðraflarý göster
    cv::imshow("Orijinal Fotoðraf", image);
    cv::imshow("Keskinleþtirilmiþ Fotoðraf", sharpened);
    cv::waitKey(0);

    // Keskinleþtirilmiþ resmi kaydet
    std::wstring outputFilePath = filePath.substr(0, filePath.find_last_of(L".")) + L"_keskin.jpg";
    cv::imwrite(cv::String(outputFilePath.begin(), outputFilePath.end()), sharpened);

    std::wcout << L"Keskinlestirme islemi tamamlandý. Sonuc: " << outputFilePath << std::endl;
}

// Gri tonlama iþlemi yapan fonksiyon
void applyGrayscale(const std::wstring& filePath)
{
    // Resmi yükle
    cv::Mat image = cv::imread(cv::String(filePath.begin(), filePath.end()), cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cout << "Resim yüklenemedi." << std::endl;
        return;
    }


    // Gri tonlama iþlemini uygula
    cv::Mat grayscaleImage;
    cv::cvtColor(image, grayscaleImage, cv::COLOR_BGR2GRAY);

    // Orijinal ve gri tonlamalý fotoðraflarý göster
    cv::imshow("Orijinal Fotoðraf", image);
    cv::imshow("Gri Tonlamalý Fotoðraf", grayscaleImage);
    cv::waitKey(0);

    // Gri tonlamalý resmi kaydet
    std::wstring outputFilePath = filePath.substr(0, filePath.find_last_of(L".")) + L"_grayscale.jpg";
    cv::imwrite(cv::String(outputFilePath.begin(), outputFilePath.end()), grayscaleImage);

    std::wcout << L"Gri tonlama islemi tamamlandi. Sonuc: " << outputFilePath << std::endl;
}


int main()
{
    // Dosya seçme iletiþim kutusu yapýsý
    OPENFILENAME ofn;
    wchar_t szFile[260]; // Seçilen dosyanýn yolu için geniþ karakter dizisi

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Resim Dosyalarý\0*.bmp;.jpg;.gif;.png\0Tüm Dosyalar\0.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    int choice = 0;



    while (choice != 6)
    {
        std::cout << "Yapmak istediginiz islemi secin:\n";
        std::cout << "1 - BLUR\n";
        std::cout << "2 - IMRESIZE\n";
        std::cout << "3 - KENAR ALGILAMA\n";
        std::cout << "4 - KESKINLESTIRME\n";
        std::cout << "5 - GRI TONLAMA\n";
        std::cout << "6 - CIKIS\n";
        std::cout << "Seciminiz: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            // Dosya seçme iletiþim kutusunu göster
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // Kullanýcýnýn seçtiði dosyanýn yolunu al
                wchar_t* filePath = ofn.lpstrFile;

                // Blur iþlemi uygula
                applyBlur(filePath);
            }
            else
            {
                // Dosya seçilmedi veya bir hata oluþtu
                std::cout << "Dosya secilmedi veya hata olustu." << std::endl;
            }
            std::cout << "Blur islemi secildi." << std::endl;
            break;

        case 2:
            // Dosya seçme iletiþim kutusunu göster
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // Kullanýcýnýn seçtiði dosyanýn yolunu al
                wchar_t* filePath = ofn.lpstrFile;

                int width, height;
                std::cout << "Yeni genislik degerini girin: ";
                std::cin >> width;
                std::cout << "Yeni yukseklik degerini girin: ";
                std::cin >> height;

                // Boyutu deðiþtirme iþlemini uygula
                applyResize(filePath, width, height);
            }
            else
            {
                // Dosya seçilmedi veya bir hata oluþtu
                std::cout << "Dosya secilmedi veya hata olustu." << std::endl;
            }
            std::cout << "Imresize islemi secildi." << std::endl;
            break;

        case 3:
            // Dosya seçme iletiþim kutusunu göster
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // Kullanýcýnýn seçtiði dosyanýn yolunu al
                wchar_t* filePath = ofn.lpstrFile;

                // Kenar algýlama iþlemini uygula
                applyEdgeDetection(filePath);
            }
            else
            {
                // Dosya seçilmedi veya bir hata oluþtu
                std::cout << "Dosya secilmedi veya hata olustu." << std::endl;
            }
            std::cout << "Kenar algýlama secildi." << std::endl;
            break;


        case 4:
            // Dosya seçme iletiþim kutusunu göster
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // Kullanýcýnýn seçtiði dosyanýn yolunu al
                wchar_t* filePath = ofn.lpstrFile;

                // Keskinleþtirme iþlemini uygula
                applySharpening(filePath);
            }
            else
            {
                // Dosya seçilmedi veya bir hata oluþtu
                std::cout << "Dosya secilmedi veya hata olustu." << std::endl;
            }
            std::cout << "Keskinlestirme secildi." << std::endl;
            break;

        case 5:
            // Dosya seçme iletiþim kutusunu göster
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // Kullanýcýnýn seçtiði dosyanýn yolunu al
                wchar_t* filePath = ofn.lpstrFile;

                // Gri tonlama iþlemini uygula
                applyGrayscale(filePath);
            }
            else
            {
                // Dosya seçilmedi veya bir hata oluþtu
                std::cout << "Dosya secilmedi veya hata olustu." << std::endl;
            }
            break;

        case 6:
            std::cout << "Programdan cikis yapildi" << std::endl;
            break;

        default:
            std::cout << "Gecersiz secim. Lutfen tekrar deneyin." << std::endl;
            return 0;
        }
    }
    return 0;
}