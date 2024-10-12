#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define WORD_SIZE 500
#define KEY_SIZE 10
#define WORD_BINARY_SIZE 500
#define WORD_BINARY_ROW_SIZE 500
#define WORD_BINARY_COLUMN_SIZE 16

#define SHOW_KEY_DECIMAL 0 // if you want to see decimale number of key character (0 - off/ 1 - on)
#define SHOW_BINARY_AND_DECIMAL 1 // if you want to see binary and decimale number of word character (0 - off/ 1 - on)
#define ENCRYPTED_MESSAGE 0 // if you want to see encrypted message (0 - off/ 1 - on)

int main() {
	bool chek = true;
	char word[WORD_SIZE], key[KEY_SIZE], word_bin_new[WORD_BINARY_ROW_SIZE][WORD_BINARY_COLUMN_SIZE], word_letters[WORD_SIZE];
	unsigned short word_bin[WORD_BINARY_SIZE];
	int remainder, divison, remainders;
	
	printf("\tWarning!\nOverflow may occur when using 2 or more characters.\nThe recommended maximum number of characters is 2.\n\n");
	printf("Enter a key(max 10 character): ");
	scanf("%10s", &key);
	
#if SHOW_KEY_DECIMAL
	printf("\n");
	for (int i = 0; i < strlen(key); i++)
	{
		printf("%c: %d\n",key[i], (int)key[i]);
	}
	printf("\n");
#endif

	while (getchar() != '\n');

	printf("Enter a word: ");
	fgets(word, sizeof(word), stdin);

	for (int i = 0; i < strlen(word); i++) word_bin[i] = word[i];
	for (int i = 0; i < strlen(word); i++) word_letters[i] = word[i];
	// Encrypted according to the necessary mathematical operations
	for (int i = 0; i < strlen(word); i++)
	{
		if (chek == true) {
			chek = false;
			for (int j = 0; j < strlen(key); j++)
			{
				word_bin[i] += 1;
				remainder = key[j] % 8;
				word_bin[i] = word_bin[i] << remainder;
			}
		}
		else if(chek == false && word_bin[i]!=10) {
			chek = true;
			for (int j = strlen(key)-1; 0 <= j; j--)
			{
				word_bin[i] += 1;
				remainder = key[j] % 8;
				word_bin[i] = word_bin[i] << remainder;
			}
		}
	}

	for (int i = 0; i < strlen(word); i++) word[i] = word_bin[i];
	
	// convert decimal to binary
	for (int i = 0; i < strlen(word)-1; i++)
	{
		divison = (int)word_bin[i];
		for (int a = 0; a < 16; a++)
		{
			remainders = divison % 2;
			divison = divison / 2;
			word_bin_new[i][a] = remainders;
		}
	}

#if SHOW_BINARY_AND_DECIMAL
	// prints binary and decimal numbers corresponding to letters
	printf("\n Binary\t\t: Decimal\n\n");
	for (int i = 0; i < strlen(word)-1; i++)
	{
		printf("%c:", word_letters[i]);
		for (int a = 15; a >= 0; a--)
		{
			printf("%d", word_bin_new[i][a]);
		}
		printf(": %d", (int)word_bin[i]);
		printf("\n");
	}
#endif
	
#if ENCRYPTED_MESSAGE
	printf("\nEncrypted message: ");
	for (int i = 0; i < strlen(word); i++)
	{
		printf("%c", word[i]);
	}
	printf("\n");
#endif
	return 0;
}