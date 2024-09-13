#include <iostream>  
#include <curl/curl.h>  
#include <fstream>  

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {  
    std::ofstream* ofs = static_cast<std::ofstream*>(userp);  
    size_t totalSize = size * nmemb;  
    ofs->write(static_cast<const char*>(contents), totalSize);  
    return totalSize;  
}  

int main() {  
    CURL* curl;  
    CURLcode res;  
    const char* url = "https://archive.ics.uci.edu/dataset/990/printed+circuit+board+processed+image";  
    const char* outputFilePath = "dataset.zip"; // Change to desired output file path  

    curl = curl_easy_init();  
    if(curl) {  
        std::ofstream ofs(outputFilePath, std::ios::binary);  
        if (!ofs) {  
            std::cerr << "Error opening file for writing: " << outputFilePath << std::endl;  
            return 1;  
        }  

        // Set curl options  
        curl_easy_setopt(curl, CURLOPT_URL, url);  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ofs);  
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  

        // Perform the request  
        res = curl_easy_perform(curl);  
        if(res != CURLE_OK) {  
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;  
        }  

        // Clean up  
        ofs.close();  
        curl_easy_cleanup(curl);  
    } else {  
        std::cerr << "Failed to initialize curl." << std::endl;  
        return 1;  
    }  

    std::cout << "Download complete." << std::endl;  
    return 0;  
}