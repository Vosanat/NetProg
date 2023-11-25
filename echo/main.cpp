#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

const int BUFFER_SIZE = 1024;
const int PORT = 7777;

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        std::cerr << "Ошибка при создании сокета\n";
        return 1;
    }
    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int rc = bind(s, reinterpret_cast<struct sockaddr *>(&server_addr), sizeof(server_addr));
    if (rc == -1){
    	std::cerr << "Ошибка при привязке адреса к сокету\n";
        close(s);
        return 1;
    } 
    while (true) {
        struct sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t recv_len = recvfrom(s, buffer, BUFFER_SIZE, 0,
                                    reinterpret_cast<struct sockaddr *>(&client_addr), &client_addr_len);
        if (recv_len == -1) {
            std::cerr << "Ошибка при чтении данных от клиента\n";
            close(s);
            return 1;
        }
        ssize_t send_len = sendto(s, buffer, recv_len, 0,
                                  reinterpret_cast<struct sockaddr *>(&client_addr), client_addr_len);
        if (send_len == -1) {
            std::cerr << "Ошибка при отправке данных клиенту\n";
            close(s);
            return 1;
        }
    }
    close(s);
    return 0;
}
