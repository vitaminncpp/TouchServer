import socket
from time import sleep
import threading

def getNetworkIp():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    s.connect(('<broadcast>', 0))
    return s.getsockname()[0]

ip = getNetworkIp()
SERVER_PORT = 5559

while(True):
    sock1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) 
    sock1.bind((ip, SERVER_PORT))
    data, addr = sock1.recvfrom(1024)
    print(data)