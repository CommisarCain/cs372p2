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

class FTPClient:



    def __init__(self, port, host_addr, dataport=33485):
        self.s = S.socket(S.AF_INET, S.SOCK_STREAM)
        self.s.bind(("127.0.0.1", int(port)))
        self.ds = S.socket(S.AF_INET, S.SOCK_STREAM)
        self.ds.bind(("127.0.0.1", int(dataport)))
        self.ds.listen(1)
        self.running = True


    def

















#space comment
