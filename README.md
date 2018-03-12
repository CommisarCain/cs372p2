# cs372p2
KNOWN ISSUES:
-l command messes up the file names
No matter what I do the client always holds on to its sockets, 
or the OS doesnt deallocate them. Everything I could find, I used. These sockets should
be getting freed.



use the make file :
$make
this will generate the server files. 

run the server:
./ftserver [port number]

run the client:
./ftclient.py [server_port_number]

enter commands -l or -g [filename to retrieve]

file collisions handled via time stamp added to duplicates

Might be worth extracredit:
I wrote a little cstring library that can handle some pretty fancy
situations. I'll probably expand on it in the future. My number one
hassles in C are always with strings. Gah!!!

Sources:
https://www.tutorialspoint.com/cprogramming/c_file_io.htm
https://stackoverflow.com/questions/5214578/python-print-string-to-text-file
https://stackoverflow.com/questions/409783/socket-shutdown-vs-socket-close
https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
https://stackoverflow.com/questions/16931770/makefile4-missing-separator-stop
http://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
http://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm
https://stackoverflow.com/questions/1921539/using-boolean-values-in-c
