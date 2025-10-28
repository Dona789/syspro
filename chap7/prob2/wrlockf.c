#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[]) {
    int fd, id;
    struct student record;

    if (argc < 2) {
        fprintf(stderr, "How to use : %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("\nEnter StudentID you want to modify : ");
    while (scanf("%d", &id) == 1) {
        // 1) 해당 학생 레코드 위치로 이동
        lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);

        // 2) lockf로 쓰기 잠금 시도 (이 레코드 크기만큼)
        //    F_LOCK: 잠금 걸고, 이미 잠겨있으면 잠금 풀릴 때까지 기다림
        if (lockf(fd, F_LOCK, sizeof(record)) == -1) {
            perror(argv[1]);
            exit(3);
        }

        // 3) 현재 레코드 읽기
        if ((read(fd, (char *)&record, sizeof(record)) > 0) && (record.id != 0)) {
            printf("Name:%s\t StuID:%d\t Score:%d\n",
                   record.name, record.id, record.score);

            // 4) 점수 수정
            printf("Enter new score : ");
            scanf("%d", &record.score);

            // 방금 읽은 위치로 다시 뒤로 가서 덮어쓰기
            lseek(fd, (long)-sizeof(record), SEEK_CUR);
            write(fd, (char *)&record, sizeof(record));

            // 5) 다시 그 레코드 위치로 이동해서 잠금 해제
            lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);
            lockf(fd, F_ULOCK, sizeof(record));  // unlock
        } else {
            printf("No record %d\n", id);
        }

        printf("\nEnter StudentID you want to modify : ");
    }

    close(fd);
    exit(0);
}

