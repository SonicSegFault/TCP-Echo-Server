#include<iostream>
#include <unistd.h>
#include<sys/socket.h>
#include <netinet/in.h> //for sockaddr

// This is what sockaddr looks like 
// struct sockaddr_in {
//     sa_family_t sin_family;   
//     in_port_t sin_port;       
//     struct in_addr sin_addr;  
// };

constexpr int PORT = 6666;

int main(){

    //create socket File descriptor
    int server_socket;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){ //TCP = sock_stream
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    //change socket settings to blind to address & port multiple times
    int opt = 1;
    if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1){
        perror("Failed to change socket settings");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET; //IPv4
    server_address.sin_port = htons(PORT); //port -> network bytes
    server_address.sin_addr.s_addr = INADDR_ANY; //Accept connections on any IP.
    socklen_t client_addrlen = sizeof(client_address);

    //bind() tells kernel: "This socket owns this IP address and port."

    //type cast server_address to struct ptr sockaddr
    if(bind(server_socket, (const struct sockaddr*)&server_address, sizeof(server_address))<0){
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if((listen(server_socket, 5))<0){
        perror("server can't listen");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i<5; i++){
        int new_socket;
        if((new_socket = accept(server_socket, (struct  sockaddr*)&client_address, &client_addrlen)) < 0){
            perror("Accepting failure");
            break;
        }

        char buffer[1024] = {};
        while(true){
            ssize_t packet_recv = recv(new_socket, buffer, sizeof(buffer), 0);
            if(packet_recv > 0){ 
                ssize_t packet_sent, i=0;
                while(i<packet_recv){
                    std::cout << buffer << std::endl;
                    packet_sent = send(new_socket, buffer+i, packet_recv-i, 0);
                    if(packet_sent == -1){ perror("Echo error"); break; }
                    i = i + packet_sent;
                }
            }
            else if (!packet_recv) break;
            else { perror("Something went wrong"), close(new_socket); break; }
        }               
        close(new_socket);
    }
}