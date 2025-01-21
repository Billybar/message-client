// main.cpp

#include ".\Message.h"
#include <iostream>
#include <string>

int main() {
    try {
        MessageUClient client;
        client.mainMenu(); // Call the mainMenu method that handles the menu loop
        return 0;

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
            std::cout << "?\n";

            int choice;
            std::cin >> choice;
            std::cin.ignore(); // Clear newline from input buffer

            switch (choice) {
            case 110: { // Register
                if (client.isRegistered()) {
                    std::cout << "Already registered\n";
                    break;
                }
                std::string username;
                std::cout << "Enter username: ";
                std::getline(std::cin, username);

                if (!client.registerClient(username)) {
                    std::cout << "Server responded with an error\n";
                }
                break;
            }
            case 120: { // Request clients list
                if (!client.isRegistered()) {
                    std::cout << "Must register first\n";
                    break;
                }
                if (!client.requestClientsList()) {
                    std::cout << "Server responded with an error\n";
                }
                break;
            }
            case 130: { // Request public key
                if (!client.isRegistered()) {
                    std::cout << "Must register first\n";
                    break;
                }
                std::string username;
                std::cout << "Enter username: ";
                std::getline(std::cin, username);

                if (!client.requestPublicKey(username)) {
                    std::cout << "Server responded with an error\n";
                }
                break;
            }
            case 140: { // Get waiting messages
                if (!client.isRegistered()) {
                    std::cout << "Must register first\n";
                    break;
                }
                if (!client.getWaitingMessages()) {
                    std::cout << "Server responded with an error\n";
                }
                break;
            }
            case 150: { // Send text message
                if (!client.isRegistered()) {
                    std::cout << "Must register first\n";
                    break;
                }
                std::string username, message;
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
                std::cout << "Enter message: ";
                std::getline(std::cin, message);

                if (!client.sendTextMessage(username, message)) {
                    std::cout << "Server responded with an error\n";
                }
                break;
            }
            case 151: { // Request symmetric key
                if (!client.isRegistered()) {
                    std::cout << "Must register first\n";
                    break;
                }
                std::string username;
                std::cout << "Enter username: ";
                std::getline(std::cin, username);

                if (!client.requestSymmetricKey(username)) {
                    std::cout << "Server responded with an error\n";
                }
                break;
            }
            case 152: { // Send symmetric key
                if (!client.isRegistered()) {
                    std::cout << "Must register first\n";
                    break;
                }
                std::string username;
                std::cout << "Enter username: ";
                std::getline(std::cin, username);

                if (!client.sendSymmetricKey(username)) {
                    std::cout << "Server responded with an error\n";
                }
                break;
            }
            case 0: // Exit
                return 0;
            default:
                std::cout << "Invalid choice\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}