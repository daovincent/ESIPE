#include <stdio.h>
#include <stdlib.h>

void print(int* array,int s){
    int i,size;
    size = s;
    for ( i = 0; i < size; i++)
    {
        printf("%d\t",array[i]);
    }
}
void permutations(int buffer[], int current, int max){
	int i;
	if (current > max)
	{
		print(buffer,max);
	}
	for ( i = 0; i < max; i++)
		{
		if (buffer[i] == 0)
			{
				buffer[i] = current;
				permutations(buffer,current+1,max);
                printf("\n");
				buffer[i] = 0;
			}			
		}
}




int main(int argc, char const *argv[])
{
    /* code */
    int buffer[] = {0,0,0,0};
	permutations(buffer,1,4);
    return 0;
}
