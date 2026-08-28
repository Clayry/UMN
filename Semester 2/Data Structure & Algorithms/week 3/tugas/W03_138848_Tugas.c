#include <stdio.h>
#include <string.h>


typedef struct {
    char nim[20];
    char nama[50];
    char jurusan[50];
} Mahasiswa;

typedef struct {
    char nim[20];
    float tugas;
    float uts;
    float uas;
    float nilaiAkhir;
    char grade[3];
} Nilai;


void hitungGrade(float nilaiAkhir, char *grade) {
    if (nilaiAkhir >= 95)
        strcpy(grade, "A+");
    else if (nilaiAkhir >= 85)
        strcpy(grade, "A");
    else if (nilaiAkhir >= 80)
        strcpy(grade, "A-");
    else if (nilaiAkhir >= 75)
        strcpy(grade, "B+");
    else if (nilaiAkhir >= 70)
        strcpy(grade, "B");
    else if (nilaiAkhir >= 65)
        strcpy(grade, "C");
    else if (nilaiAkhir >= 60)
        strcpy(grade, "C-");
    else if (nilaiAkhir >= 55)
        strcpy(grade, "D");
    else
        strcpy(grade, "E");
}


int bacaDataMahasiswa(Mahasiswa mhs[], int max) {
    FILE *fp = fopen("dataMahasiswa.txt", "r");
    if (fp == NULL) {
        printf("File dataMahasiswa.txt tidak ditemukan.\n");
        return 0;
    }
    int i = 0;
    while (!feof(fp) && i < max) {
        int result = fscanf(fp, "%[^#]#%[^#]#%[^\n]\n",
                            mhs[i].nim, mhs[i].nama, mhs[i].jurusan);
        if (result == 3) i++;
        else break;
    }
    fclose(fp);
    return i;
}

int bacaNilaiMahasiswa(Nilai nilai[], int max) {
    FILE *fp = fopen("nilaiMahasiswa.txt", "r");
    if (fp == NULL) {
        printf("File nilaiMahasiswa.txt tidak ditemukan.\n");
        return 0;
    }
    int i = 0;
    while (!feof(fp) && i < max) {
        int result = fscanf(fp, "%[^#]#%f#%f#%f#%f#%[^\n]\n",
                            nilai[i].nim, &nilai[i].tugas, &nilai[i].uts,
                            &nilai[i].uas, &nilai[i].nilaiAkhir, nilai[i].grade);
        if (result == 6) i++;
        else break;
    }
    fclose(fp);
    return i;
}


void tampilkanMahasiswa(Mahasiswa mhs[], int n) {
    printf("\n===== DATA MAHASISWA =====\n");
    printf("%-15s %-30s %-20s\n", "NIM", "Nama", "Jurusan");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-15s %-30s %-20s\n", mhs[i].nim, mhs[i].nama, mhs[i].jurusan);
    }
}

void tampilkanNilai(Nilai nilai[], int n) {
    printf("\n===== NILAI MAHASISWA =====\n");
    printf("%-15s %-8s %-8s %-8s %-12s %-5s\n",
           "NIM", "Tugas", "UTS", "UAS", "Nilai Akhir", "Grade");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-15s %-8.2f %-8.2f %-8.2f %-12.2f %-5s\n",
               nilai[i].nim, nilai[i].tugas, nilai[i].uts,
               nilai[i].uas, nilai[i].nilaiAkhir, nilai[i].grade);
    }
}


void tambahMahasiswa(Mahasiswa mhs[], int *n) {
    if (*n >= 100) {
        printf("Data mahasiswa sudah penuh!\n");
        return;
    }
    Mahasiswa baru;
    printf("\nMasukkan NIM     : ");
    scanf(" %[^\n]", baru.nim);
    printf("Masukkan Nama    : ");
    scanf(" %[^\n]", baru.nama);
    printf("Masukkan Jurusan : ");
    scanf(" %[^\n]", baru.jurusan);

    mhs[*n] = baru;
    (*n)++;

    // Append to file
    FILE *fp = fopen("dataMahasiswa.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s#%s#%s\n", baru.nim, baru.nama, baru.jurusan);
        fclose(fp);
        printf("Data mahasiswa berhasil disimpan.\n");
    }
}

void tambahNilai(Nilai nilai[], int *n) {
    if (*n >= 100) {
        printf("Data nilai sudah penuh!\n");
        return;
    }
    Nilai baru;
    printf("\nMasukkan NIM   : ");
    scanf(" %[^\n]", baru.nim);
    printf("Masukkan Tugas : ");
    scanf("%f", &baru.tugas);
    printf("Masukkan UTS   : ");
    scanf("%f", &baru.uts);
    printf("Masukkan UAS   : ");
    scanf("%f", &baru.uas);

    
    baru.nilaiAkhir = (baru.tugas * 0.30f) + (baru.uts * 0.30f) + (baru.uas * 0.40f);
    hitungGrade(baru.nilaiAkhir, baru.grade);

    nilai[*n] = baru;
    (*n)++;


    FILE *fp = fopen("nilaiMahasiswa.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s#%.2f#%.2f#%.2f#%.2f#%s\n",
                baru.nim, baru.tugas, baru.uts, baru.uas,
                baru.nilaiAkhir, baru.grade);
        fclose(fp);
        printf("Nilai akhir: %.2f | Grade: %s\n", baru.nilaiAkhir, baru.grade);
        printf("Data nilai berhasil disimpan.\n");
    }
}


int main() {
    Mahasiswa dataMhs[100];
    Nilai dataNilai[100];
    int jumlahMhs = 0;
    int jumlahNilai = 0;

    jumlahMhs   = bacaDataMahasiswa(dataMhs, 100);
    jumlahNilai = bacaNilaiMahasiswa(dataNilai, 100);

    int pilihan;
    do {
        printf("\n========== MENU ==========\n");
        printf("1. Tampilkan Data Mahasiswa\n");
        printf("2. Tampilkan Nilai Mahasiswa\n");
        printf("3. Tambah Data Mahasiswa\n");
        printf("4. Tambah Nilai Mahasiswa\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tampilkanMahasiswa(dataMhs, jumlahMhs);
                break;
            case 2:
                tampilkanNilai(dataNilai, jumlahNilai);
                break;
            case 3:
                tambahMahasiswa(dataMhs, &jumlahMhs);
                break;
            case 4:
                tambahNilai(dataNilai, &jumlahNilai);
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);

    return 0;
}