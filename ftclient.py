#!/usr/bin/python3
#############################
#Description: operates as a simple FTP server
#Input: port to run on (int)
#############################

#TODO: command line arg of [server host] [server port number]
#TODO: command line support of <command>
#TODO: command line support of <filename>
#TODO: command line support of [data port]
#TODO: establish connection to server
#TODO: after connection accept args
#TODO: support command [-l] as list all available files on new [dataport connection]
    #TODO: SERVER see [data port] [string to print] send formatted string in [string to print] and blank [incoming filename]
#TODO: support command [-g] [filename] as get filename
    #TODO: [data port] connection works like this: 1st message [string to print (blank for nothing)], 2nd message [incoming file name] if blank: end connection else: file transfer to follow
    #TODO: SERVER if [filename] is incorrect send formatted string in [string to print] and blank [incoming filename]
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

class Chat_Server:


	def __init__(self, port, max_clients):
		#this part sets up socket addr and port
		self.ssoc = S.socket(S.AF_INET, S.SOCK_STREAM)
		self.ssoc.bind(("127.0.0.1", int(port)))
		self.ssoc.listen(max_clients)
		self.clients = []
		self.client_addresses = []
		self.BUFFER_SZ = 500
		self.name = S.gethostname()
		self.threads = []
		self.running = True
		print("Server started on port %s" % port)
		print("Host name: %s" %S.gethostname())

	def chatter(self):
		conn = Thread(target=self.handle_New_Conn)
		self.threads.append(conn)
		conn.start()
		while True:
			msg = input(self.name + ">")
			if msg == "/quit":
				self.quitAll()
				break
			self.broadcast((self.name + ">" + msg).encode(), None)


	def handle_New_Conn(self):
		self.ssoc.settimeout(0.5)
		while self.running:#spawns a new thread for every connection after handling
			   #the initial setup
			#print("Accepting Connections!!!")
			try:
				client, client_address = self.ssoc.accept()#handle client connecting
			except:
				client = None
			if client:
				#print("{} has connected".format(client_address))
				self.clients.append(client)#list of all clients for repeating msg
				self.client_addresses.append(client_address) #collect ips
				client.send("connected!".encode())#all transmissions have
							  #to be in bytes
				nt = self.client_Thread #get function alias
				conn = Thread(target=nt, args=(client,))
				self.threads.append(conn)
				conn.start()

	def client_Thread(self, client):
		while self.running:
			try:
				msg = client.recv(self.BUFFER_SZ)#if you recieve 0 bytes
								 #then client dc'ed
			except:
				try:
					client.close()
					self.clients.remove(client)
					break
				except ValueError:
					pass

			if msg:
				print(" ")
				print(msg.decode())
				print(self.name +">", end="", flush=True)

				self.broadcast(msg, client)
			else:
				client.close()
				try:
					self.clients.remove(client)
				except ValueError:
					pass

				break

	def broadcast(self, msg, client):
		#print(msg)
		for sock in self.clients:
			if sock != client:
				sock.send(msg)#  inc message is byte encoded no need to encode

	def quitAll(self):
		self.running = False

cs = Chat_Server(sys.argv[1], 5)
top_thread = Thread(target=cs.chatter)
top_thread.start()
top_thread.join()
