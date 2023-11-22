#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "172.16.40.1" 
#define SERVER_PORT 13

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        std::cerr << "Не удалось создать сокет." << std::endl;
        return 1;
    }
    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP); 
    serverAddress.sin_port = htons(SERVER_PORT); 
    if (sendto(s, nullptr, 0, 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) 	{
        std::cerr << "Не удалось отправить запрос." << std::endl;
        close(s);
        return 1;
    }
    char buffer[BUFFER_SIZE];
    int bytesRead = recvfrom(s, buffer, sizeof(buffer) - 1, 0, nullptr, nullptr);
    if (bytesRead == -1) {
        std::cerr << "Не удалось прочитать ответ." << std::endl;
        close(s);
        return 1;
    }
    buffer[bytesRead] = '\0';
    std::cout << "Текущее время: " << buffer << std::endl;
    close(s);
    return 0;
}
