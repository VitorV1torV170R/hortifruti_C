#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int busca_produto_e_fornecedor(sqlite3 *db, const char *nome) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT P.ProdID, P.ProdNome, P.ProdQuant, P.ProdTipo, F.ForID, F.ForNome "
                      "FROM Produto P "
                      "JOIN Fornecedor F ON P.ForID = F.ForID "
                      "WHERE P.ProdNome = ?";
    int encontrado = 0;

    // Prepara a consulta SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_STATIC); // Vincula o nome do produto

        // Executa a consulta e verifica se encontrou resultados
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            // Se o produto for encontrado, exibe os dados do produto e do fornecedor
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char *prodNome = sqlite3_column_text(stmt, 1);
            int quantidade = sqlite3_column_int(stmt, 2);
            const unsigned char *tipo = sqlite3_column_text(stmt, 3);
            int forID = sqlite3_column_int(stmt, 4);
            const unsigned char *forNome = sqlite3_column_text(stmt, 5);

            printf("Produto encontrado:\n");
            printf("ID do Produto: %d\n", id);
            printf("Nome do Produto: %s\n", prodNome);
            printf("Quantidade: %d\n", quantidade);
            printf("Tipo: %s\n", tipo);
            printf("Fornecedor:\n");
            printf("  ID do Fornecedor: %d\n", forID);
            printf("  Nome do Fornecedor: %s\n", forNome);

            encontrado = 1; // Marca como encontrado
        }
    } else {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt); // Finaliza a consulta
    return encontrado;
}

int main() {
    sqlite3 *db;
    char nome[100];

    // Conecta ao banco de dados ou cria um novo banco de dados
    if (sqlite3_open("hortifruti.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Solicita o nome do produto ao usuário
    printf("Digite o nome do produto a ser buscado: ");
    scanf(" %[^\n]", nome); // Lê o nome do produto, incluindo espaços

    // Busca o produto no banco de dados
    if (!busca_produto_e_fornecedor(db, nome)) {
        printf("Produto não encontrado.\n");
    }

    // Fecha a conexão com o banco de dados
    sqlite3_close(db);
    return 0;
}
