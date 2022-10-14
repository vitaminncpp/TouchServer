import socket
from time import sleep

host = socket.gethostname()
port = 5560  # initiate port no above 1024

print(host)
server_socket = socket.socket()  # get instance
# look closely. The bind() function takes tuple as argument
server_socket.bind(('192.168.43.255', port))  # bind host address and port together

# configure how many client the server can listen simultaneously
server_socket.listen(2)
conn, address = server_socket.accept()  # accept new connection
print("Connection from: " + str(address))