import socket
import sys
import psutil, time
import datetime
from thread import *

HOST = ''
PORT = 8888

print '[INFO] Starting CPU Usage Daemon...'
print '[INFO] Trying to bind to port ' + str(PORT)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print '[ERROR] Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()

print '[INFO] Bind completed successfully.'
s.listen(10)
print '[INFO] Now listening for clients...'

def clientthread(conn):
    conn.send(str(int(psutil.cpu_percent())))
    conn.close()

while 1:
    conn, addr = s.accept()
    print '[INFO] Sent CPU usage to ' + addr[0] + ':' + str(addr[1])
    start_new_thread(clientthread ,(conn,))

s.close()
