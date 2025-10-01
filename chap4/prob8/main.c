#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s [stdin|stdout|stderr|파일명]\n", argv[0]);
        return 1;
    }

    if (!strcmp(argv[1], "stdin")) {
        fp = stdin;
        printf("아무 글자 입력 후 Enter: ");
        getchar();   // 입력 대기
    }
    else if (!strcmp(argv[1], "stdout")) {
        fp = stdout;
    }
    else if (!strcmp(argv[1], "stderr")) {
        fp = stderr;
    }
    else {
        fp = fopen(argv[1], "r");
        if (!fp) {
            perror("fopen");
            return 2;
        }
        if (getc(fp) == EOF) perror("getc");
    }

#if defined(__GLIBC__)
    // glibc 기준 내부 필드 사용
    printf("Stream = %s, ", argv[1]);
    if (fp->_flags & 0x0002)
        printf("Unbuffered");
    else if (fp->_flags & 0x0200)
        printf("Line buffered");
    else
        printf("Fully buffered");

    printf(", Buffer size = %ld\n",
           (long)(fp->_IO_buf_end - fp->_IO_buf_base));
#else
    // 다른 libc 환경에서는 버퍼 크기 직접 확인 어려움
    printf("Stream = %s → 버퍼 확인 기능은 이 환경에서 지원 안 됨\n", argv[1]);
#endif

    if (fp != stdin && fp != stdout && fp != stderr)
        fclose(fp);

    return 0;
}

