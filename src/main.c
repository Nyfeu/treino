
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sqlite3.h"

#define MAX_STRING_READ 20

void getConnection(const char* db_path, sqlite3** db);
void closeConnection(sqlite3* db);

typedef unsigned int uint;

typedef enum {

  SAIR = 0,
  PRECIPITACAO_MEDIA,
  TEMPERATURA_MAX,
  TEMPERATURA_MIN,
  TEMPERATUrA_MED

} option;

option menu();

uint read_uint();
void read_string(char *buffer);

int main() {

  sqlite3* db;

  getConnection("Tempo.db", &db);

  closeConnection(db);

  return 0;
}

option menu() {

  printf(
    "Informe a opcao desejada: \n"
    "1 - Consultar a precipitacao media no periodo \n"
    "2 - Consultar os dias com a temperatura maxima no periodo \n"
    "3 - Consultar os dias com a temperatura minima no periodo \n"
    "4 - Consultar a temperatura media no periodo \n"
    "0 - Sair do Sistema \n"
  );

  uint opt;

  do {

    printf("Digite a opcao: ");
    opt = read_uint();

  } while (opt < 0 || opt > 4);

  return opt;

}

float read_float() {

  char buffer[MAX_STRING_READ];
  read_string(buffer);
  return strtof(buffer, NULL);

}

uint read_uint() {

  char buffer[MAX_STRING_READ];
  read_string(buffer);
  return strtol(buffer, NULL, 10);

}

void read_string(char *buffer) {

  if (fgets(buffer, MAX_STRING_READ, stdin) != NULL) {

    size_t len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';

  }

}

void getConnection(const char* db_path, sqlite3** db) {

  printf("Conectando-se ao banco de dados...\n");

  if (sqlite3_open(db_path, db) != SQLITE_OK) {

    printf("Erro na conexao... %s\n\n", sqlite3_errmsg(*db));
    exit(-1);

  }

  printf("Conexao estabelecida com sucesso!");

}
void closeConnection(sqlite3* db) {

  printf("Finalizando conexao com o banco de dados...\n");

  if (sqlite3_close(db) != SQLITE_OK) {

    printf("Erro no fechamento da conexao... %s\n\n", sqlite3_errmsg(db));
    exit(-1);

  }

  printf("Conexao finalizada com sucesso!");

}
