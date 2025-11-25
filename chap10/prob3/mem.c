#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[32] = "Do you like Linux?";
    char *ptr, *p;

    // 1) malloc으로 32바이트 동적 할당
    ptr = (char *)malloc(32);
    if (ptr == NULL) {
        perror("malloc");
        exit(1);
    }

    // 2) memcpy로 str의 내용을 ptr에 복사
    memcpy(ptr, str, strlen(str) + 1);  // +1은 \0 포함
    puts(ptr);

    // 3) memset: ptr의 12번째 위치 문자를 'l'로 바꿈
    memset(ptr + 12, 'l', 1);
    puts(ptr);

    // 4) memchr: ptr에서 'l'을 처음 찾은 위치를 p에 저장
    p = (char *)memchr(ptr, 'l', 18);
    if (p != NULL)
        puts(p);

    // 5) memmove로 str의 7번째부터 10개를 str의 12번째 위치로 이동
    memmove(str + 12, str + 7, 10);
    puts(str);

    free(ptr);
    return 0;
}

