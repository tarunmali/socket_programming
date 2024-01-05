from socket import *
import sys

# Client class definitions
# We import socket libraries so we can simulate operations in a more 
# realistic way within the network.
# We are defining standard addresses, to avoid conflicts etc.

class Client:
    # This is the initialization function, where we define the default values
    # for our client.
    # We always start by requesting user data, to record
    # on our server.
    # We use a standard to identify them, with name and RG.
    def __init__(self):
        self.socket = socket(AF_INET, SOCK_STREAM)
        self.socket.connect(('127.0.0.1',9000))
        print('Enter Bank name and code')
        self.id = input().replace(' ', '')
        msg = 'id_' + self.id
        self.socket.send(msg.encode())
        self.socket.close()

    # Connect function responsible for starting the connection to the determined address.
    def connect(self):
        self.socket = socket(AF_INET, SOCK_STREAM)
        self.socket.connect(('127.0.0.1',9000))
        
    # Auxiliary function that will serve throughout the program, sending
    # messages to the user, via console.
    # There are several options, but all are performed by sending messages
    # to the server and receiving responses, to designate the screen.
    def sendmsg(self):
        print('Enter the number according to the option you want:')
        print('1: Withdraw')
        print('2: Deposit')
        print('3: Transfer')
        print('4: Balance')
        print('5: Exit')
        msg = input()

        print('')
        
        # Withdrawal option, returns success or failure message
        if msg == '1':
            print('Enter the amount')
            msg = msg + self.id + '.' + input().strip()
            self.connect()
            self.socket.send(msg.encode())
            response = self.socket.recv(1).decode()
            if response == '1':     
                print('Your request was successful!')
            else:
                print('Insufficient amount!')
            
        # Deposit option, returns success message
        elif msg == '2':
            print('Enter the amount')
            msg = msg + self.id + '.' + input().strip()
            self.connect()
            self.socket.send(msg.encode())
            print('Your request was successful!')

        # Transfer option, returns success or failure message, because
        # in addition to checking the balance, it checks the existence of the recipient in the
        # system.
        elif msg == '3':
            print('Enter the recipient\'s account (id)')
            recipient = input()
            print('Enter the amount')
            msg = msg + self.id + '.' + recipient + '.' + input().strip()
            self.connect()
            self.socket.send(msg.encode())
            response = self.socket.recv(1).decode()
            if response == '2':     
                print('Your request was successful!')
            elif response == '1':
                print('Invalid recipient!')
            else:
                print('Insufficient amount!')

        # Balance option, returns the value
        elif msg == '4':
            msg = msg + self.id
            self.connect()
            self.socket.send(msg.encode())
            balance = self.socket.recv(10).decode()
            print('Your balance is:', balance)
            
        # Exit option, finalizes the server and exits the current system,
        # the client.
        elif msg == '5':
            self.connect()
            self.socket.send(msg.encode())
            self.socket.close()
            sys.exit()

        # Error handling in case the user selects an
        # invalid option
        else:
            self.connect()
            print('Invalid operation!')

        print('')        
        
        self.socket.close()

client = Client()

while True:
    client.sendmsg()
