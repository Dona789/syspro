#include <stdio.h>
#include <fcntl.h>   
#include <unistd.h>  

int main(int argc, char *argv[]) {
    int fd;

   
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        return 1;
    }


    fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("파일 열기 오류");
        return 1;
    }

    printf("파일명: %s\n", argv[1]);
    printf("파일 디스크립터: %d\n", fd);

   
    close(fd);
    return 0;
}

