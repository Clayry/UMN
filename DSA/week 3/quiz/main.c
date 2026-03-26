#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char title[64];
    char director[64];
    int releaseDate;
    int duration;
    float rating;
}Movie;
void trimNewLine(char *str){
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n'){
        str[len - 1] = '\0';
    }
}
int displayFilm(){
    int i=0;
    Movie movies[20];
    FILE *fp = fopen("film.txt", "r");

    if (fp == NULL)
    {
        printf("error");
        return 0;
    }
    
    while (i<20 && !feof(fp))
    {
        Movie newMovie;
        fscanf(fp, "%[^#]#%[^#]#%d#%d#%f\n", newMovie.title, newMovie.director, &newMovie.releaseDate, &newMovie.duration, &newMovie.rating);
        movies[i] = newMovie;
        i++;
    }
    fclose(fp);
    int total = i;
    for ( i = 0; i < total; i++)
    {
        printf("%d. %s - %s (%d) [%d menit] rating: %.1f \n", i+1, movies[i].title, movies[i].director, movies[i].releaseDate, movies[i].duration, movies[i].rating);
    }
    return 1;
}

int addFilm(){
    Movie newMovie;

    while (getchar() != '\n');

    printf("Film Title    : ");
    fgets(newMovie.title, sizeof(newMovie.title), stdin);
    trimNewline(newMovie.title);

    printf("Film Director : ");
    fgets(newMovie.director, sizeof(newMovie.director), stdin);
    trimNewline(newMovie.director);

    printf("Release Year  : ");
    scanf("%d", &newMovie.releaseDate);

    printf("Duration (min): ");
    scanf("%d", &newMovie.duration);

    printf("Rating (0-10) : ");
    scanf("%f", &newMovie.rating);

    // Validate rating
    if (newMovie.rating < 0) newMovie.rating = 0;
    if (newMovie.rating > 10) newMovie.rating = 10;

    FILE *fp = fopen("film.txt", "a");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return 0;
    }
}

int searchByYear() {
    int year;
    printf("Enter release year to search: ");
    scanf("%d", &year);

    Movie movies[20];
    int total = 20;
    int found = 0;

    printf("\n==== Film Released in %d ====\n", year);
    for (int i = 0; i < total; i++) {
        if (movies[i].releaseDate == year) {
            printMovie(i, movies[i]);
            found++;
        }
    }

    if (found == 0)
        printf("No movies found for year %d.\n", year);
    else
        printf("Found: %d film(s)\n", found);

    printf("\n");
    return found;
}

int updateRating() {
    Movie movies[20];
    int total = 20;

    if (total == 0) {
        printf("No movies available to update.\n");
        return 0;
    }

    printf("\n==== Update Rating Film ====\n");
    for (int i = 0; i < total; i++) {
        printMovie(i, movies[i]);
    }

    int index;
    printf("Select film number to update (1-%d): ", total);
    scanf("%d", &index);
    index--; // Convert to 0-based

    if (index < 0 || index >= total) {
        printf("Invalid selection.\n");
        return 0;
    }

    float newRating;
    printf("Current Rating: %.1f\n", movies[index].rating);
    printf("New Rating (0-10): ");
    scanf("%f", &newRating);

    if (newRating < 0) newRating = 0;
    if (newRating > 10) newRating = 10;

    movies[index].rating = newRating;
    saveMovies(movies, total);

    printf("Rating for \"%s\" updated to %.1f!\n\n", movies[index].title, newRating);
    return 1;
}

void display(){
    printf("==== Database Film ====\n");
    printf("1. Tampilkan Film\n");
    printf("2. Tambah Film\n");
    printf("3. Cari Film by Tahun\n");
    printf("4. Update Rating\n");
    printf("5. keluar\n");
    printf("Pilih: ");
}


int main(){
    int choice;
    do {
        display();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displayFilm();
            break;

        case 2:
            addFilm();
            break;

        case 3:
            searchByYear();
            break;

        case 4:
            updateRating();
            break;

        default:
            break;
        }
    }while(choice != 5);

    return 0;
}