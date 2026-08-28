#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    char username[100];
    char nickname[100];
    char hero[100];
    int matches;
    int winrate;
    struct Player *next;
    struct Player *prev;
} Player;

Player *createPlayer(char *username, char *nickname, char *hero, int matches,
                     int winrate) {
    Player *p = (Player *)malloc(sizeof(Player));
    if (!p)
        return NULL;
    strcpy(p->username, username);
    strcpy(p->nickname, nickname);
    strcpy(p->hero, hero);
    p->matches = matches;
    p->winrate = winrate;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

Player *copyList(Player *head) {
    if (head == NULL)
        return NULL;

    Player *newHead = createPlayer(head->username, head->nickname, head->hero,
                                   head->matches, head->winrate);
    Player *currOriginal = head->next;
    Player *currCopy = newHead;

    while (currOriginal != NULL) {
        Player *newNode = createPlayer(
            currOriginal->username, currOriginal->nickname, currOriginal->hero,
            currOriginal->matches, currOriginal->winrate);
        currCopy->next = newNode;
        newNode->prev = currCopy;

        currCopy = newNode;
        currOriginal = currOriginal->next;
    }
    return newHead;
}

void freeList(Player *head) {
    while (head) {
        Player *temp = head;
        head = head->next;
        free(temp);
    }
}

void displayData(Player *p) {
    if (p == NULL) {
        printf("\nNo data available.\n");
        return;
    }
    printf("\n%-20s %-20s %-20s %-10s %-10s\n", "Username", "Nickname", "Hero",
           "Matches", "Winrate");
    printf("-------------------------------------------------------------------"
           "------------------\n");
    while (p != NULL) {
        printf("%-20s %-20s %-20s %-10d %-10d\n", p->username, p->nickname,
               p->hero, p->matches, p->winrate);
        p = p->next;
    }
}

void swapData(Player *a, Player *b) {
    char tempStr[100];
    int tempVal;

    strcpy(tempStr, a->username);
    strcpy(a->username, b->username);
    strcpy(b->username, tempStr);

    strcpy(tempStr, a->nickname);
    strcpy(a->nickname, b->nickname);
    strcpy(b->nickname, tempStr);

    strcpy(tempStr, a->hero);
    strcpy(a->hero, b->hero);
    strcpy(b->hero, tempStr);

    tempVal = a->matches;
    a->matches = b->matches;
    b->matches = tempVal;

    tempVal = a->winrate;
    a->winrate = b->winrate;
    b->winrate = tempVal;
}

Player *merge(Player *first, Player *second) {
    if (!first)
        return second;
    if (!second)
        return first;

    if (strcmp(first->username, second->username) <= 0) {
        first->next = merge(first->next, second);
        if (first->next)
            first->next->prev = first;
        first->prev = NULL;
        return first;
    } else {
        second->next = merge(first, second->next);
        if (second->next)
            second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

Player *split(Player *head) {
    Player *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Player *temp = slow->next;
    slow->next = NULL;
    if (temp)
        temp->prev = NULL;
    return temp;
}

Player *mergeSort(Player *head) {
    if (!head || !head->next)
        return head;
    Player *second = split(head);
    head = mergeSort(head);
    second = mergeSort(second);
    return merge(head, second);
}

void heapify(Player **arr, int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && strcmp(arr[l]->nickname, arr[smallest]->nickname) < 0)
        smallest = l;
    if (r < n && strcmp(arr[r]->nickname, arr[smallest]->nickname) < 0)
        smallest = r;

    if (smallest != i) {
        swapData(arr[i], arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void heapSortNicknameDesc(Player *head, int n) {
    if (n <= 1)
        return;
    Player **arr = (Player **)malloc(sizeof(Player *) * n);
    Player *curr = head;
    for (int i = 0; i < n; i++) {
        arr[i] = curr;
        curr = curr->next;
    }

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swapData(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
    free(arr);
}

Player *getTail(Player *cur) {
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

Player *partition(Player *head, Player *end, Player **newHead,
                  Player **newEnd) {
    Player *pivot = end;
    Player *prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->matches < pivot->matches) {
            if ((*newHead) == NULL)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            Player *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == NULL)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

Player *quickSortRecur(Player *head, Player *end) {
    if (!head || head == end)
        return head;

    Player *newHead = NULL, *newEnd = NULL;
    Player *pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Player *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
        pivot->prev = tmp;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    if (pivot->next)
        pivot->next->prev = pivot;

    return newHead;
}

int binarySearchNickname(Player *head, int n, char *nickname) {
    if (n <= 0)
        return -1;
    Player **arr = (Player **)malloc(sizeof(Player *) * n);
    Player *curr = head;
    for (int i = 0; i < n; i++) {
        arr[i] = curr;
        curr = curr->next;
    }

    int low = 0, high = n - 1;
    int index = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(arr[mid]->nickname, nickname);
        if (cmp == 0) {
            index = mid;
            break;
        }
        if (cmp < 0)
            high = mid - 1;
        else
            low = mid + 1;
    }
    free(arr);
    return index;
}

int main() {
    int choice;
    Player *p = NULL;
    int count = 0;
    do {
        printf("\n==== CLAYRY DANA JAYO 138848 TOURNAMENT SYSTEM ====\n");
        printf("1. Input Player\n");
        printf("2. Display data\n");
        printf("3. Merge Sort Username Asc \n");
        printf("4. Heap Sort Nickname Desc \n");
        printf("5. Quick Sort Match Asc \n");
        printf("6. Binary Search Nickname\n");
        printf("7. Exit\n");
        printf("Choose: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n')
                ;
            continue;
        }
        getchar();

        switch (choice) {
        case 1: {
            char username[100], nickname[100], hero[100];
            int matches, winrate;
            printf("Username: ");
            scanf(" %[^\n]", username);
            printf("Nickname: ");
            scanf(" %[^\n]", nickname);
            printf("Hero: ");
            scanf(" %[^\n]", hero);
            printf("Matches: ");
            scanf("%d", &matches);
            printf("Winrate: ");
            scanf("%d", &winrate);

            Player *newNode =
                createPlayer(username, nickname, hero, matches, winrate);
            if (p == NULL) {
                p = newNode;
            } else {
                Player *temp = p;
                while (temp->next)
                    temp = temp->next;
                temp->next = newNode;
                newNode->prev = temp;
            }
            count++;
            printf("\nPlayer added successfully!\n");
            break;
        }
        case 2:
            displayData(p);
            break;
        case 3:
            if (count > 0) {
                Player *tempList = copyList(p);
                tempList = mergeSort(tempList);
                printf("\n=== MERGE SORT USERNAME ASC ===\n");
                displayData(tempList);
                freeList(tempList);
            } else {
                printf("\nList is empty.\n");
            }
            break;
        case 4:
            if (count > 0) {
                Player *tempList = copyList(p);
                heapSortNicknameDesc(tempList, count);
                printf("\n=== HEAP SORT NICKNAME DESC ===\n");
                displayData(tempList);
                freeList(tempList);
            } else {
                printf("\nList is empty.\n");
            }
            break;
        case 5:
            if (count > 0) {
                Player *tempList = copyList(p);
                tempList = quickSortRecur(tempList, getTail(tempList));
                printf("\n=== QUICK SORT MATCHES ASC ===\n");
                displayData(tempList);
                freeList(tempList);
            } else {
                printf("\nList is empty.\n");
            }
            break;
        case 6: {
            if (count == 0) {
                printf("\nNo players to search.\n");
                break;
            }
            char nickname_search[100];
            printf("Nickname to search: ");
            scanf(" %[^\n]", nickname_search);

            Player *tempList = copyList(p);
            heapSortNicknameDesc(tempList, count);

            int idx = binarySearchNickname(tempList, count, nickname_search);
            if (idx != -1)
                printf("\nPlayer '%s' found!\n", nickname_search);
            else
                printf("\nNickname not found.\n");

            freeList(tempList);
            break;
        }
        case 7:
            printf("\nExiting system...\n");
            break;
        default:
            printf("\nInvalid choice!\n");
        }
    } while (choice != 7);

    freeList(p);
    return 0;
}
