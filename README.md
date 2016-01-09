# ext-c-lib
Extended C library. It is a easy to use library for fast coding on C-language for<br>
many platforms.
<br>
If you want to compile library with all modules, you need to write:
<br>
For Unix (Linux,FreeBSD,MacOS...):
````
./build.sh -p unix -m all
````
For Windows:
````
./build.sh -p win32 -m all
````
<br>
If you want to compile library with certain modules, you need to write:
````
./build.sh -p unix -m tcp,slist,dlist,jcfg,tmr
````
<br>
For Windows you need to install MSYS2 tool and Jansson library
<br> (if you want JsonConfigs module) from official site:<br>
<a href="https://msys2.github.io/">https://msys2.github.io/</a>
<br>
<a href="http://www.digip.org/jansson/">http://www.digip.org/jansson/</a>
<br>
Tested platforms:
````
Linux Fedora
Windows 7
````
<br>
Developed by: <b>Sergey Denisov</b>
<br>
Email: <b>DenisovS21@gmail.com</b>
<br>
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/3b/LGPLv3_Logo.svg/400px-LGPLv3_Logo.svg.png" />
