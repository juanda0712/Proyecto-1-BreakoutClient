
#ifndef CLIENT_SOCKETCLIENT_H
#define CLIENT_SOCKETCLIENT_H
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;


class SocketClient{
public:
    SocketClient();
    void conectar(); //se conecta a un servidor
    void setMensaje(const char* msn);

private:
    int descriptor; //identifica a los sistemas
    sockaddr_in info; //informacion del socket servidor

    static void* controlador(void* obj); //lleva el control de los mensajes de los clientes, cada cliente es un hilo

};
#endif //CLIENT_SOCKETCLIENT_H
