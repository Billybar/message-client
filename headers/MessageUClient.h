// MessageUClient.h
#pragma once
#include <string>
#include "ServerInfo.h"
#include "MyInfo.h"
#include "Register.h"
#include "RequestClientsList.h"
#include "RequestPublicKey.h"
#include "RequestWaitingMessages.h"

class MessageUClient {
private:
    ServerInfo serverInfo;
    MyInfo myInfo;
    std::vector<Client> m_clients;

public:
    // Constructor that accepts paths to config files
    MessageUClient(const std::string& serverInfoPath = "C:\\Users\\kipi\\source\\repos\\mmn15_client\\x64\\Debug\\server.info",
        const std::string& myInfoPath = "C:\\Users\\kipi\\source\\repos\\mmn15_client\\x64\\Debug\\my.info");

    // Main run loop
    void run();

    // Menu operations
    void registerUser();
    void requestClientsList();
    void requestPublicKey();
    void requestWaitingMessages();
    //void sendTextMessage();
    //void sendSymKeyRequest();
    //void sendSymKey();
};