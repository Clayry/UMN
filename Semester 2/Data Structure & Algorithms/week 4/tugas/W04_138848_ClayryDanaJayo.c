#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int nim;
    char nama[50];
    float ipk;
    struct Node* next;
} Node;

Node* head = NULL;

Node* buatNode(int nim, char nama[], float ipk) {
    Node* baru = (Node*)malloc(sizeof(Node));
    baru->nim = nim;
    strcpy(baru->nama, nama);
    baru->ipk = ipk;
    baru->next = NULL;
    return baru;
}

void insertBelakang() {
    int nim;
    char nama[50];
    float ipk;

    printf("\n=== Insert Data Mahasiswa ===\n");
    printf("NIM    : ");
    scanf("%d", &nim);
    printf("Nama   : ");
    getchar();
    fgets(nama, 50, stdin);
    nama[strcspn(nama, "\n")] = '\0';
    printf("IPK    : ");
    scanf("%f", &ipk);

    Node* baru = buatNode(nim, nama, ipk);

    if (head == NULL) {
        head = baru;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }
    printf("Data berhasil ditambahkan!\n");
}

// 2. Print linked list
void printLinkedList() {
    printf("\n=== Data Mahasiswa ===\n");
    if (head == NULL) {
        printf("Linked list kosong.\n");
        return;
    }

    Node* temp = head;
    int no = 1;
    printf("%-4s %-12s %-30s %-6s\n", "No", "NIM", "Nama", "IPK");
    printf("----------------------------------------------------------\n");
    while (temp != NULL) {
        printf("%-4d %-12d %-30s %-6.2f\n", no++, temp->nim, temp->nama, temp->ipk);
        temp = temp->next;
    }
}

void deleteAll() {
    if (head == NULL) {
        printf("Linked list sudah kosong.\n");
        return;
    }
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Semua data berhasil dihapus!\n");
}

void deleteFirst() {
    if (head == NULL) {
        printf("Linked list kosong, tidak ada data yang dihapus.\n");
        return;
    }
    Node* temp = head;
    head = head->next;
    printf("Data dengan NIM %d (%s) berhasil dihapus!\n", temp->nim, temp->nama);
    free(temp);
}

void deleteByNim() {
    if (head == NULL) {
        printf("Linked list kosong.\n");
        return;
    }

    int nim;
    printf("\nMasukkan NIM yang akan dihapus: ");
    scanf("%d", &nim);

    if (head->nim == nim) {
        Node* temp = head;
        head = head->next;
        printf("Data dengan NIM %d (%s) berhasil dihapus!\n", temp->nim, temp->nama);
        free(temp);
        return;
    }

    Node* prev = head;
    Node* curr = head->next;
    while (curr != NULL) {
        if (curr->nim == nim) {
            prev->next = curr->next;
            printf("Data dengan NIM %d (%s) berhasil dihapus!\n", curr->nim, curr->nama);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Data dengan NIM %d tidak ditemukan.\n", nim);
}


int main() {
    int pilihan;

    do {
        printf("\n=============================\n");
        printf("   MENU LINKED LIST MAHASISWA\n");
        printf("=============================\n");
        printf("1. Insert New Node\n");
        printf("2. Print Linked List\n");
        printf("3. Delete All Data\n");
        printf("4. Delete First Data\n");
        printf("5. Delete Data by NIM\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: insertBelakang();   break;
            case 2: printLinkedList();  break;
            case 3: deleteAll();        break;
            case 4: deleteFirst();      break;
            case 5: deleteByNim();      break;
            case 0: printf("Program selesai.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);

    return 0;
}