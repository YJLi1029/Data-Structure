#include <stdio.h>
#include "queuesADT.h"

void Era(int num){//에라토스테네스의 체에 관한 함수
    int* arr;
    arr=(int*)malloc(sizeof(int) * num);//배열 공간 할당
    arr[0]=arr[1]=0;//0 과 1에 해당하는 부분 0으로 초기화

    //배열 초기화
    for(int i=2;i<=num;i++){
        arr[i]=i;
    }

    //i를 제외한 i의 배수를 0으로 설정
    for(int i=2;i<=num;i++){
        if(arr[i]==0) continue;
        for(int j=i+i;j<=num;j+=i){
            arr[j]=0;
        }
    }
    //소수를 구한 결과 출력
    for(int i=0;i<num;i++){
        if(arr[i]==0) continue; //0으로 설정했던 소수가 아닌 수들을 제외
        printf("%d ", arr[i]);
    }
}

int main(){

    Era(100);
}