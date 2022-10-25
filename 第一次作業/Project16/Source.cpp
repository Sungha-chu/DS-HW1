#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define N 512

//�蹳
void mirrorImg(unsigned char* src, unsigned char* dest) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			dest[row * N + col] = src[row * N + (N - (col+1))];
		}
	}
}

//½��
void flipImg(unsigned char* src, unsigned char* dest) {
	for (int col = 0; col < N; col++) {
		for (int row = 0; row < N; row++) {
			dest[row * N + col] = src[(N-(row+1)) * N + col];
			 
		}
	}
}

//����
void turnImg(unsigned char* src, unsigned char* dest) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			dest[row * N + col] = src[col * N + N - row];
			int num = dest[(N - (row + 1)) * N + col];
			num = dest[row * N + col];
		}
	}
}

//�t��
void negImg(unsigned char* src, unsigned char* dest) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			dest[row * N + col] = 255 - src[row * N + col];
		}
	}
}

//�ҽk
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
	unsigned char* temp = (unsigned char*)malloc(N * N * sizeof(unsigned char));	//�ഫ
	unsigned char src[N * N];	//�ӷ�

	char filename[20];
	printf("FileName:");
	scanf("%s", filename);//��J�ɮצW��

	FILE* file = fopen(filename, "rb+");
	fread(src, 512 * 512, 1, file);
	fclose(file);
	
	//�蹳
	mirrorImg(src, temp);
    file = fopen("mirror", "wb");
	fwrite(temp, N * N, 1, file);
	fclose(file);
	
	//½��
	flipImg(src, temp);
	file = fopen("flip", "wb");
	fwrite(temp, N * N, 1, file);
	fclose(file);
	
	//����
	turnImg(src, temp);
	file = fopen("turn", "wb");
	fwrite(temp, N * N, 1, file);
	fclose(file);

	//�t��
	negImg(src, temp);
    file = fopen("negative", "wb");
	fwrite(temp, N * N, 1, file);
	fclose(file);

	//�ҽk��
	blurImg(src, temp);
    file = fopen("blur", "wb");
	fwrite(temp, N * N, 1, file);
	fclose(file);

	free(temp);
}