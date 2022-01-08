#include <stdio.h>
#include <stdlib.h>
 
int main(void) {
	FILE *fp; // FILE型構造体
	char fname[] = "Iris.txt";
	int chr;
 
	fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
	}
 
	while((chr = fgetc(fp)) != EOF) {
		putchar(chr);
	}

    printf("\n");
 
	fclose(fp); // ファイルを閉じる
 
	return 0;
}