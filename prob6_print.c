#include <stdio.h>
#include <fcntl.h>    // open()
#include <unistd.h>   // read(), lseek(), close()
#include "student.h"  // 우리가 만든 구조체 헤더 포함

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        return 1;
    }

    // 1️⃣ 파일 열기 (읽기 전용)
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("파일 열기 오류");
        return 1;
    }

    char cont = 'Y';         // 계속할지 여부
    struct student s;        // 학생 구조체 변수
    int id;                  // 검색할 학번

    // 2️⃣ 계속 검색 반복
    do {
        printf("검색할 학번을 입력하세요: ");
        scanf("%d", &id);

        // 3️⃣ 학번에 맞는 위치로 이동
        off_t pos = (off_t)(id - START_ID) * sizeof(s);
        if (lseek(fd, pos, SEEK_SET) == -1) {
            perror("lseek 오류");
            close(fd);
            return 1;
        }

        // 4️⃣ 구조체 한 개 읽기
        ssize_t n = read(fd, &s, sizeof(s));
        if (n == sizeof(s) && s.id != 0) {
            printf("✅ 학생 정보\n");
            printf("학번: %d\n", s.id);
            printf("이름: %s\n", s.name);
            printf("점수: %d\n", s.score);
        } else {
            printf("❌ 해당 학번의 레코드가 없습니다.\n");
        }

        // 5️⃣ 계속 검색할지 물어보기
        printf("계속 검색하시겠습니까? (Y/N): ");
        scanf(" %c", &cont);  // 앞에 공백 꼭 넣기 (버퍼 제거용)

    } while (cont == 'Y' || cont == 'y');

    close(fd);
    return 0;
}

