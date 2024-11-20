#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int verifica_produto(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM Produto WHERE ProdID = ?";
    int existe = 0;

    // Prepara a consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id); // Vincula o ID à consulta

        // Executa a consulta
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            existe = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt); // Finaliza a consulta
    return existe;
}

int insere_produto(sqlite3 *db, int id, const char *nome, int quantidade, const char *tipo) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Produto (ProdID, ProdNome, ProdQuant, ProdTipo) VALUES (?, ?, ?, ?)";

    // Prepara a instrução SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Vincula os valores de ID, Nome, Quantidade e Tipo
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, nome, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, quantidade);
    sqlite3_bind_text(stmt, 4, tipo, -1, SQLITE_STATIC);

    // Executa a inserção
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Erro ao inserir dados: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt); // Finaliza a inserção
    return 1;
}

int main() {
    sqlite3 *db;
    int id, quantidade;
    char nome[100], tipo[50];
    int resultado;

    // Conecta ao banco de dados ou cria um novo banco de dados
    if (sqlite3_open("hortifruti.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Cria a tabela Produtos se ela não existir
    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS Produto ("
                                   "ProdID INTEGER PRIMARY KEY, "
                                   "ProdNome TEXT NOT NULL, "
                                   "ProdQuant INTEGER, "
                                   "ProdTipo TEXT NOT NULL);";
    if (sqlite3_exec(db, sql_create_table, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar a tabela: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Solicita ao usuário os dados do produto
    printf("Digite o ID do produto: ");
    scanf("%d", &id);

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", nome);

    printf("Digite a quantidade do produto: ");
    scanf("%d", &quantidade);

    printf("Digite o tipo do produto: ");
    scanf(" %[^\n]", tipo);

    // Verifica se o produto já existe
    if (verifica_produto(db, id)) {
        printf("Produto com ID %d já existe.\n", id);
    } else {
        // Insere o produto no banco de dados
        resultado = insere_produto(db, id, nome, quantidade, tipo);
        if (resultado) {
            printf("Produto inserido com sucesso!\n");
        } else {
            printf("Erro ao inserir o produto.\n");
        }
    }

    // Fecha a conexão com o banco de dados
    sqlite3_close(db);
    return 0;
}
