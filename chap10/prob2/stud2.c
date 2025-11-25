#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[20];
    struct student *next;
};

int main() {
    int id;
    char name[20];
    int count = 0;
    struct student *p, *head = NULL;

    printf("학번과 이름을 입력하세요\n");
    printf("(학번란에 정수가 아닌 값을 입력하면 입력을 종료합니다)\n");

    // 학번에 정수 외의 값이 들어오면 scanf가 실패해서 while문이 종료됨
    while (scanf("%d %s", &id, name) == 2) {
        p = (struct student *)malloc(sizeof(struct student));
        if (p == NULL) {
            perror("malloc");
            exit(1);
        }

        p->id = id;
        strcpy(p->name, name);

        // 역순 출력을 위해 항상 리스트의 맨 앞에 삽입
        p->next = head;
        head = p;
    }

    printf("\n* 학생 정보 (역순) *\n");
    p = head;
    while (p != NULL) {
        count++;
        printf("학번: %d  이름: %s\n", p->id, p->name);
        p = p->next;
    }
    printf("총 %d 명입니다.\n", count);

    // 동적 할당 해제
    p = head;
    while (p != NULL) {
        struct student *tmp = p->next;
        free(p);
        p = tmp;
    }

    return 0;
}

