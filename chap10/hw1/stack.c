#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

/* top은 '스택의 맨 위를 가리키는 더미(head) 노드'라고 생각하면 됨.
   실제 데이터 노드들은 top->next부터 시작 */
void push(struct node *top, int data) {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL) {
        perror("malloc");
        exit(1);
    }

    p->data = data;
    p->next = top->next;  // 기존 맨 앞 노드를 그 다음으로
    top->next = p;        // 새 노드를 스택의 맨 위로
}

int pop(struct node *top) {
    struct node *p;
    int value;

    if (top->next == NULL) {
        // 스택이 비어있을 때
        fprintf(stderr, "스택이 비어 있습니다.\n");
        return -1;
    }

    p = top->next;        // 맨 위 노드
    value = p->data;      // 데이터 저장
    top->next = p->next;  // 두 번째 노드를 새로운 top->next로
    free(p);              // 노드 메모리 해제
    return value;
}

int main(void) {
    struct node top;   // 더미(head) 노드
    int x;

    top.next = NULL;   // 처음에는 스택이 비어 있음

    printf("자연수를 차례로 입력하세요.\n");
    printf("자연수 외 값을 입력하면 입력을 종료하고 스택을 출력합니다.\n");

    // 자연수 입력 받기: 정수 아니거나, 1 이하(0, 음수)면 종료
    while (scanf("%d", &x) == 1 && x > 0) {
        push(&top, x);
    }

    printf("\n[스택 내용: Top -> Bottom]\n");
    while (top.next != NULL) {
        int v = pop(&top);
        printf("%d ", v);
    }
    printf("\n");

    return 0;
}

