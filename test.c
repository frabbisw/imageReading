#include<stdio.h>

struct M
{
	int a;
	int b;
};

int main()
{
	unsigned char str[100]={1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,0,5,0,0,0,6,0,0,0,7,0,0,0,8,0,0,0,9,0,0,0,10,0,0,0};
	
	struct M *arr = str;
	
	arr[0].a=255,arr[0].b=255;
	
	printf("%d\n",str[0]);
		
		
	
	return 0;
}
