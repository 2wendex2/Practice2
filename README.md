# Dependencies
-libevent(server-socket)
-asio(client-socket)
# Visual Studio Set Up
-Additional Include Directories = $(PATH_TO_LIBEVENT)libevent\include
-Additional Library Directories = $(PATH_TO_LIBEVENT)libevent\lib
-Additional Dependencies = event.lib;%(AdditionalDependencies);Ws2_32.lib;
