#ifndef SERVER_H
#define SERVER_H

class Server {
public:
    /*
    * Ejecuta la logica del servidor, creando un hilo
    * que aceptará conexiones entrantes hasta que se 
    * ingrese una 'q' por la entrada estándar
    * */
    void start(const char *servname);
};

#endif
