#include <stdio.h>
#define MAXLINE 1024   // 한 줄 최대 길이

int main(int argc, char *argv[]) {
    char buf[MAXLINE];
    int line = 0;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일명\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen");
        return 2;
    }

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        printf("%3d %s", ++line, buf);
    }

    fclose(fp);
    return 0;
}

