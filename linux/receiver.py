import socket
from time import sleep
import threading

ip = '192.168.1.10'
ECHO_PORT = 5560
SERVER_PORT = 5559

while(True):
    sock1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) 
    sock1.bind((ip, SERVER_PORT))
    data, addr = sock1.recvfrom(1024)
    print(data)