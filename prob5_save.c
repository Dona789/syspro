#include <stdio.h>
#include <fcntl.h>    // open(), O_WRONLY, O_CREAT
#include <unistd.h>   // write(), lseek(), close()
#include "student.h"  // 우리가 만든 구조체 헤더 포함

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [저장할파일명]\n", argv[0]);
        return 1;
    }

    // 1️⃣ 파일 열기 (없으면 만들기)
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0640);
    if (fd == -1) {
        perror("파일 생성/열기 실패");
        return 1;
    }

    struct student s;
    printf("학번 이름 점수 입력 (Ctrl+D로 종료)\n");

    // 2️⃣ Ctrl+D 입력 전까지 반복해서 학생 정보 받기
    while (scanf("%d %s %d", &s.id, s.name, &s.score) == 3) {
        // 3️⃣ 학번을 기준으로 파일에서 저장할 위치 계산
        off_t pos = (off_t)(s.id - START_ID) * sizeof(s);

        // 4️⃣ 해당 위치로 이동
        if (lseek(fd, pos, SEEK_SET) == -1) {
            perror("lseek 실패");
            close(fd);
            return 1;
        }

        // 5️⃣ 구조체 데이터를 파일에 쓰기
        if (write(fd, &s, sizeof(s)) != sizeof(s)) {
            perror("쓰기 실패");
            close(fd);
            return 1;
        }
    }

    printf("✅ 학생 정보 저장 완료!\n");
    close(fd);
    return 0;
}

