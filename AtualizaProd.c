#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int busca_produto(sqlite3 *db, const char *nome, int *id, char *tipo, int *quantidade, char *vProdNome) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ProdID, ProdQuant, ProdTipo, ProdNome FROM Produto WHERE ProdNome = ?";
    int encontrado = 0;

    // Prepara a consulta SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_STATIC); // Vincula o nome do produto

        // Executa a consulta e verifica se encontrou resultados
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            *id = sqlite3_column_int(stmt, 0);
            *quantidade = sqlite3_column_int(stmt, 1);
            strcpy(tipo, (const char *)sqlite3_column_text(stmt, 2));
            strcpy(vProdNome, (const char *)sqlite3_column_text(stmt, 3));
            encontrado = 1;
        }
    } else {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt); // Finaliza a consulta
    return encontrado;
}

int atualiza_produto(sqlite3 *db, int id, const char *novoNome, int novaQuantidade, const char *novoTipo) {
    const char *sql = "UPDATE Produto SET ProdNome = ?, ProdQuant = ?, ProdTipo = ? WHERE ProdID = ?";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a atualização: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, novoNome, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, novaQuantidade);
    sqlite3_bind_text(stmt, 3, novoTipo, -1, SQLITE_STATIC);
    //sqlite3_bind_text(stmt, 4, novavProdNome, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt); // Finaliza a instrução de atualização

    if (rc == SQLITE_DONE) {
        return 1;
    } else {
        fprintf(stderr, "Erro ao atualizar o produto: %s\n", sqlite3_errmsg(db));
        return 0;
    }
}

int main() {
    sqlite3 *db;
    char nome[100], novoNome[100], tipo[50], novoTipo[50], vProdNome[50], novavProdNome[50];
    int quantidade, novaQuantidade, id;

    // Conecta ao banco de dados
    if (sqlite3_open("hortifruti.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Solicita o nome do produto ao usuário
    printf("Digite o nome do produto a ser buscado: ");
    scanf(" %[^\n]", nome); // Lê o nome do produto com espaços

    // Busca o produto no banco de dados
    if (busca_produto(db, nome, &id, tipo, &quantidade, vProdNome)) {
        // Exibe os dados atuais do produto
        printf("Produto encontrado:\n");
        printf("Nome atual: %s\n", nome);
        printf("Quantidade atual: %d\n", quantidade);
        printf("Tipo atual: %s\n", tipo);
        //printf("Data de Cadastro atual: %s\n", vProdNome);

        // Solicita novos valores para atualizar
        printf("\nDigite os novos valores para o produto:\n");

        printf("Novo nome (ou o mesmo): ");
        scanf(" %[^\n]", novoNome);

        printf("Nova quantidade: ");
        scanf("%d", &novaQuantidade);

        printf("Novo tipo: ");
        scanf(" %[^\n]", novoTipo);

        //printf("Nova data de cadastro (AAAA-MM-DD): ");
        //scanf(" %[^\n]", novavProdNome);

        // Atualiza o produto no banco de dados
        if (atualiza_produto(db, id, novoNome, novaQuantidade, novoTipo)) {
            printf("Produto atualizado com sucesso.\n");
            // Busca o produto no banco de dados
            
        } else {
            printf("Erro ao atualizar o produto.\n");
        }
    } else {
        printf("Produto não encontrado.\n");
    }

    // Fecha a conexão com o banco de dados
    sqlite3_close(db);
    return 0;
}
