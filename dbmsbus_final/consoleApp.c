#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sqlda.h>
#include <pgtypes_date.h>
#include <pgtypes_numeric.h>
void updateQuery(PGconn *conn, char str[]) {
    PGresult * q;
    int rec_count;
    q = PQexec(conn, str);
    if (PQresultStatus(q) != PGRES_COMMAND_OK) {
      puts("sorry your query result has failed!");
    } else puts("query successfully executed");
  }
void executeQuery(PGconn * conn, char str[]) {
  PGresult * q;
  int rec_count;
  q = PQexec(conn, str);
  if (PQresultStatus(q) != PGRES_TUPLES_OK) {
    puts("there is no data regarding this query!");
  }
  //rec_count = PQntuples(q);
  int rows = PQntuples(q);
  int cols = PQnfields(q);
  int row;
  int col;
  printf("We received %d records.\n", rows);
  puts("==========================");
  for (row = 0; row < rows; row++) {
    for (col = 0; col < cols; col++) {
      printf("%s\t", PQgetvalue(q, row, col));
    }
    puts("");
  }
}
int main() {
  PGconn *conn;
  PGresult *res;
  int rec_count;
  int row;
  int col;
  conn = PQconnectdb("hostaddr=10.100.71.21 user=201601224 port=5432 dbname=201601224 password=201601224");
  if (PQstatus(conn) == CONNECTION_BAD) {
    puts("We were unable to connect to the database"); exit(0);
  }
  res = PQexec(conn,"set search_path to mylinkedin;");
  char query[300];
  scanf("%[^\n]s", query);
  int i;
  if (query[0] == 'S' || query[0] == 's')
    executeQuery(conn, query);
  else
    updateQuery(conn, query);
  PQclear(res);
  PQfinish(conn);
  return 0;
}
