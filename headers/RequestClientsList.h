// RequestClientsList.h
#pragma once
#include <string>
#include <boost/asio.hpp>
#include <vector>
#include <utility>

class RequestClientsList {
public:
    void getClientsList(const std::string& address, int port, const std::array<uint8_t, 16>& myId);

private:
    static constexpr uint8_t VERSION = 1;
    static constexpr uint16_t LIST_CODE = 601;

    struct RequestHeader {
        uint8_t clientId[16];
        uint8_t version;
        uint16_t code;
        uint32_t payloadSize;
    };

    void sendListRequest(boost::asio::ip::tcp::socket& socket, const std::array<uint8_t, 16>& myId);
    void handleListResponse(boost::asio::ip::tcp::socket& socket);
};