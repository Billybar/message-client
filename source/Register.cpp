#include "../headers/Register.h"
#include <array>
#include <vector>
#include <stdexcept>

void Register::registerUser(const std::string& address, int port, const std::string& username) {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket(io_context);

    // Connect to server
    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::address::from_string(address), port);
    socket.connect(endpoint);

    sendRegistrationRequest(socket, username);
    handleRegistrationResponse(socket);
}

void Register::sendRegistrationRequest(boost::asio::ip::tcp::socket& socket, const std::string& username) {
    // Prepare header
    RequestHeader header{};
    // header.clientId = 0; ClientID not exsit yet
    header.version = VERSION;
    header.code = REGISTER_CODE;
    header.payloadSize = 255 + 160; // Username(255) + PublicKey(160)

    // Prepare payload - username padded to 255 bytes
    std::vector<uint8_t> payload(415, 0); // 255 + 160 bytes
    std::copy(username.begin(), username.end(), payload.begin());
    // TO DO: add public key to payload

    // Send header + payload
    std::array<boost::asio::const_buffer, 2> buffers = {
        boost::asio::buffer(&header, sizeof(header)),
        boost::asio::buffer(payload)
    };
    boost::asio::write(socket, buffers);

    // Send header
    //boost::asio::write(socket, boost::asio::buffer(&header, sizeof(header)));
    // Send payload
    //boost::asio::write(socket, boost::asio::buffer(payload));
}

void Register::handleRegistrationResponse(boost::asio::ip::tcp::socket& socket) {
    // Read response header (7 bytes)
    std::array<uint8_t, 7> responseHeader;
    boost::asio::read(socket, boost::asio::buffer(responseHeader));

    uint16_t responseCode = *reinterpret_cast<uint16_t*>(&responseHeader[1]);
    uint32_t payloadSize = *reinterpret_cast<uint32_t*>(&responseHeader[3]);

    if (responseCode == 9000) {
        throw std::runtime_error("server responded with an error");
    }

    if (responseCode == 2100 && payloadSize == 16) {
        // Read client ID
        std::array<uint8_t, 16> clientId;
        boost::asio::read(socket, boost::asio::buffer(clientId));

        // TODO: Save client ID to me.info file
    }
}