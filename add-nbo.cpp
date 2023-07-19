#include <iostream>
#include <cstdint>
#include <fstream>

uint32_t read_uint32(const char* filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    std::streamsize size = file.tellg();
    if (size != 4) {
        std::cerr << "Invalid file size: " << size << " bytes. Expected 4 bytes." << std::endl;
        exit(1);
    }

    file.seekg(0, std::ios::beg);
    uint32_t num;
    file.read(reinterpret_cast<char*>(&num), sizeof(uint32_t));
    file.close();

    return num;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: add-nbo <file1> <file2>" << std::endl;
        return 1;
    }

    uint32_t num1 = read_uint32(argv[1]);
    uint32_t num2 = read_uint32(argv[2]);

    uint32_t sum = num1 + num2;

    std::cout << num1 << "(0x" << std::hex << num1 << ") + "
              << num2 << "(0x" << std::hex << num2 << ") = "
              << sum << "(0x" << std::hex << sum << ")" << std::endl;

    return 0;
}
