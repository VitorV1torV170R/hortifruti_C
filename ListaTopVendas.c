#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void listar_produtos_com_menor_estoque(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = 
        "SELECT p.ProdNome, SUM(e.EstQtdMov) AS TotalEstoque "
        "FROM Produto p "
        "JOIN estoque e ON p.ProdID = e.ProdID "
        "WHERE EstQtdMov < 0 "
        "GROUP BY p.ProdID "
        "ORDER BY TotalEstoque ASC "
        "LIMIT 10;";

    // Prepara a consulta SQL
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("Produtos com mais vendas:\n");
    printf("%-20s %10s\n", "Produto", "Quantidade");

    // Executa a consulta e exibe os resultados
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *prodNome = (const char *)sqlite3_column_text(stmt, 0);
        int totalEstoque = sqlite3_column_int(stmt, 1);

        printf("%-20s %10d\n", prodNome, totalEstoque);
    }

    // Finaliza a instrução SQL
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;

    // Conecta ao banco de dados
    int rc = sqlite3_open("hortifruti.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Lista os produtos com as menores quantidades totais no estoque
    listar_produtos_com_menor_estoque(db);

    // Fecha a conexão com o banco de dados
    sqlite3_close(db);

    return 0;
}
