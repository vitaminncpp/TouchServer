import socket
from time import sleep
import threading
import json
import pyautogui

def getNetworkIp():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    s.connect(('<broadcast>', 0))
    return s.getsockname()[0]

def getBroadcastAdd(ip):
    block = ip.split('.')
    return block[0]+'.'+block[1]+'.'+block[2]+'.255'

ip_server = getNetworkIp()
ip_broadcast = getBroadcastAdd(ip_server)
print(ip_broadcast)
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

    if inputType == 1:
        xDisp = int(obj['dx']) * 10
        yDisp = int(obj['dy']) * 10
        print('Moving:',xDisp,yDisp)
        pyautogui.move(xDisp, yDisp)
        # mouse.move(100, 50)

    if inputType == 2:
        print('Left Mouse down')
        pyautogui.mouseDown()
    
    if inputType == 4:
        print('Left Mouse up')
        pyautogui.mouseUp()
    
    if inputType == 8:
        print('Right Mouse down')
        pyautogui.mouseDown(button='right')
        
    if inputType == 16:
        print('Right Mouse up')
        pyautogui.mouseUp(button='right')

x1 = threading.Thread(target=echo)
x2 = threading.Thread(target=server)

x1.start()
x2.start()
