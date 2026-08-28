#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char title[64];
    char director[64];
    int releaseDate;
    int duration;
    float rating;
} Movie;

void trimNewLine(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void printMovie(int index, Movie m) {
    printf("%d. %s - %s (%d) [%d menit] rating: %.1f\n", index + 1, m.title, m.director, m.releaseDate, m.duration, m.rating);
}

void saveMovies(Movie movies[], int total) {
    FILE *fp = fopen("film.txt", "w");
    if (fp == NULL) return;
    for (int i = 0; i < total; i++) {
        fprintf(fp, "%s#%s#%d#%d#%.1f\n", movies[i].title, movies[i].director, movies[i].releaseDate, movies[i].duration, movies[i].rating);
    }
    fclose(fp);
}

int loadMovies(Movie movies[]) {
    FILE *fp = fopen("film.txt", "r");
    if (fp == NULL) return 0;

    int i = 0;
    while (i < 20 && fscanf(fp, " %[^#]#%[^#]#%d#%d#%f\n", movies[i].title, movies[i].director, &movies[i].releaseDate, &movies[i].duration, &movies[i].rating) == 5) {
        i++;
    }
    fclose(fp);
    return i;
}

int displayFilm() {
    Movie movies[20];
    int total = loadMovies(movies);
    if (total == 0) {
        printf("Database empty or file not found.\n");
        return 0;
    }
    for (int i = 0; i < total; i++) {
        printMovie(i, movies[i]);
    }
    return 1;
}

int addFilm() {
    Movie newMovie;
    getchar();

    printf("Film Title    : ");
    fgets(newMovie.title, sizeof(newMovie.title), stdin);
    trimNewLine(newMovie.title);

    printf("Film Director : ");
    fgets(newMovie.director, sizeof(newMovie.director), stdin);
    trimNewLine(newMovie.director);

    printf("Release Year  : ");
    scanf("%d", &newMovie.releaseDate);
    printf("Duration (min): ");
    scanf("%d", &newMovie.duration);
    printf("Rating (0-10) : ");
    scanf("%f", &newMovie.rating);

    FILE *fp = fopen("film.txt", "a");
    if (fp == NULL) return 0;
    fprintf(fp, "%s#%s#%d#%d#%.1f\n", newMovie.title, newMovie.director, newMovie.releaseDate, newMovie.duration, newMovie.rating);
    fclose(fp);
    printf("Film added successfully!\n");
    return 1;
}

int searchByYear() {
    int year;
    printf("Enter release year to search: ");
    scanf("%d", &year);

    Movie movies[20];
    int total = loadMovies(movies);
    int found = 0;

    printf("\n==== Film Released in %d ====\n", year);
    for (int i = 0; i < total; i++) {
        if (movies[i].releaseDate == year) {
            printMovie(i, movies[i]);
            found++;
        }
    }
    if (found == 0) printf("No movies found for year %d.\n", year);
    return found;
}

int updateRating() {
    Movie movies[20];
    int total = loadMovies(movies);

    if (total == 0) {
        printf("No movies available to update.\n");
        return 0;
    }

    displayFilm();
    int index;
    printf("Select film number to update (1-%d): ", total);
    scanf("%d", &index);
    index--; 

    if (index < 0 || index >= total) {
        printf("Invalid selection.\n");
        return 0;
    }

    printf("Current Rating: %.1f\nNew Rating (0-10): ", movies[index].rating);
    scanf("%f", &movies[index].rating);
    
    saveMovies(movies, total);
    printf("Rating updated!\n");
    return 1;
}

void displayMenu() {
    printf("\n==== Database Film ====\n");
    printf("1. Tampilkan Film\n2. Tambah Film\n3. Cari Film by Tahun\n4. Update Rating\n5. Keluar\nPilih: ");
}

int main() {
    int choice;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1: displayFilm(); break;
            case 2: addFilm(); break;
            case 3: searchByYear(); break;
            case 4: updateRating(); break;
        }
    } while (choice != 5);
    return 0;
}