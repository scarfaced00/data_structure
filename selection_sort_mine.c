/*selection sort-max-first version*/
#include <stdio.h>
void swap(int *a, int *b);

int main()
{
    int list[] = {31, 9, 10, 23, 49, 15, 11, 7};
    int max, i, j;
    int n = sizeof(list)/sizeof(int);
    for(i = n-1; i > 1; i--)
    {
        max = i;
        for(j = i-1; j >= 0; j--)
            if(list[j] > list[max])
            {
                max = j;
            }
        swap(&list[i], &list[max]);    
    }

}
void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}