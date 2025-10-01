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

    fp = fopen(argv[1], "w");
    if (!fp) {
        perror("fopen");
        return 2;
    }

    printf("학번 이름 점수 입력 (Ctrl+D로 종료)\n");

    while (scanf("%d %19s %hd", &rec.id, rec.name, &rec.score) == 3) {
        fprintf(fp, "%d %s %d\n", rec.id, rec.name, rec.score);
    }

    fclose(fp);
    return 0;
}

