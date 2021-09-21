#include "SocketClient.h"

SocketClient::SocketClient() {}

void SocketClient::conectar() {
    //Crear un descriptor
    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (descriptor < 0) //valida la creacion del socket
        cout << "Error al crear el socket " << endl;

    info.sin_family = AF_INET; //IPV4 tipo de conexion
    info.sin_addr.s_addr = inet_addr("192.168.0.11"); //acepta a cualquiera con mi ip y mi puerto
    info.sin_port = ntohs(4050); //definimos el puerto
    memset(&info.sin_zero, 0, sizeof(info.sin_zero)); //limpiamos la estructura
    cout << "Se creo el socket " << endl;

    if ((connect(descriptor, (sockaddr *)&info, (socklen_t)sizeof(info)))<0){
        cout << "Error al conectarse con el servidor";
    }
    cout << "Nos hemos conectado correctamente" << endl;
    pthread_t hilo;
    pthread_create(&hilo, 0, SocketClient::controlador, (void *)this);
    pthread_detach(hilo);

}

void * SocketClient::controlador(void *obj) {
    SocketClient* c = (SocketClient *)obj;
    bool estado = true;
    while(true){
        string mensaje;
        char buffer[1024] = {0};
        //aca va la condicion para cerrar el while (cerrar la conexion con el socket)
        if (mensaje == "salir"){
            break;
        }

        while(true){
            memset(buffer,0,1024);
            int bytes = recv(c->descriptor, buffer, 1024, 0); //funcion bloqueante
            mensaje.append(buffer, bytes);
            if (bytes <= 0 ){
                close(c->descriptor);
                pthread_exit(NULL);
            }
            if(bytes < 1024){
                break;
            }
        }
        cout << mensaje << endl; //mensaje del cliente
        //mensaje es la variable que me llega del cliente y tengo que ver que hago con ella en el servidor
        // se puede usar para el juego o para una clase
    }
    close(c->descriptor);
    pthread_exit(NULL);

}

void SocketClient::setMensaje(const char *msn) {
    send(descriptor, msn, strlen(msn), 0);
}