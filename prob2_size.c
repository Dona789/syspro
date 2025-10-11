#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>   

#define BUFSIZE 512   

int main(int argc, char *argv[]) {
    int fd;               
    char buf[BUFSIZE];   
    ssize_t n;            
    int total = 0;        

    
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        return 1;
    }

    
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("파일 열기 오류");
        return 1;
    }

    
    while ((n = read(fd, buf, BUFSIZE)) > 0) {
        total += n;
    }

    printf("파일명: %s\n", argv[1]);
    printf("파일 크기: %d 바이트\n", total);

   
    close(fd);
    return 0;
}

