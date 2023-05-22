#include <Windows.h>
#include <commdlg.h>
#include <iostream>
#include <opencv2/opencv.hpp>

// Blur i�lemi yapan i�lev
void applyBlur(const std::wstring& filePath)
{
    // Resmi y�kle
    cv::Mat image = cv::imread(cv::String(filePath.begin(), filePath.end()), cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cout << "Resim y�klenemedi." << std::endl;
        return;
    }

    // Blur i�lemi uygula
    cv::Mat blurredImage;
    cv::blur(image, blurredImage, cv::Size(15, 15)); // Blur filtresi boyutunu belirle

    // Orijinal ve blur uygulanm�� foto�raflar� g�ster
    cv::imshow("Orijinal Foto�raf", image);
    cv::imshow("Blur Uygulanm�� Foto�raf", blurredImage);
    cv::waitKey(0);

    // Blur i�lemi uygulanan resmi kaydet
    std::wstring outputFilePath = filePath.substr(0, filePath.find_last_of(L".")) + L"_blur.jpg";
    cv::imwrite(cv::String(outputFilePath.begin(), outputFilePath.end()), blurredImage);

    std::wcout << L"Blur islemi tamamland�. Sonuc: " << outputFilePath << std::endl;
}

// Foto�raf boyutunu de�i�tiren i�lev
void applyResize(const std::wstring& filePath, int width, int height)
{
    // Resmi y�kle
    cv::Mat image = cv::imread(cv::String(filePath.begin(), filePath.end()), cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cout << "Resim y�klenemedi." << std::endl;
        return;
    }

    // Boyutu de�i�tir
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(width, height)); // Yeni boyutu belirle

    // Orijinal ve boyutu de�i�tirilmi� foto�raflar� g�ster
    cv::imshow("Orijinal Foto�raf", image);
    cv::imshow("Boyutu De�i�tirilmi� Foto�raf", resizedImage);
    cv::waitKey(0);

    // Boyutu de�i�tirilmi� resmi kaydet
    std::wstring outputFilePath = filePath.substr(0, filePath.find_last_of(L".")) + L"_imresize.jpg";
    cv::imwrite(cv::String(outputFilePath.begin(), outputFilePath.end()), resizedImage);

    std::wcout << L"Boyutu degi�tirme islemi tamamland�. Sonuc: " << outputFilePath << std::endl;
}

// Kenar alg�lama i�lemi yapan fonksiyon
void applyEdgeDetection(const std::wstring& filePath)
{
    // Resmi y�kle
    cv::Mat image = cv::imread(cv::String(filePath.begin(), filePath.end()), cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cout << "Resim y�klenemedi." << std::endl;
        return;
    }

    // Kenar alg�lama i�lemi uygula
    cv::Mat edges;
    cv::Canny(image, edges, 50, 150, 3);

    // Kenarlar� g�ster
    cv::imshow("Orijinal Foto�raf", image);
    cv::imshow("Kenarlar", edges);
    cv::waitKey(0);

    // Kenarl� resmi kaydet
    std::wstring outputFilePath = filePath.substr(0, filePath.find_last_of(L".")) + L"_kenaralg.jpg";
    cv::imwrite(cv::String(outputFilePath.begin(), outputFilePath.end()), edges);

    std::wcout << L"Kenar alg�lama islemi tamamland�. Sonuc: " << outputFilePath << std::endl;
}


// Keskinle�tirme i�lemi yapan fonksiyon
void applySharpening(const std::wstring& filePath)
{
    // Resmi y�kle
    cv::Mat image = cv::imread(cv::String(filePath.begin(), filePath.end()), cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cout << "Resim yuklenemedi." << std::endl;
        return;
    }

    // Keskinle�tirme filtresini tan�mla
    cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0);

    // Keskinle�tirme i�lemini uygula
    cv::Mat sharpened;
    cv::filter2D(image, sharpened, -1, kernel);

    // Orijinal ve keskinle�tirilmi� foto�raflar� g�ster
    cv::imshow("Orijinal Foto�raf", image);
    cv::imshow("Keskinle�tirilmi� Foto�raf", sharpened);
    cv::waitKey(0);

    // Keskinle�tirilmi� resmi kaydet
    std::wstring outputFilePath = filePath.substr(0, filePath.find_last_of(L".")) + L"_keskin.jpg";
    cv::imwrite(cv::String(outputFilePath.begin(), outputFilePath.end()), sharpened);

    std::wcout << L"Keskinlestirme islemi tamamland�. Sonuc: " << outputFilePath << std::endl;
}

