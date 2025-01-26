// Client.h
#pragma once
#include <string>
#include <array>
#include <vector>

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
};