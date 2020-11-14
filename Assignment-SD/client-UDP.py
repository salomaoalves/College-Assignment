#client.py----------------------------------------------

import socket 

s = socket.socket()
host = socket.gethostname()
port = 1234

print('conectando-se ao servidor')
s.connect((host, port))
dest = (host, port)
print('Conectado')

while 1:
    
    msg = input("Digite mensagem: ") 
    s.sendall(msg.encode())
    if msg=='SAIR':
        print('Desconectando.')
        break
    print('Mensagem enviada')

    print('Esperando resposta...')
    data = s.recv(2048)
    print(f'Mensagem recebida: {data.decode()}')

s.close()