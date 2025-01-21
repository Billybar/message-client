#pragma once
#include <string>
#include <vector>
#include <array>
#include <stdexcept>

class User {
private:
    std::string username;               // ASCII username, null terminated
    std::array<uint8_t, 16> uuid;      // 128-bit unique identifier
    std::vector<uint8_t> publicKey;     // 160 bytes public key
    std::vector<uint8_t> symmetricKey;  // Optional symmetric key for this user
    bool hasSymmetricKey;              // Flag indicating if symmetric key exists

public:
    // Constructor with UUID and username
    User(const std::array<uint8_t, 16>& userId, const std::string& name);

    // Getters
    const std::string& getUsername() const;
    const std::array<uint8_t, 16>& getUUID() const;

    // Public key management
    void setPublicKey(const std::vector<uint8_t>& key);
    const std::vector<uint8_t>& getPublicKey() const;

    // Symmetric key management
    void setSymmetricKey(const std::vector<uint8_t>& key);
    const std::vector<uint8_t>& getSymmetricKey() const;
    bool hasValidSymmetricKey() const;

    // Equality operators based on UUID
    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
};