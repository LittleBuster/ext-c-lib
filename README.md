# ext-c-lib
Extended C library. It is a easy to use library for fast coding on C-language for many platforms.
<br>
<br>
<b>Building:</b><br>
If you want to compile library with all modules, you need to write:
<br>
For Linux:
````
./build.sh -p unix -m all
````
For FreeBSD, MacOS:
````
./build.sh -p unix -c clang -m all
````
For Windows:
````
./build.sh -p win32 -m all
````
If you want to compile library with certain modules, you need to write:
````
./build.sh -p unix -m tcp,slist,dlist,jcfg,tmr,gtime
````
<br>
For Windows you need to install MSYS2 tool and Jansson library (if you want JsonConfigs module) from official site:<br>
<a href="https://msys2.github.io/">https://msys2.github.io/</a>
<br>
<a href="http://www.digip.org/jansson/">http://www.digip.org/jansson/</a>
<br>
<br>
<b>Installation:</b><br>
If you want to install library, you need to write:
For Unix (Linux,FreeBSD,MacOS...):
````
./build.sh -p unix install
````
For Windows:
````
./build.sh -p win32 install
````
<br>
<b>Removing:</b><br>
If you want to remove library, you need to write:
For Unix (Linux,FreeBSD,MacOS...):
````
./build.sh -p unix remove
````
For Windows:
````
./build.sh -p win32 remove
````
<br>
<b>Cleaning:</b><br>
If you want to clean temporary files and library in folder after installing, you need to write:
For Unix (Linux,FreeBSD,MacOS...):
````
./build.sh -p unix clean
````
For Windows:
````
./build.sh -p win32 clean
````
<br>
<b>Tested platforms:</b><br>
````
Linux Fedora
Windows 7
````
<br>
Developed by: <b>Sergey Denisov</b>
<br>
Email: <b>DenisovS21@gmail.com</b>
<br>
<br>
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/3b/LGPLv3_Logo.svg/400px-LGPLv3_Logo.svg.png" />
