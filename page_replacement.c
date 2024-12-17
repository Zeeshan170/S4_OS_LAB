#include <stdio.h>

typedef struct {
    int page;
} Frame;

int pf = 0; // stores no.of page faults
int total = 5; // no.of frames
Frame Frames[5]; // Frames available

typedef struct {
    int page;
    int freq;
} Freq;

void Display() {
    printf("\n");
    for(int i = 0; i < total; i++) {
        printf("Frame %d: Page %d\n", i, Frames[i].page);
    }
    printf("\n");
}

int check_fault(int page) {
    for(int i = 0; i < total; i++) {
        if (Frames[i].page == page) {
            return 1;
        }
    }
    return 0;
}

void FIFO(int REQ[], int N) {
    int front = 0;
    pf = 0;
    for(int i = 0; i < N; i++) {
        if (!check_fault(REQ[i])) { // page fault occurred
            Frames[front].page = REQ[i];
            front = (front + 1) % total;
            pf++;
        }
        Display();
    }
}

int find_page(int page) {
    for(int i = 0; i < total; i++) {
        if (Frames[i].page == page) {
            return i;
        }
    }
    return -1;
}

int look_back(int REQ[], int current, int looked) {
    if (current <= total) {
        return -1; // frames are not completely filled don't look back
    }
    for(int i = looked; i < current; i++) {
        if (find_page(REQ[i]) != -1) {
            printf("%d", find_page(REQ[i]));
            return find_page(REQ[i]);
        }
    }
    return -1;
}

void LRU(int REQ[], int N) {
    int time = 0;
    int front = 0;
    pf = 0;
    for(int i = 0; i < total; i++) {
        Frames[i].page = -1;
    }
    for(int i = 0; i < N; i++) {
        if (!check_fault(REQ[i])) { // page fault occurred
            if(front < total) {
                Frames[front].page = REQ[i];
                front++;
            } else {
                int lru_time = time;
                int lru_index = 0;
                for(int j = 0; j < total; j++) {
                    if(Frames[j].page != -1) {
                        int k = i - 1;
                        while(k >= 0 && REQ[k] != Frames[j].page) {
                            k--;
                        }
                        if(k < lru_time) {
                            lru_time = k;
                            lru_index = j;
                        }
                    }
                }
                Frames[lru_index].page = REQ[i];
            }
            pf++;
        }
        time++;
        Display();
    }
}

void sort(Freq table[], int len) {
    for(int i = 0; i < len; i++) {
        for(int j = i; j < len - i - 1; j++) {
            if (table[j].freq < table[j + 1].freq) {
                Freq temp;
                temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            }
        }
    }
}

int find_min_freq(int REQ[], int current) {
    Freq table[30];
    int count = 0;
    for(int i = 0; i < current; i++) { // make freq table for the pages seen until now
        int found = 0;
        for(int j = 0; j < count; j++) {
            if(table[j].page == REQ[i]) {
                found = 1;
                table[j].freq = table[j].freq + 1;
            }
        }
        if (found == 0) {
            table[count].page = REQ[i];
            table[count].freq = 1;
            count++;
        }
    }
    for(int i = 0; i < count; i++) {
        printf("%d:%d\n", table[i].page, table[i].freq);
    }
    printf("\n");
    sort(table, count);
    for(int i = 0; i < count; i++) {
        for(int j = 0; j < total; j++) {
            if (table[i].page == Frames[j].page) {
                return j;
            }
        }
    }
    return -1;
}

void LFU(int REQ[], int N) {
    int front = 0;
    int looked = 0;
    for(int i = 0; i < N; i++) {
        int index = find_min_freq(REQ, i);
        if(!check_fault(REQ[i]) && front >= 5) {
            printf("*\n");
            Frames[index].page = REQ[i];
        } else if (!check_fault(REQ[i])) {
            printf("here\n");
            Frames[front].page = REQ[i];
            front++;
        }
        Display();
    }
}

int main() {
    int ch;
    int N;
    int REQ[40];
    while(1) {
        printf("MENU:\n1:FIFO\n2:LRU\n3:LFU\n");
        printf("Enter no.of Pages:");
        scanf("%d", &N);
        printf("Enter Page no:");
        for(int i = 0; i < N; i++) {
            scanf("%d", &REQ[i]);
        }
        printf("Enter choice:");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                FIFO(REQ, N);
                break;
            case 2:
                LRU(REQ, N);
                break;
            case 3:
                LFU(REQ, N);
                break;
            case -1:
                return 0;
                break;
            default:
                printf("Invalid input\n");
                break;
        }
    }
}
