#Configura��o
module Settings
  SERVER_HOST = "seu_ip"# Endere�o host ou Ip
  SERVER_PORT = 5000 # Id da porta(aconcelhado >= 1000)
  SERVER_PASS = "senha"
  
  PRINT_PACKETS = false # Loga os pacontes na tela
  WAIT_TO_EXIT = true # Espera o usuario pressionar ENTER para sair
  
  DB_HOST = "localhost" # Endere�o host ou IP
  DB_USER = "root" # Usuario
  DB_PASS = "senha_mysql" # Senha
  DB_NAME = "nome_da_database_no_mysql" # Nome da database
end