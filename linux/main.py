import socket
from time import sleep

ip = '192.168.1.255'

def main():
    # interfaces = socket.getaddrinfo(host=ip, port=None, family=socket.AF_INET)

    while True:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) 
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        sock.bind((ip,0))
        sock.sendto(b'x', ("255.255.255.255", 5560))
        sock.close()
        sleep(3)

main()
