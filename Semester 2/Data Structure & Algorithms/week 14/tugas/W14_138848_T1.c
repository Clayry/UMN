#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KOTA 26
#define INF 1e9

int charToIndex(char c) { return c - 'a'; }

char indexToChar(int i) { return i + 'a'; }
void dijkstra(int graph[MAX_KOTA][MAX_KOTA], int asal, int tujuan,
              bool kotaAktif[MAX_KOTA]) {
  int jarak[MAX_KOTA];
  bool dikunjungi[MAX_KOTA];
  int parent[MAX_KOTA];

  for (int i = 0; i < MAX_KOTA; i++) {
    jarak[i] = INF;
    dikunjungi[i] = false;
    parent[i] = -1;
  }

  jarak[asal] = 0;

  for (int count = 0; count < MAX_KOTA - 1; count++) {
    int minJarak = INF;
    int u = -1;

    for (int v = 0; v < MAX_KOTA; v++) {
      if (!dikunjungi[v] && jarak[v] < minJarak && kotaAktif[v]) {
        minJarak = jarak[v];
        u = v;
      }
    }

    if (u == -1)
      break;

    dikunjungi[u] = true;

    if (u == tujuan)
      break;

    for (int v = 0; v < MAX_KOTA; v++) {
      if (!dikunjungi[v] && graph[u][v] && jarak[u] != INF &&
          jarak[u] + graph[u][v] < jarak[v] && kotaAktif[v]) {
        jarak[v] = jarak[u] + graph[u][v];
        parent[v] = u;
      }
    }
  }

  if (jarak[tujuan] == INF) {
    printf("\nTidak ada rute dari kota '%c' ke kota '%c'.\n", indexToChar(asal),
           indexToChar(tujuan));
  } else {
    printf("\njarak minimun dari '%c' ke '%c' adalah: %d\n", indexToChar(asal),
           indexToChar(tujuan), jarak[tujuan]);
  }
}

int main() {
  int graph[MAX_KOTA][MAX_KOTA] = {0};
  bool kotaAktif[MAX_KOTA] = {false};

  char src, dest;
  int weight;

  while (1) {
    printf("Input rute: ");

    if (scanf(" %c#%c#%d", &src, &dest, &weight) != 3) {
      printf("Format salah! Gunakan format S#D#W\n");
      while (getchar() != '\n')
        ;
      continue;
    }

    if (src == '-' && dest == '-' && weight == -1) {
      break;
    }

    if (src < 'a' || src > 'z' || dest < 'a' || dest > 'z') {
      printf("Error: Kota harus berupa huruf kecil a-z\n");
      continue;
    }

    int u = charToIndex(src);
    int v = charToIndex(dest);

    graph[u][v] = weight;
    graph[v][u] = weight;

    kotaAktif[u] = true;
    kotaAktif[v] = true;
  }

  char asal, tujuan;
  printf("\n=== Cari jarak Minimum ===\n");
  printf("Masukkan Kota Asal: ");
  scanf(" %c", &asal);
  printf("Masukkan Kota Tujuan: ");
  scanf(" %c", &tujuan);

  if (asal < 'a' || asal > 'z' || tujuan < 'a' || tujuan > 'z') {
    printf("Error: Input kota tidak valid.\n");
    return 1;
  }

  int idxAsal = charToIndex(asal);
  int idxTujuan = charToIndex(tujuan);

  if (!kotaAktif[idxAsal] || !kotaAktif[idxTujuan]) {
    printf("Error: Kota asal tujuan tidak terdaftar dalam rute yang diinput\n");
  } else {
    dijkstra(graph, idxAsal, idxTujuan, kotaAktif);
  }

  return 0;
}