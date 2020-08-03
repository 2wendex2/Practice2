# Dependencies
Server-Socket = libevent  
Client-Socket = winsock  
Game = glfw, soil  
# Visual Studio Set Up
-Additional Include Directories = $(PATH_TO_LIBEVENT)libevent\include  
-Additional Library Directories = $(PATH_TO_LIBEVENT)libevent\lib  
-Additional Dependencies = event.lib;%(AdditionalDependencies);Ws2_32.lib;  
# [Unit-Tests](./vs2019/Unit-Tests)
Google Test  
![Tests](https://personalfebus.s-ul.eu/ZIxU8yrs)  
