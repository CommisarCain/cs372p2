#!/usr/bin/python3
#############################
#Description: operates as a simple FTP server
#Input: port to run on (int)
#############################

#TODO: command line arg of [server host] [server port number]
#TODO: command line support of <command>
#TODO: command line support of <filename>
#COMPLETE: command line support of [data port]
#TODO: establish connection to server
#TODO: after connection accept args
#TODO: support command [-l] as list all available files on new [dataport connection]
    #TODO: #SERVER see [data port] [string to print] send formatted string in [string to print] and blank [incoming filename]
#TODO: support command [-g] [filename] as get filename
    #TODO: [data port] connection works like this: 1st message [string to print (blank for nothing)], 2nd message [incoming file name] if blank: end connection else: file transfer to follow
    #TODO: #SERVER if [filename] is incorrect send formatted string in [string to print] and blank [incoming filename]
    #TODO: if filename already exists, append (int counter) i to name and try again.
#TODO: error check commands and then send an error string to server to be echoed back. Technically this fulfills the req. but not the spirit of the req. Client must display the returned error.
#TODO: capture connections on [data port]
#TODO: terminate after operation complete i.e. when data port is terminated, terminate.

#Extra credit
#TODO: transfer multiple file types
#TODO: Username/Password login
#TODO: Multi thread server....



import socket as S
from threading import Thread
import sys
import os
import datetime

class FTPClient:



    def __init__(self, serverport, host_addr="127.0.0.1", port=33489, dataport=33485):
        self.s = S.socket(S.AF_INET, S.SOCK_STREAM)
        self.s.bind((host_addr, int(port)))
        self.ds = S.socket(S.AF_INET, S.SOCK_STREAM)
        self.ds.bind((host_addr, int(dataport)))
        self.ds.listen(1)
        self.running = True
        self.action = 0
        self.BUFFER_SZ = 4096
        self.host_addr = host_addr
        self.port = port
        self.dataport = dataport
        self.serverport = serverport
        self.expected_filename = "default_name"


    def get_cmd(self):
        if len(sys.argv) > 2: #we have a command
            pass
        else: #no command found
            cmd = input("Input command: ")
            cmd = cmd.split()
            if cmd[0] == "-l":
                self.comm_server(1)
                self.dataport_handler()
                self.dc()
            elif len(cmd) == 2 and cmd[0] == "-g":
                self.comm_server(2, content=cmd[1])
                self.expected_filename = cmd[1]
                self.dataport_handler()
                self.dc()
            else:
                print("Comm server 3 called")
                self.comm_server(3, content="Unrecognized Input")
                self.dataport_handler()
                self.dc()

    def comm_server(self, cmd_type, content=""):

        try:
            self.s.connect((self.host_addr,int(self.serverport)))
            self.s.send(str(self.dataport).encode())
            dis_msg = self.s.recv(self.BUFFER_SZ)
            print("this is dis: " + dis_msg.decode())
        except:
            self.dc()
        if cmd_type == 1:
            self.s.send("1,".encode())
        elif cmd_type == 2:
            self.s.send(str("2,"+content).encode())
        else:
            self.s.send(str("3,"+content).encode())


    def dataport_handler(self):
        server, server_addr = self.ds.accept()
        msg = server.recv(self.BUFFER_SZ)
        msg = msg.decode()
        msg = msg.split(',')
        if msg[0] == "2":
            print("String file incoming!")
            if os.path.isfile(self.expected_filename):
                self.expected_filename = self.expected_filename+str( datetime.datetime.now())
            tf = open(self.expected_filename,"w")
            tf.write(msg[1])
            tf.close()
        else:
            print(msg[1:])

    def dc(self):
        try:
            self.s.shutdown(S.SHUT_RDWR)
            self.s.close()
        except:
            pass
        try:
            self.ds.shutdown(S.SHUT_RDWR)
            self.ds.close()
        except:
            pass
        print("Closing Time, you dont have to go home!!!!!")
        print("but you can't run heeeeeere")






c = FTPClient(sys.argv[1])
c.get_cmd()










#space comment
