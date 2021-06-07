/*bubble sort*/
#include <stdio.h>
void swap(int *a, int *b);

int main()
{
    int list[] = {15, 4, 8, 3, 50, 9, 20};
    int flag = 1, i, j;
    int n = sizeof(list)/sizeof(int);
    for(i = n-1; flag > 0; i--)
    {
        flag = 0; //no swap
        for(j = 0; j < i; j++)
            if(list[j] > list[j+1])
            {
                swap(&list[j], &list[j+1]);
                flag = 1; //swap
            }   
    }

}
void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}