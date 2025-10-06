#include <stdio.h>



int mystrlen(const char* str1) {

	int k = 0;

	for (k; str1[k] != '\0'; k++)
		;
	

	return k;

}

char* mystrcpy(char* dest, const char* str2) {
	int k = 0;
	int len = mystrlen(str2);
	for (k; k != len; k++)
		dest[k] = str2[k];

	dest[k] = '\0';

	return dest;
}

char* mystrcmp(char* str1, char* str2) {

	int max_len;
	int k = 0;
	int len1 = mystrlen(str1);
	int len2 = mystrlen(str2);

	if (len1 > len2)
		max_len = len1;
	else
		max_len = len2;

	for (k; k < max_len; k++) {
		if ((str1[k] == '\0') && (str2[k] > 0))
			return -1;
		else if ((str2[k] == '\0') && (str1[k] > 0))
			return 1;
		else if (str1[k] < str2[k])
			return -1;
		else if (str1[k] > str2[k])
			return 1;
		

		if ((k + 1) == max_len)
			return 0;

	}

}

char* mystrcat(char* str1, char* str2) {

	int k = 0;
	int i = 0;
	int len1 = mystrlen(str1);
	int len2 = mystrlen(str2);
	int len_sum = len1 + len2;

	for (k; k < len_sum; k++) {
		if (k >= len1) {
			str1[k] = str2[i];
			i++;
		}
	}
	str1[k] = '\0';

	return str1;
}




char* mystrstr(char* str1, char* str2)
{	
	int k = 0;
	int len1 = mystrlen(str1);
	int len2 = mystrlen(str2);
	int i = 0;


for ( k ; k <= len1 - len2; k++) {

	for (i = 0; i < len2; i++) {
		if (str1[k + i] != str2[i]) {
			break;
		}
	}
	if (i == len2) {
		return &str1[k];
	}
}

return 0;

}

char* reverse(char* dest, char* str2) {

	int k = 0;
	int i = mystrlen(str2) - 1;
	int len = i+1;
	

	for (i , k ; i > 0 && k < len ; i--, k++) {
		dest[k] = str2[i];
	}

	dest[k] = '\0';

	return dest;

}

int main(void)
{
	char str1[100] = "ab";
	char* str2 = "abc";
	char dest[100];



	//printf("%d\n", mystrlen(str1));

	//printf("%s", mystrcpy(dest, str2));

	printf("%d", mystrcmp(str1, str2));

	//printf("%s", mystrcat(str1, str2));

	//printf("%s\n", mystrstr(str1, str2));
	
	//printf("%s", reverse(dest, str2));

	return 0;
}




