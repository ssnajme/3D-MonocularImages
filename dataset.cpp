#include <stdio.h>
#include <stdlib.h>

int main() {
    // Download the dataset using curl
    system("curl -O http://diode-dataset.s3.amazonaws.com/val.tar.gz");

    // Extract the dataset using tar
    system("tar -xzf val.tar.gz");

    printf("Dataset downloaded and extracted successfully!\n");

    return 0;
}
