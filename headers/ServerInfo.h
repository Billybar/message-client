#pragma once
#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>

class ServerInfo {
private:
    std::string serverAddress;
    int serverPort;

public:
    // Constructor loads server info from file
    ServerInfo(const std::string& filePath) {
        readFromFile(filePath);
    }

    void readFromFile(const std::string& filePath) {
        std::ifstream serverInfoFile(filePath);
        if (!serverInfoFile.is_open()) {
            throw std::runtime_error("Could not open server.info file");
        }

        std::string serverLine;
        if (!std::getline(serverInfoFile, serverLine)) {
            throw std::runtime_error("Failed to read server info");
        }

        // Find the colon separator
        size_t colonPos = serverLine.find(':');
        if (colonPos == std::string::npos) {
            throw std::runtime_error("Invalid server.info format");
        }

        // Extract IP and port
        serverAddress = serverLine.substr(0, colonPos);
        try {
            serverPort = std::stoi(serverLine.substr(colonPos + 1));
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Invalid port number");
        }
    }

    // Getters
    const std::string& getAddress() const { return serverAddress; }
    int getPort() const { return serverPort; }

    void print() const {
        std::cout << "Server Address: " << serverAddress << std::endl;
        std::cout << "Server Port: " << serverPort << std::endl;
    }
};