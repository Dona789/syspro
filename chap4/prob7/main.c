#include <stdio.h>

struct student {
    int id;
    char name[20];
    short score;
};

int main(int argc, char *argv[]) {
    struct student rec;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일명\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "rb");   // binary read 모드
    if (!fp) {
        perror("fopen");
        return 2;
    }

    printf("-----------------------------------\n");
    printf(" StudentID   Name   Score\n");
    printf("-----------------------------------\n");

    while (fread(&rec, sizeof(rec), 1, fp) > 0) {
        printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);
    }

    printf("-----------------------------------\n");

    fclose(fp);
    return 0;
}

