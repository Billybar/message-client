// MessageUMessage.cpp
#include "../headers/MessageUClient.h"
#include <iostream>
#include <stdexcept>


MessageUClient::MessageUClient(const std::string& serverInfoPath, const std::string& myInfoPath)
    : serverInfo(serverInfoPath)
    , myInfo(myInfoPath) // Init list - prevents double initialization
{
    // Generate private/public key pair if user not registered
    if (!myInfo.getIsRegistered()) {
        RSAPrivateWrapper rsaPrivate;
        std::string privateKey = rsaPrivate.getPrivateKey();

        // Get public key in binary format
        std::vector<uint8_t> publicKeyBin(160);
        rsaPrivate.getPublicKey(reinterpret_cast<char*>(publicKeyBin.data()), 160);

        Base64Wrapper base64;
        std::string encodedPrivateKey = base64.encode(privateKey);

        myInfo.setPrivateKey(encodedPrivateKey);
        myInfo.setPublicKey(publicKeyBin);
    }
}

void MessageUClient::registerUser() {
    try {
        Register reg{ myInfo };
        reg.registerUser(serverInfo.getAddress(), serverInfo.getPort());
    }
    catch (const std::exception& e) {
        std::cout << "Registration failed: " << e.what() << std::endl;
    }
}

void MessageUClient::requestClientsList() {
    try {
        m_clients.clear();
        RequestClientsList rcl(m_clients);
        rcl.getClientsList(serverInfo.getAddress(), serverInfo.getPort(), myInfo.getUuid());
    }
    catch (const std::exception& e) {
        std::cout << "Failed to get clients list: " << e.what() << std::endl;
    }
}

void MessageUClient::requestPublicKey() {
    try {
        RequestPublicKey rpk(m_clients);  // Pass clients vector reference
        rpk.getPublicKey(serverInfo.getAddress(), serverInfo.getPort(), myInfo.getUuid());
    }
    catch (const std::exception& e) {
        std::cout << "Failed to get public key: " << e.what() << std::endl;
    }
}

void MessageUClient::requestWaitingMessages() {
    try {
        RequestWaitingMessages rwm(m_clients);
        rwm.getWaitingMessages(serverInfo.getAddress(), serverInfo.getPort(), myInfo.getUuid());
    }
    catch (const std::exception& e) {
        std::cout << "Failed to get waiting messages: " << e.what() << std::endl;
    }
}

void MessageUClient::sendTextMessage() {
    try {
        SendTextMessage stm(m_clients);
        stm.sendMessage(serverInfo.getAddress(), serverInfo.getPort(), myInfo.getUuid());
    }
    catch (const std::exception& e) {
        std::cout << "Failed to send message: " << e.what() << std::endl;
    }
}

void MessageUClient::sendSymKeyRequest() {
    try {
        SendSymKeyRequest ssr(m_clients);
        ssr.sendRequest(serverInfo.getAddress(), serverInfo.getPort(), myInfo.getUuid());
    }
    catch (const std::exception& e) {
        std::cout << "Failed to send symmetric key request: " << e.what() << std::endl;
    }
}

void MessageUClient::sendSymKey() {
    try {
        SendSymKey ssk(m_clients);
        ssk.sendKey(serverInfo.getAddress(), serverInfo.getPort(), myInfo.getUuid());
    }
    catch (const std::exception& e) {
        std::cout << "Failed to send symmetric key: " << e.what() << std::endl;
    }
}

void MessageUClient::run() {
    try {
        // Print connection info
        serverInfo.print();

        // Print user info if registered
        if (myInfo.getIsRegistered()) {
            myInfo.print();
        }

        // Main menu loop
        while (true) {
            std::cout << "\nMessageU client at your service.\n";
            std::cout << "110) Register\n";
            std::cout << "120) Request for clients list\n";
            std::cout << "130) Request for public key\n";
            std::cout << "140) Request for waiting messages\n";
            std::cout << "150) Send a text message\n";
            std::cout << "151) Send a request for symmetric key\n";
            std::cout << "152) Send your symmetric key\n";
            std::cout << "0) Exit client\n";
            std::cout << "? ";

            int choice;
            std::cin >> choice;

            // Handle menu choices
            switch (choice) {
            case 110:
                if (myInfo.getIsRegistered()) {
                    std::cout << "Already registered\n";
                }
                else {
                    registerUser();
                }
                break;
            case 120:
                if (!myInfo.getIsRegistered()) {
                    std::cout << "Must register first\n";
                }
                else {
                    requestClientsList();
                }
                break;
            case 130:
                if (!myInfo.getIsRegistered()) {
                    std::cout << "Must register first\n";
                }
                else {
                   requestPublicKey();
                }
                break;
            case 140:
                if (!myInfo.getIsRegistered()) {
                    std::cout << "Must register first\n";
                }
                else {
                    requestWaitingMessages();
                }
                break;
            case 150:
                if (!myInfo.getIsRegistered()) {
                    std::cout << "Must register first\n";
                }
                else {
                    sendTextMessage();
                }
                break;
            case 151:
                if (!myInfo.getIsRegistered()) {
                    std::cout << "Must register first\n";
                }
                else {
                    sendSymKeyRequest();
                }
                break;
            case 152:
                if (!myInfo.getIsRegistered()) {
                    std::cout << "Must register first\n";
                }
                else {
                    sendSymKey();
                }
                break;
            case 0:
                std::cout << "Goodbye!\n";
                return;
            default:
                std::cout << "Invalid choice\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        MessageUClient client;
        client.run();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}