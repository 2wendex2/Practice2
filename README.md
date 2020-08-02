# Dependencies
Server = libevent  
Client = winsock, opengl, glfw, soil  

# Visual Studio Set Up
Server
-Additional Include Directories = $(PATH_TO_LIBEVENT)libevent\include  
-Additional Library Directories = $(PATH_TO_LIBEVENT)libevent\lib  
-Additional Dependencies = event.lib;%(AdditionalDependencies);Ws2_32.lib; 

Client
-Additional Include Directories = $(PATH_TO_GLFW)include\GLFW;$(PATH_TO_SOIL)include\SOIL;
-Additional Library Directories = $(PATH_TO_GLFW)libvc-2019;$(PATH_TO_SOIL)lib;
-Additional Dependencies = opengl32.lib;glfw3.lib;SOIL.lib;

# [Unit-Tests](https://github.com/2wendex2/Practice2/tree/server_dev/vs2019/Unit-Tests)
Google Test  
![Tests](https://personalfebus.s-ul.eu/ZIxU8yrs)  
