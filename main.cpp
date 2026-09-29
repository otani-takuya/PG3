#include <stdio.h>
#include <iostream>

int main(){
	//コンソールをUTF-8に設定
	system("chcp 65001 > nul"); 
	char str[] = "こんにちは";
	printf("%s\n", str);

	return 0;
}