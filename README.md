README - Sistema de Gerenciamento Hortifruti

1. Visão Geral do Projeto
Este projeto foi desenvolvido como parte do Projeto Integrado Multidisciplinar (PIM) dos cursos superiores em Análise e Desenvolvimento de Sistemas (ADS) da Universidade Paulista (UNIP). Ele visa implementar um sistema de gerenciamento de um estabelecimento Hortifruti, integrando o controle de produtos, clientes, fornecedores e estoque.
O projeto foi desenhado para rodar em um ambiente console utilizando a linguagem C e banco de dados SQLite. Além disso, o projeto integra conceitos de disciplinas como Fundamentos de Redes de Dados e Comunicação, Engenharia de Software, Lógica, e Desenvolvimento Sustentável.
2. Funcionalidades
2.1. Cadastro e Consulta de Produtos
O sistema permite:
•	Cadastro de novos produtos, com detalhes como nome, quantidade e tipo (fruta, verdura, legume, etc).
•	Consulta por produtos já cadastrados, exibindo dados completos.
•	Atualização de informações dos produtos existentes.
2.2. Gerenciamento de Estoque
•	Registro de entradas e saídas de produtos no estoque.
•	Consulta aos produtos com menor estoque para priorizar reposição.
2.3. Controle de Clientes e Fornecedores
•	Cadastro de clientes, incluindo nome, CPF e endereço.
•	Registro de fornecedores com CNPJ, nome e endereço.
2.4. Relatórios de Vendas e Movimentação de Estoque
•	Relatório de vendas por cliente.
•	Relatório de produtos mais vendidos e com maior saída de estoque.
3. Configuração do Ambiente
Para configurar e compilar o projeto, siga os seguintes passos:
3.1. Instalação de Dependências
•	Baixe e instale o VSCode (Visual Studio Code).
•	Instale as extensões para C e C++ no VSCode.
•	Instale o compilador GCC (via MinGW-w64 para Windows).
•	Instale o SQLite3.
•	Coloque o cabeçalho SQLite3.h no caminho C:\msys64\ucrt64\include\SQLite3.h.
3.2. Estrutura do Projeto
1.	Pasta de Projeto:
o	Crie uma pasta em C:\DEV.
o	Coloque nesta pasta:
	Códigos-fonte .c
	Executáveis .exe
	Banco de Dados .db
2.	Banco de Dados:
o	O banco de dados principal é hortifruti.db.
o	Ele contém as tabelas Cliente, Fornecedor, Produto, Estoque, e Venda com suas estruturas definidas.
3.3. Compilação e Execução
Para compilar o programa Cadprod.c e gerar o executável, utilize o seguinte comando:
bash
Copiar código
gcc Cadprod.c -o Cadprod -IC:\sqlite -LC:\sqlite -lsqlite3
3.4. Inicializando o Banco de Dados
Para acessar e manipular o banco de dados em linha de comando, utilize:
bash
Copiar código
cd C:\DEV
sqlite3 hortifruti.db
4. Estrutura de Dados do Banco
Tabelas e Estruturas
As tabelas foram criadas para armazenar informações de produtos, estoque, clientes e vendas. Abaixo, exemplos de comandos SQL usados para criar e manipular dados nas tabelas:
•	Clientes: Cadastro de clientes com dados essenciais.
sql
Copiar código
CREATE TABLE Cliente (
    CliID INTEGER PRIMARY KEY,
    CliNome TEXT NOT NULL,
    CliCPF TEXT NOT NULL,
    CliEnd TEXT NOT NULL
);
•	Produtos: Registro de produtos, quantidades e tipo (fruta, legume, etc).
sql
Copiar código
CREATE TABLE Produto (
    ProdID INTEGER PRIMARY KEY,
    ProdNome TEXT NOT NULL,
    ProdQuant INTEGER,
    ProdTipo TEXT NOT NULL
);
•	Estoque: Movimentação de entrada e saída de produtos.
sql
Copiar código
CREATE TABLE Estoque (
    EstID INTEGER PRIMARY KEY,
    ProdID INTEGER,
    EstData DATE,
    EstQtdMov INTEGER
);
5. Código-fonte: Principais Arquivos
1.	ListaCliente.c: Lista todos os clientes do banco.
2.	CadProd02.c: Cadastro de novos produtos no sistema.
3.	BuscaProduto.c: Consulta detalhes de um produto e seu fornecedor.
4.	AtualizaProd.c: Atualização de dados de produtos.
5.	ListaTopVendas.c: Lista produtos com maior número de vendas (menor quantidade em estoque).
Os códigos-fonte possuem comentários para facilitar a compreensão e manipulação.
6. Exemplo de Uso
Cadastro de Produto
Execute Cadprod.exe, informe os dados solicitados (ID, Nome, Quantidade e Tipo do Produto) para cadastrar um novo produto. O sistema verifica se o produto já existe e notifica o usuário.
Consulta de Estoque
Execute ListaTopVendas.exe para listar os 10 produtos com menor estoque, identificando os itens de maior demanda.
7. Colaboradores e Orientações
Para o desenvolvimento do projeto, é necessário trabalhar em grupo, com uma divisão clara das responsabilidades. Consulte o guia de normalização da UNIP para as normas ABNT e entregue o trabalho no sistema acadêmico dentro do prazo.
8. Extensão Universitária
Como atividade adicional, sugerimos que o grupo desenvolva um infográfico explicando a cadeia de produção do hortifruti e uma cartilha nutricional dos produtos.
9. Fontes de Referência
•	Guia de normalização ABNT: UNIP Biblioteca
•	Modelo de negócio Hortifruti: Agro20

