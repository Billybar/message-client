#pragma once
#include <string>
#include <array>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>

class MyInfo {
private:
    std::string username;
    std::array<uint8_t, 16> uuid;
    std::string privateKey;
    bool isRegistered;

public:
    MyInfo(const std::string& filePath) : isRegistered(false) {
        try {
            readFromFile(filePath);
            isRegistered = true;
        }
        catch (const std::runtime_error& e) {
            // File doesn't exist or other error - user not registered
        }
    }

    void readFromFile(const std::string& filePath) {
        std::ifstream infoFile(filePath);
        if (!infoFile) {
            throw std::runtime_error("my.info file not found. Please register first.");
        }

        // Read name
        std::getline(infoFile, username);

        // Read UUID in ASCII hex format
        std::string uuidHex;
        std::getline(infoFile, uuidHex);
        if (uuidHex.length() != 32) {
            throw std::runtime_error("Invalid UUID format in my.info");
        }

        // Convert hex string to bytes
        for (size_t i = 0; i < 16; ++i) {
            std::string byteString = uuidHex.substr(i * 2, 2);
            uuid[i] = std::stoul(byteString, nullptr, 16);
        }

        // Read private key in base64 format
        std::getline(infoFile, privateKey);
    }

    void writeToFile(const std::string& filePath, const std::string& newUsername,
        const std::array<uint8_t, 16>& newUuid,
        const std::string& newPrivateKey) {
        std::ofstream outFile(filePath);
        if (!outFile) {
            throw std::runtime_error("Failed to create my.info file");
        }

        // Write username
        outFile << newUsername << std::endl;

        // Write UUID as hex string
        for (uint8_t byte : newUuid) {
            outFile << std::hex << std::setw(2) << std::setfill('0')
                << static_cast<int>(byte);
        }
        outFile << std::endl;

        // Write private key
        outFile << newPrivateKey << std::endl;

        // Update member variables
        username = newUsername;
        uuid = newUuid;
        privateKey = newPrivateKey;
        isRegistered = true;
    }

    // Seter
    void setIsRegistered(bool status) { isRegistered = status; }

    // Getters
    const std::string& getUsername() const { return username; }
    const std::array<uint8_t, 16>& getUuid() const { return uuid; }
    const std::string& getPrivateKey() const { return privateKey; }
    bool getIsRegistered() const { return isRegistered; }

    void print() const {
        std::cout << "Username: " << username << std::endl;
        std::cout << "UUID: ";
        for (uint8_t b : uuid) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                << static_cast<int>(b);
        }
        std::cout << std::endl;
        std::cout << "Private Key: " << privateKey << std::endl;
    }

    void reload(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file) {
            isRegistered = false;
            return;
        }

        std::string line;

        // Read username
        if (std::getline(file, line)) {
            username = line;
        }

        // Read UUID hex string and convert to bytes
        if (std::getline(file, line)) {
            for (size_t i = 0; i < 32; i += 2) {
                uuid[i / 2] = std::stoi(line.substr(i, 2), nullptr, 16);
            }
        }

        // Read private key
        if (std::getline(file, line)) {
            privateKey = line;
        }

        isRegistered = true;
        file.close();
    }
};