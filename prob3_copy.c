#include <stdio.h>
#include <fcntl.h>    // open()
#include <unistd.h>   // read(), write(), close()

#define BUFSIZE 512   // 읽고 쓸 버퍼 크기

int main(int argc, char *argv[]) {
    int fd1, fd2;           // fd1: 원본 파일, fd2: 새 파일
    char buf[BUFSIZE];      // 읽어올 버퍼
    ssize_t n;              // 읽은 바이트 수

    // 명령줄 인자가 제대로 들어왔는지 확인
    if (argc != 3) {
        fprintf(stderr, "사용법: %s [원본파일] [새파일]\n", argv[0]);
        return 1;
    }

    // 1️⃣ 원본 파일 열기 (읽기 전용)
    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("원본 파일 열기 오류");
        return 1;
    }

    // 2️⃣ 새 파일 만들기 (쓰기 전용, 없으면 생성, 있으면 덮어쓰기)
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd2 == -1) {
        perror("새 파일 생성 오류");
        close(fd1);
        return 1;
    }

    // 3️⃣ 원본 파일에서 읽어서 새 파일에 쓰기
    while ((n = read(fd1, buf, BUFSIZE)) > 0) {
        write(fd2, buf, n);
    }

    printf("✅ 복사가 완료되었습니다!\n");

    // 4️⃣ 파일 닫기
    close(fd1);
    close(fd2);

    return 0;
}

