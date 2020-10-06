/*에라토스테네스의 체(Eratosthenes' sieve) 문제를 구현하시오.
(PPT p.29의 queue applications 내용을 참고하여 2~100까지의 수 가운데 소수(prime number)를 찾아 queue에 저장하고, 이를 화면에 출력)*/

#include <stdio.h>
#include "queuesADT.h"

 int num=100;
int N[101];

int main(){
    

}

void PNum(){
    for(int i=2;i<=num;i++){
        N[i]=i;
    }
    for(int i=2;i<=num;i++){
        if(N[i]==0) continue;
        for(int j=i+i;j<=num;j+=i){
            N[j]=0;
        }
    }
}