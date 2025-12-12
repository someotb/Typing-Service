#include <cstdio>
#include <iostream>
#include <cstring>
#include <optional>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <nlohmann/json.hpp>
#include <optional>

using namespace std;
using namespace nlohmann;

optional<string> jsonify(const string& body) {
    try {
        json json_response = json::parse(body);
        return json_response["text"].get<string>();
    } catch (json::exception& err) {
        cout << "Error parsing JSON: " << err.what() << endl;
        return std::nullopt;
    }
}

int main() {
    const char* server_ip = "127.0.0.1";
    int port = 5000;

    int sock = socket(AF_INET, SOCK_STREAM, 0); //AF_INET - IPv4, SOCK_STREAM - TCP, 0 - использовать TCP (FD)
    if (sock == -1) {
        perror("Socket creation failed!");
        return -1;
    }

    struct sockaddr_in serv_addr; // sockaddr_in - структура описывающая IPv4
    memset(&serv_addr, 0, sizeof(serv_addr)); // memset - заполняет струтуру нулями

    serv_addr.sin_family = AF_INET; // IPv4
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sock, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection to host failed");
        return -1;
    }

    string request = "GET /typing HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n";
    send(sock, request.c_str(), request.length(), 0);

    char buffer[4096];
    string response;
    ssize_t bytes_read;
    while ((bytes_read = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        response += buffer;
    }

    close(sock);

    size_t body_start = response.find("\r\n\r\n");
    string body;
    if (body_start != string::npos) {
        body = response.substr(body_start + 4); // +4 потому что find возвращает начало найденой части("\r\n\r\n")
    } else {
        cout << "Could not find response body!" << endl;
        return 1;
    }

    auto response_json_body = jsonify(body);
    if (response_json_body.has_value()) {
        cout << response_json_body.value() << endl;
    } else {
        cout << "Error: Empty response" << endl;
    }

    return 0;
}
