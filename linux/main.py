import socket
from time import sleep
import threading
import json

# TODO: find a way to use soft coded IP
ip_broadcast = '192.168.1.255'
ip_server = '192.168.1.10'
ECHO_PORT = 5560
SERVER_PORT = 5559

def echo():
    while(True):
        sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) 
        sock2.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        sock2.bind((ip_broadcast, ECHO_PORT))
        sock2.sendto(b'x', ("255.255.255.255", ECHO_PORT))
        print('---- Sending echo ---')
        sock2.close()
        sleep(3)
    
def server():
    while(True):
        sock1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) 
        sock1.bind((ip_server, SERVER_PORT))
        data, addr = sock1.recvfrom(1024)
        parseInputCommand(data)

def parseInputCommand(input):
    obj = json.loads(input)
    inputType = int(obj['dwFlags'])
    # print(inputType)
    
    if inputType == 2:
        print('Left Mouse down')
    
    if inputType == 4:
        print('Left Mouse up')
    
    if inputType == 8:
        print('Right Mouse down')

    if inputType == 16:
        print('Right Mouse up')
    


x1 = threading.Thread(target=echo)
x2 = threading.Thread(target=server)

x1.start()
x2.start()