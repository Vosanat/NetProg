#include <iostream>
#include <cstring>
#include <memory>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

const int BUFFER_SIZE = 1024;
const int PORT = 7777;

int main()
{
    try {
        int s = socket(AF_INET, SOCK_STREAM, 0);
        if (s == -1) {
            throw std::system_error(errno, std::generic_category());
        }
        std::unique_ptr<sockaddr_in> self_addr(new sockaddr_in);
        self_addr->sin_family = AF_INET;
        self_addr->sin_port = htons(PORT);
        self_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
        int rc = bind(s, reinterpret_cast<const sockaddr*>(self_addr.get()), sizeof(sockaddr_in));
        if (rc == -1) {
            throw std::system_error(errno, std::generic_category(),"сокет не создан");
        }
        while (true) {
            rc = listen(s, SOMAXCONN);
            if (rc == -1) {
                throw std::system_error(errno, std::generic_category()," сервер не встал на прослушку");
            }
            sockaddr_in client_addr;
            socklen_t len = sizeof(sockaddr_in);

            int work_sock = accept(s, reinterpret_cast<sockaddr*>(&client_addr), &len);
            if (work_sock == -1) {
                throw std::system_error(errno, std::generic_category(), "не приняты данные");
            }
            char buffer[BUFFER_SIZE];
            int recv_len = recv(work_sock, buffer, BUFFER_SIZE, 0);
            if (recv_len == -1) {
                throw std::system_error(errno, std::generic_category(),"не записаны данные от клиента");
            }
            int send_len = send(work_sock, buffer, recv_len, 0);
            if (send_len == -1) {
                throw std::system_error(errno, std::generic_category(), "не отправлены данные клиенту");
            }
            close(work_sock);
        }
        close(s);
    } catch (const std::system_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
