#include <stdio.h>
#include <fcntl.h>    // open()
#include <unistd.h>   // read(), write(), lseek(), close()
#include "student.h"  // 구조체 헤더 포함

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        return 1;
    }

    // 1️⃣ 읽기/쓰기 모드로 파일 열기
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("파일 열기 오류");
        return 1;
    }

    char cont = 'Y';          // 계속 여부
    struct student s;         // 학생 구조체
    int id;                   // 수정할 학번

    // 2️⃣ 반복: 수정할 학번 입력받기
    do {
        printf("수정할 학생의 학번을 입력하세요: ");
        scanf("%d", &id);

        // 3️⃣ 해당 학번의 위치로 이동
        off_t pos = (off_t)(id - START_ID) * sizeof(s);
        if (lseek(fd, pos, SEEK_SET) == -1) {
            perror("lseek 오류");
            close(fd);
            return 1;
        }

        // 4️⃣ 구조체 하나 읽기
        ssize_t n = read(fd, &s, sizeof(s));
        if (n == sizeof(s) && s.id != 0) {
            printf("현재 점수: %d\n", s.score);
            printf("새 점수를 입력하세요: ");
            scanf("%d", &s.score);

            // 5️⃣ 커서를 한 칸 뒤로 되돌려서 덮어쓰기
            if (lseek(fd, -(off_t)sizeof(s), SEEK_CUR) == -1) {
                perror("lseek 되돌리기 실패");
                close(fd);
                return 1;
            }

            if (write(fd, &s, sizeof(s)) != sizeof(s)) {
                perror("쓰기 실패");
                close(fd);
                return 1;
            }

            printf("✅ 점수가 성공적으로 수정되었습니다!\n");
        } else {
            printf("❌ 해당 학번의 레코드가 없습니다.\n");
        }

        // 6️⃣ 계속 여부 묻기
        printf("다른 학생도 수정하시겠습니까? (Y/N): ");
        scanf(" %c", &cont);  // 앞에 공백 주의 (버퍼 제거)

    } while (cont == 'Y' || cont == 'y');

    close(fd);
    return 0;
}

