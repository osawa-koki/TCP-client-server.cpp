#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

  std::cout << "ð¸ð¸ð¸ Starting server..." << std::endl;

  // ã½ã±ãããä½æ
  int listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // ã½ã±ããã¢ãã¬ã¹æ§é ä½ãä½æãããµã¼ãã®ã¢ãã¬ã¹æå ±ãè¨­å®
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(12345); // ãã¼ãçªå·
  serverAddr.sin_addr.s_addr = INADDR_ANY; // ãã¹ã¦ã®ã­ã¼ã«ã«IPã¢ãã¬ã¹ãä½¿ç¨

  // ã½ã±ããã«ã¢ãã¬ã¹ããã¤ã³ã
  bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

  // ã¯ã©ã¤ã¢ã³ãããã®æ¥ç¶è¦æ±ãå¾æ©
  listen(listenSocket, 5);

  std::cout << "ð¬ð¬ð¬ Waiting for client..." << std::endl;

  while (true) {
    // ã¯ã©ã¤ã¢ã³ãããã®æ¥ç¶è¦æ±ãåãå¥ãã
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(listenSocket, (sockaddr*)&clientAddr, &clientAddrSize);

    std::cout << "ððð Client connected..." << std::endl;

    // ã¯ã©ã¤ã¢ã³ãããã®ã¡ãã»ã¼ã¸ãåä¿¡
    char buffer[1024];
    int recvSize = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    // åä¿¡ãããã¼ã¿ã®æ«å°¾ã«NULLæå­ãè¿½å 
    buffer[recvSize] = '\0';

    // åä¿¡ããã¡ãã»ã¼ã¸ãè¡¨ç¤º
    std::cout << "Received: " << buffer << std::endl;

    std::cout << "ð³ð³ð³ Sending message to client..." << std::endl;

    // ã¯ã©ã¤ã¢ã³ãã«ã¡ãã»ã¼ã¸ãéä¿¡
    std::string message = "Hello, client!";
    send(clientSocket, message.c_str(), message.size(), 0);

    // ã½ã±ãããéãã
    close(clientSocket);
  }

  // ãªã¹ãã³ã°ã½ã±ãããéãã
  close(listenSocket);

  return 0;
}
