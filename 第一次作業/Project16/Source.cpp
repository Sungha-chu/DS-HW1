#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define N 512

//鏡像
void mirrorImg(unsigned char* src, unsigned char* dest) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			dest[row * N + col] = src[row * N + (N - (col+1))];
		}
	}
}

//翻轉
void flipImg(unsigned char* src, unsigned char* dest) {
	for (int col = 0; col < N; col++) {
		for (int row = 0; row < N; row++) {
			dest[row * N + col] = src[(N-(row+1)) * N + col];
			 
		}
	}
}

//旋轉
void turnImg(unsigned char* src, unsigned char* dest) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			dest[row * N + col] = src[col * N + N - row];
			int num = dest[(N - (row + 1)) * N + col];
			num = dest[row * N + col];
		}
	}
}

//負片
void negImg(unsigned char* src, unsigned char* dest) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			dest[row * N + col] = 255 - src[row * N + col];
		}
	}
}

//模糊
void blurImg(unsigned char* src, unsigned char* dest) {
	for (int row = 1; row < N; row++) {
		for (int col = 1; col < N; col++) {
			int sum = (src[(row - 1) * 512 + col - 1] + src[(row - 1) * 512 + col] + src[(row - 1) * 512 + col + 1] +
				src[row * 512 + col - 1] + src[row * 512 + col] + src[row * 512 + col + 1] +
				src[(row + 1) * 512 + col - 1] + src[(row + 1) * 512 + col] + src[(row + 1) * 512 + col + 1]) / 9.0;
			dest[row * 512 + col] = sum;
		}
	}
}

void main() {
	unsigned char* temp = (unsigned char*)malloc(N * N * sizeof(unsigned char));	//轉換
	unsigned char src[N * N];	//來源

	char filename[20];
	printf("FileName:");
	scanf("%s", filename);//輸入檔案名稱

	FILE* file = fopen(filename, "rb+");
	fread(src, 512 * 512, 1, file);
	fclose(file);
	
	//鏡像
	mirrorImg(src, temp);
    file = fopen("mirror", "wb");
	fwrite(temp, N * N, 1, file);
	fclose(file);
	
	//翻轉
	flipImg(src, temp);
	file = fopen("flip", "wb");
	fwrite(temp, N * N, 1, file);
	fclose(file);
	
	//旋轉
	turnImg(src, temp);
	file = fopen("turn", "wb");
	fwrite(temp, N * N, 1, file);
	fclose(file);

	//負片
	negImg(src, temp);
    file = fopen("negative", "wb");
	fwrite(temp, N * N, 1, file);
	fclose(file);

	//模糊化
	blurImg(src, temp);
    file = fopen("blur", "wb");
	fwrite(temp, N * N, 1, file);
	fclose(file);

	free(temp);
}