// Gri tonlama i�lemi yapan fonksiyon
void applyGrayscale(const std::wstring& filePath)
{
    // Resmi y�kle
    cv::Mat image = cv::imread(cv::String(filePath.begin(), filePath.end()), cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cout << "Resim y�klenemedi." << std::endl;
        return;
    }


    // Gri tonlama i�lemini uygula
    cv::Mat grayscaleImage;
    cv::cvtColor(image, grayscaleImage, cv::COLOR_BGR2GRAY);

    // Orijinal ve gri tonlamal� foto�raflar� g�ster
    cv::imshow("Orijinal Foto�raf", image);
    cv::imshow("Gri Tonlamal� Foto�raf", grayscaleImage);
    cv::waitKey(0);

    // Gri tonlamal� resmi kaydet
    std::wstring outputFilePath = filePath.substr(0, filePath.find_last_of(L".")) + L"_grayscale.jpg";
    cv::imwrite(cv::String(outputFilePath.begin(), outputFilePath.end()), grayscaleImage);

    std::wcout << L"Gri tonlama islemi tamamlandi. Sonuc: " << outputFilePath << std::endl;
}


int main()
{
    // Dosya se�me ileti�im kutusu yap�s�
    OPENFILENAME ofn;
    wchar_t szFile[260]; // Se�ilen dosyan�n yolu i�in geni� karakter dizisi

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Resim Dosyalar�\0*.bmp;.jpg;.gif;.png\0T�m Dosyalar\0.*\0";
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
            // Dosya se�me ileti�im kutusunu g�ster
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // Kullan�c�n�n se�ti�i dosyan�n yolunu al
                wchar_t* filePath = ofn.lpstrFile;

                // Blur i�lemi uygula
                applyBlur(filePath);
            }
            else
            {
                // Dosya se�ilmedi veya bir hata olu�tu
                std::cout << "Dosya secilmedi veya hata olustu." << std::endl;
            }
            std::cout << "Blur islemi secildi." << std::endl;
            break;

        case 2:
            // Dosya se�me ileti�im kutusunu g�ster
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // Kullan�c�n�n se�ti�i dosyan�n yolunu al
                wchar_t* filePath = ofn.lpstrFile;

                int width, height;
                std::cout << "Yeni genislik degerini girin: ";
                std::cin >> width;
                std::cout << "Yeni yukseklik degerini girin: ";
                std::cin >> height;

                // Boyutu de�i�tirme i�lemini uygula
                applyResize(filePath, width, height);
            }
            else
            {
                // Dosya se�ilmedi veya bir hata olu�tu
                std::cout << "Dosya secilmedi veya hata olustu." << std::endl;
            }
            std::cout << "Imresize islemi secildi." << std::endl;
            break;

        case 3:
            // Dosya se�me ileti�im kutusunu g�ster
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // Kullan�c�n�n se�ti�i dosyan�n yolunu al
                wchar_t* filePath = ofn.lpstrFile;

                // Kenar alg�lama i�lemini uygula
                applyEdgeDetection(filePath);
            }
            else
            {
                // Dosya se�ilmedi veya bir hata olu�tu
                std::cout << "Dosya secilmedi veya hata olustu." << std::endl;
            }
            std::cout << "Kenar alg�lama secildi." << std::endl;
            break;


        case 4:
            // Dosya se�me ileti�im kutusunu g�ster
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // Kullan�c�n�n se�ti�i dosyan�n yolunu al
                wchar_t* filePath = ofn.lpstrFile;

                // Keskinle�tirme i�lemini uygula
                applySharpening(filePath);
            }
            else
            {
                // Dosya se�ilmedi veya bir hata olu�tu
                std::cout << "Dosya secilmedi veya hata olustu." << std::endl;
            }
            std::cout << "Keskinlestirme secildi." << std::endl;
            break;

        case 5:
            // Dosya se�me ileti�im kutusunu g�ster
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // Kullan�c�n�n se�ti�i dosyan�n yolunu al
                wchar_t* filePath = ofn.lpstrFile;

                // Gri tonlama i�lemini uygula
                applyGrayscale(filePath);
            }
            else
            {
                // Dosya se�ilmedi veya bir hata olu�tu
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