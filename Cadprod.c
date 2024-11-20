#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

// Função callback para processar cada linha do resultado da consulta
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    //Analisar resultado da consulta
    //Inserir dados caso não exista produto
    return 0;
}

int main() {
    // Definir variaveis
    
    sqlite3 *db;
    char *err_msg = 0;
    int vProdID = 0;
    char vProdNome[50];
    int vProdQuant = 0;
    char *vSQL = 0;

    //Solicitar dados produto
    printf("\n********************* Digite o produto ***********************\n");
    printf("\nDigite o código do produto:\n");
    scanf("%d",&vProdID);
    printf("\nDigite o nome do produto:\n");
    scanf("%49s",vProdNome);
    printf("\nDigite a quantidade do produto:\n");
    scanf("%d",&vProdQuant);
    printf("\n********************* Obrigado ***********************\n");

    printf("String: %s\n", vProdNome);
    printf("\n");

    // Abre o banco de dados
    int rc = sqlite3_open("hortifruti.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // Consulta SQL para listar todos os dados da tabela Cliente
    char *sql = "SELECT * FROM Produto";// WHERE ProdNome = '";
    //Beterraba'";
    strcat(sql, vProdNome);
    //strcat(sql, "'");
    //char vsql = *sql;
    
    //printf("Copied sql: %s\n", vSQL);
    fprintf(stderr, "String: %s\n", sql);
    strcpy(vSQL, sql);
    //fprintf(stderr, "String: %s\n", vSQL);
    printf("\n");

    // Executa a consulta
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao listar dados: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Dados da tabela Cliente listados com sucesso.\n");
    }
    //O que ele listou

    // Fecha o banco de dados
    sqlite3_close(db);

    return 0;
}
