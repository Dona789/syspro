#include <stdio.h>
#include <fcntl.h>   // open(), creat()
#include <unistd.h>  // write(), dup(), close()
#include <string.h>  // strlen()

int main() {
    int fd, new_fd;

    // 1️⃣ myfile.txt라는 새 파일 만들기 (쓰기용)
    fd = creat("myfile.txt", 0600);   // rw------- 권한
    if (fd == -1) {
        perror("파일 생성 오류");
        return 1;
    }

    // 2️⃣ 첫 번째 디스크립터(fd)로 데이터 쓰기
    const char *msg1 = "Hello! Linux\n";
    write(fd, msg1, strlen(msg1));

    // 3️⃣ fd를 복제해서 new_fd 만들기
    new_fd = dup(fd);  // fd를 복제하면 같은 파일을 가리키는 새 번호가 생김
    if (new_fd == -1) {
        perror("dup 오류");
        close(fd);
        return 1;
    }

    // 4️⃣ 복제된 new_fd로 다른 내용 쓰기
    const char *msg2 = "Bye! Linux\n";
    write(new_fd, msg2, strlen(msg2));

    // 5️⃣ 파일 닫기
    close(fd);
    close(new_fd);

    printf("✅ myfile.txt 파일에 두 번 쓰기가 완료되었습니다!\n");
    return 0;
}

