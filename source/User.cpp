#include "..\headers\User.h"

User::User(const std::array<uint8_t, 16>& userId, const std::string& name)
    : uuid(userId), username(name), hasSymmetricKey(false) {
    // Validate username length (should be <= 255 bytes including null terminator)
    if (name.length() >= 255) {
        throw std::invalid_argument("Username too long (max 254 characters)");
    }
}

// Getters
const std::string& User::getUsername() const { return username; }
const std::array<uint8_t, 16>& User::getUUID() const { return uuid;}

// Get & Set - Public key
void User::setPublicKey(const std::vector<uint8_t>& key) {
    if (key.size() != 160) {
        throw std::invalid_argument("Public key must be exactly 160 bytes");
    }
    publicKey = key;
}

const std::vector<uint8_t>& User::getPublicKey() const {
    if (publicKey.empty()) {
        throw std::runtime_error("Public key not set");
    }
    return publicKey;
}

// Get & Set - Symetric key
void User::setSymmetricKey(const std::vector<uint8_t>& key) {
    symmetricKey = key;
    hasSymmetricKey = true;
}

const std::vector<uint8_t>& User::getSymmetricKey() const {
    if (!hasSymmetricKey) {
        throw std::runtime_error("Symmetric key not set");
    }
    return symmetricKey;
}

bool User::hasValidSymmetricKey() const {
    return hasSymmetricKey;
}

bool User::operator==(const User& other) const {
    return uuid == other.uuid;
}

bool User::operator!=(const User& other) const {
    return !(*this == other);
}