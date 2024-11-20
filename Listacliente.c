#include <stdio.h>
#include <sqlite3.h>

// Função callback para processar cada linha do resultado da consulta
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    // Definir variaveis
    
    sqlite3 *db;
    char *err_msg = 0;

    // Abre o banco de dados
    int rc = sqlite3_open("hortifruti.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // Consulta SQL para listar todos os dados da tabela Cliente
    char *sql = "SELECT * FROM Cliente";

    // Executa a consulta
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao listar dados: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Dados da tabela Cliente listados com sucesso.\n");
    }

    // Fecha o banco de dados
    sqlite3_close(db);

    return 0;
}
