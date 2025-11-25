#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node *head, struct node *tail, int data) {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL) {
        perror("malloc");
        exit(1);
    }

    p->data = data;
    p->next = NULL;

    // tail->next가 실제 마지막 노드 (첫 노드도 tail가 관리)
    tail->next->next = p;  // 현재 마지막 노드의 next = 새 노드
    tail->next = p;        // tail가 새 노드를 가리키도록 갱신
}

int delete(struct node *head, struct node *tail) {
    struct node *p;
    int value;

    // head->next가 실제 첫 번째 노드
    if (head->next == tail->next) {
        fprintf(stderr, "큐가 비어 있습니다.\n");
        return -1;
    }

    p = head->next;          // 첫 번째 노드
    value = p->data;

    head->next = p->next;    // 두 번째 노드를 첫 노드로
    free(p);

    return value;
}

int main(void) {
    struct node head, tail;
    struct node dummy;   // 데이터 없는 더미 노드(큐 시작점)
    int x;

    dummy.next = NULL;
    head.next = &dummy;  // 큐 시작
    tail.next = &dummy;  // 큐 끝 → 처음엔 dummy가 head = tail

    printf("자연수를 차례로 입력하세요.\n");
    printf("자연수 외의 값을 입력하면 큐 전체를 출력합니다.\n");

    // 입력: 자연수만 addq(), 그 외는 종료
    while (scanf("%d", &x) == 1 && x > 0) {
        addq(&head, &tail, x);
    }

    printf("\n[큐 내용: Front -> Rear]\n");
    while (head.next != tail.next) {
        int v = delete(&head, &tail);
        printf("%d ", v);
    }
    printf("\n");

    return 0;
}

