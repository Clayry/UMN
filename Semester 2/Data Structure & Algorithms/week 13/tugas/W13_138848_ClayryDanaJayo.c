#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nim[15];
    char nama[50];
    float nilaiTugas;
    float nilaiUTS;
    float nilaiUAS;
    float nilaiAkhir;
} Mahasiswa;

void urutkanMahasiswa(Mahasiswa mhs[], int jumlah) {
    Mahasiswa temp;
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (strcmp(mhs[j].nim, mhs[j + 1].nim) > 0) {
                temp = mhs[j];
                mhs[j] = mhs[j + 1];
                mhs[j + 1] = temp;
            }
        }
    }
}

void tampilkanTabel(Mahasiswa mhs[], int jumlah) {
    printf("\n==================================================\n");
    printf("%-3s | %-15s | %-25s\n", "No", "NIM", "Nama Mahasiswa");
    printf("==================================================\n");
    for (int i = 0; i < jumlah; i++) {
        printf("%-3d | %-15s | %-25s\n", i + 1, mhs[i].nim, mhs[i].nama);
    }
    printf("==================================================\n");
}

void showStudentDetail(Mahasiswa mhs[], int jumlah) {
    if (jumlah == 0) {
        printf("\n[Sistem] Belum ada data mahasiswa.\n");
        return;
    }

    urutkanMahasiswa(mhs, jumlah);

    printf("\n--- DAFTAR MAHASISWA (ASCENDING BY NIM) ---\n");
    tampilkanTabel(mhs, jumlah);

    char cariNIM[15];
    printf("Masukkan NIM Mahasiswa yang ingin dilihat detailnya: ");
    scanf("%s", cariNIM);

    int ditemukan = -1;
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(mhs[i].nim, cariNIM) == 0) {
            ditemukan = i;
            break;
        }
    }

    if (ditemukan != -1) {
        printf("\n==================================================\n");
        printf("                DETAIL DATA MAHASISWA             \n");
        printf("==================================================\n");
        printf("NIM          : %s\n", mhs[ditemukan].nim);
        printf("Nama         : %s\n", mhs[ditemukan].nama);
        printf("Nilai Tugas  : %.2f\n", mhs[ditemukan].nilaiTugas);
        printf("Nilai UTS    : %.2f\n", mhs[ditemukan].nilaiUTS);
        printf("Nilai UAS    : %.2f\n", mhs[ditemukan].nilaiUAS);
        printf("Nilai Akhir  : %.2f\n", mhs[ditemukan].nilaiAkhir);
        printf("==================================================\n");
    } else {
        printf("\n[Sistem] NIM '%s' tidak ditemukan.\n", cariNIM);
    }
}

int main() {
    Mahasiswa listMhs[100] = {
        {"2301928341", "Budi Santoso", 80, 75, 85, 80.5},
        {"2301432109", "Andi Wijaya", 90, 85, 88, 87.7},
        {"2301556677", "Citra Lestari", 75, 80, 70, 74.5}};
    int jumlahMhs = 3;
    int pilihan;

    do {
        printf("\n=== APLIKASI DATA MAHASISWA ===\n");
        printf("1. Input Data Student\n");
        printf("2. Show All Students\n");
        printf("3. Update Student\n");
        printf("4. Show student detail\n");
        printf("5. Exit\n");
        printf("Pilih menu (1-5): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
        case 1:
            printf("\n[Menu 1] Fitur input data...\n");
            break;
        case 2:
            printf("\n[Menu 2] Fitur show all...\n");
            break;
        case 3:
            printf("\n[Menu 3] Fitur update...\n");
            break;
        case 4:
            showStudentDetail(listMhs, jumlahMhs);
            break;
        case 5:
            printf("\nTerima kasih! Keluar dari program.\n");
            break;
        default:
            printf("\nPilihan tidak valid! Silakan coba lagi.\n");
        }
    } while (pilihan != 5);

    return 0;
}
