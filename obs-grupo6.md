El server tiene varios crashes. Basta con conectar 1 cliente
y desconectarlo para tener esto:

```
==920== Conditional jump or move depends on uninitialised value(s)
==920==    at 0x12727D: operator() (thread_acceptor.cpp:12)
==920==    by 0x12727D: operator()<__gnu_cxx::__normal_iterator<Thread**, std::vector<Thread*> > > (predefined_ops.h:318)
==920==    by 0x12727D: __find_if<__gnu_cxx::__normal_iterator<Thread**, std::vector<Thread*> >, __gnu_cxx::__ops::_Iter_pred<ThreadAcceptor::cleanFinishedHandlers()::<lambda(Thread*)> > > (stl_algobase.h:2099)
==920==    by 0x12727D: __find_if<__gnu_cxx::__normal_iterator<Thread**, std::vector<Thread*> >, __gnu_cxx::__ops::_Iter_pred<ThreadAcceptor::cleanFinishedHandlers()::<lambda(Thread*)> > > (stl_algobase.h:2114)
==920==    by 0x12727D: __remove_if<__gnu_cxx::__normal_iterator<Thread**, std::vector<Thread*> >, __gnu_cxx::__ops::_Iter_pred<ThreadAcceptor::cleanFinishedHandlers()::<lambda(Thread*)> > > (stl_algo.h:816)
==920==    by 0x12727D: remove_if<__gnu_cxx::__normal_iterator<Thread**, std::vector<Thread*> >, ThreadAcceptor::cleanFinishedHandlers()::<lambda(Thread*)> > (stl_algo.h:894)
==920==    by 0x12727D: ThreadAcceptor::cleanFinishedHandlers() (thread_acceptor.cpp:8)
==920==    by 0x127392: ThreadAcceptor::run() (thread_acceptor.cpp:40)
==920==    by 0x12F87F: Thread::runExpecting() (thread.cpp:7)
==920==    by 0x494A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==920==    by 0x4C33B42: start_thread (pthread_create.c:442)
==920==    by 0x4CC4BB3: clone (clone.S:100)
```

Al conectarse 2 jugadores, jugar un rato, cerrarlos y querer crear una
segunda partida con 2 nuevos jugadores el server crashea mal (no se
cierra pero valgrind muestra muchos errores y la segunda partida no
empieza).

Esto es solo un fragmento:

```
==929== Thread 2:
==929== Conditional jump or move depends on uninitialised value(s)
==929==    at 0x12823D: operator() (thread_matchs_handler.cpp:10)
==929==    by 0x12823D: operator()<__gnu_cxx::__normal_iterator<ThreadMatchHandler**, std::vector<ThreadMatchHandler*> > > (predefined_ops.h:318)
==929==    by 0x12823D: __find_if<__gnu_cxx::__normal_iterator<ThreadMatchHandler**, std::vector<ThreadMatchHandler*> >, __gnu_cxx::__ops::_Iter_pred<ThreadMatchsHandler::cleanFinishedHandlers()::<lambda(ThreadMatchHandler*)> > > (stl_algobase.h:2099)
==929==    by 0x12823D: __find_if<__gnu_cxx::__normal_iterator<ThreadMatchHandler**, std::vector<ThreadMatchHandler*> >, __gnu_cxx::__ops::_Iter_pred<ThreadMatchsHandler::cleanFinishedHandlers()::<lambda(ThreadMatchHandler*)> > > (stl_algobase.h:2114)
==929==    by 0x12823D: __remove_if<__gnu_cxx::__normal_iterator<ThreadMatchHandler**, std::vector<ThreadMatchHandler*> >, __gnu_cxx::__ops::_Iter_pred<ThreadMatchsHandler::cleanFinishedHandlers()::<lambda(ThreadMatchHandler*)> > > (stl_algo.h:816)
==929==    by 0x12823D: remove_if<__gnu_cxx::__normal_iterator<ThreadMatchHandler**, std::vector<ThreadMatchHandler*> >, ThreadMatchsHandler::cleanFinishedHandlers()::<lambda(ThreadMatchHandler*)> > (stl_algo.h:894)
==929==    by 0x12823D: ThreadMatchsHandler::cleanFinishedHandlers() (thread_matchs_handler.cpp:6)
==929==    by 0x1283E5: ThreadMatchsHandler::run() (thread_matchs_handler.cpp:45)
==929==    by 0x12F87F: Thread::runExpecting() (thread.cpp:7)
==929==    by 0x494A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==929==    by 0x4C33B42: start_thread (pthread_create.c:442)
==929==    by 0x4CC4BB3: clone (clone.S:100)
==929==
Exception caught in a thread: 'Exception caught in a thread: 'socket was closed by the other end.'
socket was closed by the other end.'
==929== Thread 10:
==929== Invalid read of size 8
==929==    at 0x12C817: operator- (stl_deque.h:356)
==929==    by 0x12C817: size (stl_deque.h:1233)
==929==    by 0x12C817: size (stl_queue.h:209)
==929==    by 0x12C817: size (blocking_queue.h:37)
==929==    by 0x12C817: operator() (lobby_match.cpp:60)
==929==    by 0x12C817: for_each<__gnu_cxx::__normal_iterator<BlockingQueue<std::__cxx11::basic_string<char> >**, std::vector<BlockingQueue<std::__cxx11::basic_string<char> >*> >, LobbyMatch::push_to_output_queues(MatchState)::<lambda(BlockingQueue<std::__cxx11::basic_string<char> >*)> > (stl_algo.h:3820)
==929==    by 0x12C817: LobbyMatch::push_to_output_queues(MatchState) (lobby_match.cpp:55)
==929==    by 0x127F4F: ThreadMatchHandler::run() (thread_match_handler.cpp:41)
==929==    by 0x12F87F: Thread::runExpecting() (thread.cpp:7)
==929==    by 0x494A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==929==    by 0x4C33B42: start_thread (pthread_create.c:442)
==929==    by 0x4CC4BB3: clone (clone.S:100)
==929==  Address 0x81d0d68 is in a rw- anonymous segment

==929== Invalid read of size 8
==929==    at 0x12C81E: operator- (stl_deque.h:356)
==929==    by 0x12C81E: size (stl_deque.h:1233)
==929==    by 0x12C81E: size (stl_queue.h:209)
==929==    by 0x12C81E: size (blocking_queue.h:37)
==929==    by 0x12C81E: operator() (lobby_match.cpp:60)
==929==    by 0x12C81E: for_each<__gnu_cxx::__normal_iterator<BlockingQueue<std::__cxx11::basic_string<char> >**, std::vector<BlockingQueue<std::__cxx11::basic_string<char> >*> >, LobbyMatch::push_to_output_queues(MatchState)::<lambda(BlockingQueue<std::__cxx11::basic_string<char> >*)> > (stl_algo.h:3820)
==929==    by 0x12C81E: LobbyMatch::push_to_output_queues(MatchState) (lobby_match.cpp:55)
==929==    by 0x127F4F: ThreadMatchHandler::run() (thread_match_handler.cpp:41)
==929==    by 0x12F87F: Thread::runExpecting() (thread.cpp:7)
==929==    by 0x494A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==929==    by 0x4C33B42: start_thread (pthread_create.c:442)
==929==    by 0x4CC4BB3: clone (clone.S:100)
==929==  Address 0x81d0d48 is in a rw- anonymous segment
```

Luego de eso el server ya no se cierra presionando una `q` (posiblemente
se queda bloqueado en join a un thread q crasheo).

De lado del cliente no hay forma de distinguir q autos son de un equipo
o de otro. El resto de la UI esta muy incompleta.


