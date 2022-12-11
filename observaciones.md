# cppcheck

Hay algunos warnings q deberían revisarse.

# valgrind

Ok, no hay errores del lado del server.

Lo único es que logre colgarlo una vez al tener 2 partidas en juego e ir
cerrando los clientes sin q las partidas terminen y luego presionar 'q'
en el server.

Le di ctrl-c para forzar el cierre y valgrind capturó esto:

```
==1289== Process terminating with default action of signal 2 (SIGINT)
==1289==    at 0x4C30197: __futex_abstimed_wait_common64 (futex-internal.c:57)
==1289==    by 0x4C30197: __futex_abstimed_wait_common (futex-internal.c:87)
==1289==    by 0x4C30197: __futex_abstimed_wait_cancelable64 (futex-internal.c:139)
==1289==    by 0x4C356A3: __pthread_clockjoin_ex (pthread_join_common.c:105)
==1289==    by 0x494A326: std::thread::join() (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==1289==    by 0x127EF4: Server::run(char const*) (server.cpp:32)
==1289==    by 0x1192B8: main (server_main.cpp:21)
```

Entiendo q el server estaba colgado en ese join.
