#ifndef CLIENT_H
#define CLIENT_H

class Client {
public:
    /*
    * Ejecuta la logica del cliente, estableciendo la conexión
    * con el servidor y procesando los comandos recibidos por
    * la entrada estándar
    * */
    void start(
        const char *hostname,
        const char *servname);
};
#endif
