#server.py----------------------------------------------

import socket

s = socket.socket()
host = socket.gethostname()
port = 1234       
s.bind((host, port))       

s.listen(5)
while True:
    # Establish connection with client.
    print('Esperando conexão...')
    c, addr = s.accept()
    print('Conectado')
    
    while True:
        print('Esperando mensagem...')
        msg = c.recv(2048)
        if msg.decode()=='SAIR':
            print('Conexão encerrada.')
            break
        print(f'Mensagem recebida: {msg.decode()}')

        msg = input('Digite Resposta: ')
        c.sendall(msg.encode())
        print('Resposta enviada')
             
    c.close()