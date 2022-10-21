import socket
from time import sleep
import threading

ip = '192.168.1.255'
ECHO_PORT = 5560
SERVER_PORT = 5559

while(True):
    sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) 
    sock2.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    sock2.bind((ip,ECHO_PORT))
    sock2.sendto(b'x', ("255.255.255.255", ECHO_PORT))
    sock2.close()
    sleep(3)