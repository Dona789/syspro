#include <stdio.h>

int main(int argc, char *argv[]) {
    int ch;
    FILE *fp1, *fp2;

    if (argc != 3) {
        fprintf(stderr, "사용법: %s 원본파일 대상파일\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "r");
    if (!fp1) {
        fprintf(stderr, "File %s Open Error\n", argv[1]);
        return 2;
    }

    fp2 = fopen(argv[2], "w");
    if (!fp2) {
        perror("대상 파일 열기 실패");
        fclose(fp1);
        return 3;
    }

    while ((ch = fgetc(fp1)) != EOF) {
        fputc(ch, fp2);
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}

