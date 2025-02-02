// Client.h
#pragma once
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <iomanip>      // FOR TESTING - using  std::setw
#include <algorithm>    // FOR TESTING - using std::max

class Client {
private:
    std::array<uint8_t, 16> m_id;
    std::string m_username;
    std::vector<uint8_t> m_publicKey;
    std::vector<uint8_t> m_symmetricKey;

public:
    Client(const std::array<uint8_t, 16>& clientId, const std::string& name)
        : m_id(clientId), m_username(name) {}

    // Getters
    const std::array<uint8_t, 16>& getId() const { return m_id; }
    const std::string& getUsername() const { return m_username; }
    const std::vector<uint8_t>& getPublicKey() const { return m_publicKey; }
    const std::vector<uint8_t>& getSymmetricKey() const { return m_symmetricKey; }

    // Setters
    void setPublicKey(const std::vector<uint8_t>& key) { m_publicKey = key; }
    void setSymmetricKey(const std::vector<uint8_t>& key) { m_symmetricKey = key; }

    // Check if client has keys
    bool hasPublicKey() const { return !m_publicKey.empty(); }
    bool hasSymmetricKey() const { return !m_symmetricKey.empty(); }


    // ptint
    void print() const {
        // Print username
        std::cout << std::endl << "Username: " << m_username << std::endl;

        // Print ID in hexadecimal format
        std::cout << "ID: ";
        for (const auto& byte : m_id) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                << static_cast<int>(byte);
        }
        std::cout << std::dec << std::endl;  // Reset to decimal format

        // Print public key status
        if (hasPublicKey()) {
            std::cout << "public key: ...";
            size_t start = m_publicKey.size() >= 5 ? m_publicKey.size() - 5 : 0;
            for (size_t i = start; i < m_publicKey.size(); i++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0')
                    << static_cast<int>(m_publicKey[i]);
            }
            std::cout << std::dec << std::endl;
        }
        else{
            std::cout << "Public Key: " << "Not Present" << std::endl;
        }

        // Print symmetric key status
        if (hasSymmetricKey()) {
            std::cout << "symmetric key: ...";
            for (const auto& byte : m_symmetricKey) {
                std::cout << std::hex << std::setw(2) << std::setfill('0')
                    << static_cast<int>(byte);
            }
            /*size_t start = m_symmetricKey.size() >= 5 ? m_symmetricKey.size() - 5 : 0;
            for (size_t i = start; i < m_symmetricKey.size(); i++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0')
                    << static_cast<int>(m_symmetricKey[i]);
            }*/
            std::cout << std::dec << std::endl;
        }
        else {
            std::cout << "Symmetric Key: " << "Not Present" << std::endl;
        }

        std::cout << "------------------------" << std::endl;
    }
};