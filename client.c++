#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

int main(){

    int client_socket;
    if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("FD creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(6666);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    std::cout << "Connecting..." << std::endl;
    if((connect(client_socket, (const struct sockaddr*)&server_address, sizeof(server_address))) < 0){
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    const char* msg = "Wsg!";
    ssize_t total_msg_sent = 0;
    while(strlen(msg)>total_msg_sent) {
        ssize_t msg_sent = send(client_socket, msg+total_msg_sent, strlen(msg)-total_msg_sent, 0);
        std::cout << "Message sent" << std::endl;
        if(msg_sent == -1) { perror("Send failed"); break; }
        total_msg_sent = total_msg_sent + msg_sent;
    }
    
    close(client_socket);
}   