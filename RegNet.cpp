#include <iostream>  
#include <vector>  

class InputLayer {  
public:  
    InputLayer(int height, int width, int channels)  
        : height(height), width(width), channels(channels) {}  

    void setInput(const std::vector<std::vector<std::vector<float>>>& img) {  
        // Here, you would normally resize and normalize your image data  
        inputData = img;  
    }  

    void printInputShape() const {  
        std::cout << "Input shape: " << height << " x " << width << " x " << channels << std::endl;  
    }  

private:  
    int height;  
    int width;  
    int channels;  
    std::vector<std::vector<std::vector<float>>> inputData; // for storing image data  
};  

int main() {  
    // Create an input layer for 224x224 RGB images  
    InputLayer inputLayer(224, 224, 3);  
    
    // Normally, you would populate inputData with image data here  

    inputLayer.printInputShape(); // Output the input shape  

    return 0;  
}