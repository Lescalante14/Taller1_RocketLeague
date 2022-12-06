#include <string>
#include <iostream>
#include <QApplication>

#include "client/threads/client_thread_receiver.h"
#include "client/threads/client_thread_sender.h"
#include "LobbyClient.h"
#include "client.h"
#include "Game.h"
#include "common/blocking_queue.h"
#include "common/protocol.h"
#include "common/socket.h"

#include "qt-menu/menu.h"

void Client::run(
        const char *hostname,
        const char *servname) {
    Socket skt(hostname, servname);
    Protocol protocol(skt);

    BlockingQueue<std::string> received_queue;
    BlockingQueue<std::string> to_send_queue;

    ClientThreadReceiver receiver(protocol, received_queue);
    ClientThreadSender sender(protocol, to_send_queue);
    receiver.start();
    sender.start();

    // LobbyClient lobby(received_queue, to_send_queue);
	int _argc = 0;
	char *_argv = NULL;

	bool play = false;
	
	QApplication g_client(_argc, &_argv);
    Menu m(&play, to_send_queue, received_queue);
    m.show();
    g_client.exec();

    try {
        if (play) {
            Game game(received_queue, to_send_queue);
            game.run();
        }
    } catch (const std::exception &e) {
    std::cerr << "Exception caught in Game: '" << e.what() << "'" << std::endl;
    } catch (...) {
        std::cerr << "Unknown error caught in Game" << std::endl;
    }

    received_queue.close();
    to_send_queue.close();
    protocol.closeConnection();
    receiver.join();
    sender.join();
}
