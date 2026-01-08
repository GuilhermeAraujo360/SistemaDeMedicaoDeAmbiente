# |=======================================================================================|
# | código cliente, feito por Guilherme Araujo                                            | 
# |=======================================================================================|


import socket

HOST = 'xxx.xxx.xxx'
PORT = 8080

# função que capta byte a byte do servidor, que após isso é traduzida para a linguagem humana 
# o intuito dela é que cada mensagem seja lida corretamente e não fique lixo no buffer 
# comprometendo futuras requisições 
def traducao(sock):
    mensagem = b""
    while b'\n' not in mensagem:
        byte = sock.recv(1)
        if not byte:
            break
        mensagem += byte
    return mensagem.decode().strip()

    
# criação de um socket que recebe e envia dados TCP
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as cliente:
    cliente.settimeout(60.0)

    
# conexão ao servidor    
    try:
        cliente.connect((HOST, PORT))
        print("Conectado ao sistema Phoenix\n")
        
      
        try:
            introducao = traducao(cliente)
            print(introducao)
        except socket.timeout:
            print("erro ao inicar conexao")
            introducao = ""

            

        while True:
            print("\nDigite:")
            print("TEMPERATURA")
            print("UMIDADE")
            print("SAIR")

            prompt = input("Comando: ").strip().upper()
            
        
            cliente.sendall((prompt + "\n").encode())
            
            if prompt == "SAIR":
                print("Encerrando...")
                break
            
            try:
                resposta = traducao(cliente)
                print("Phoenix:", resposta)
            except socket.timeout:
                print("Phoenix não respondeu")
                break

# mensagnes de erros              
    except ConnectionRefusedError:
        print("Erro: Não foi possível conectar ao Phoenix")
    except socket.timeout:
        print("Erro: Timeout na conexão")
    except Exception as e:
        print(f"Erro inesperado: {e}")
