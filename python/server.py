from socket import *

# Server class definitions
# We import socket libraries so we can simulate operations in a more 
# realistic way within the network.
# We are defining standard addresses, to avoid conflicts etc.

class Server:
    # This is the initialization function, where we define the default values
    # for our socket.
    # In addition, we initialize an array to store the data
    # of possible clients.
    def __init__(self):
        self.socket = socket(AF_INET, SOCK_STREAM)
        self.socket.bind(('127.0.0.1',9000))
        self.clients = {}
        
    # Listen operation, where we wait and handle requests by
    # part of the client, from the packets.
    def listen(self):
        self.socket.listen(5)
        (client, dummy) = self.socket.accept()
        packet = client.recv(50).decode()
        
        # Treatment we do for the first moment of registration,
        # where we receive the client's information, saving his id
        # and initializing his zero balance.
        # In all the following options, we observe the request from the
        # character '.' ; what happens is that we separate values and flags, 
        # between points " . " to know what is ID and what is value.
        if packet[:3] == 'id_':
            self.clients[packet[3:]] = 0
            print('client id:', packet[3:])
        
        # Withdrawal option, returns success or failure message (0 or 1)
        elif packet[0] == '1':
            id, amount = packet[1:].split('.')

            if abs(int(amount)) > self.clients[id]:
                msg = '0' #insufficient_amount
                client.sendall(msg.encode())
            else:
                msg = '1' #sufficient_amount
                client.sendall(msg.encode())
                self.clients[id] -= abs(int(amount))

        # Deposit option, where we only add amount to the client,
        # without return.
        elif packet[0] == '2':
            id, amount = packet[1:].split('.')
            self.clients[id] += abs(int(amount))

        # Transfer option, returns success or failure message, because
        # in addition to checking the balance, it checks the existence of the recipient in the
        # system. If everything is in order, we perform the
        # mathematical operations.
        elif packet[0] == '3':
            id, id2, amount = packet[1:].split('.')
            if abs(int(amount)) > self.clients[id]:
                msg = '0' #insufficient_amount
                client.sendall(msg.encode())
            elif id2 not in self.clients:
                msg = '1' #invalid_recipient
                client.sendall(msg.encode())
            else:
                msg = '2' #sufficient_amount
                self.clients[id] -= abs(int(amount))
                self.clients[id2] += abs(int(amount))
                client.sendall(msg.encode())
                
        # Balance option, returns the value of the specific client.
        elif packet[0] == '4':
            client.sendall(str(self.clients[packet[1:]]).encode())
            
        client.close()

server = Server()

while True:
    server.listen()
