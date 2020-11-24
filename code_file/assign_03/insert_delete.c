#include <stdio.h>
#include "linkedListADT.h"
#include <stdbool.h>

int main(){
    LIST* list;
    bool chk;
    int* dataPtr;
    int n=0;
    int data;

    //insert
    list=createList(compare);//리스트생성

    addNode(list, 20);//null 리스트에 노드 삽입
    addNode(list, 5);//첫 노드 앞에 노드 삽입
    addNode(list, 10);//두 데이터 노드 사이에 삽입
    addNode(list, 15);//마지막 노드 뒤에 삽입

    do{
        chk=traverse(list, n, &data);
        if(!chk) printf("empty list");
        else printf("%d", &data);
    }while(chk);


    destroyList(list);//리스트 다시 비워주기

    //delete
    list=createList(compare);//리스트생성

    removeNode(list, 3, data);//null 리스트에서 제거하기

    addNode(list, 20);//null 리스트에 노드 삽입
    addNode(list, 5);
    addNode(list, 10);
    addNode(list, 15);
    removeNode(list, 20, data);//리스트의 첫번째 노드 삭제하기
    removeNode(list, 10, data);//두 데이터 사이의 노드 삭제하기
    removeNode(list, 15, data);//리스트의 마지막에 있는 노드 삭제하기
    removeNode(list, 50, data);//존재하지 않는 노드 삭제 시도하기
    removeNode(list, 8, data);//첫번째 데이터값보다 작은 값의 노드를 삭제하기
    removeNode(list, 30, data);//첫번째 데이터값보다 큰 값의 노드를 삭제하기
    removeNode(list, 5, data);//리스트 비우기
    removeNode(list, 5, data);//빈 리스트에서 삭제 시도하기





}