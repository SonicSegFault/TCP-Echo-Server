# TCP Echo Server

A simple TCP echo server and client implementation in C++ for learning socket programming.  
The server listens on a TCP port, accepts incoming connections, and echoes back any data it receives.  
The client connects to the server, sends a message.

---

## ✨ Features
- **Server**
  - Listens on port `6666` (default).
  - Accepts multiple client connections sequentially.
  - Echoes back any message received.
- **Client**
  - Connects to the server using IPv4 (`127.0.0.1` by default).
  - Sends a message reliably using a robust `send()` loop.
  - Receives and prints the echoed reply.

---

## 📦 Requirements
- Linux/Unix environment
- g++ (C++ compiler)
- Basic networking tools (`nc`, `netstat` optional for testing)

---

## ⚙️ Build Instructions
Compile the server and client separately:

```bash
# Build server
g++ server.cpp -o server

# Build client
g++ client.cpp -o client
```

---

## 🚀 Usage
Start the server

```bash
./server
```
The server will start listening on port 6666.

Run the client

```bash
./client
```
The client will connect to 127.0.0.1:6666, send "Wsg!"
