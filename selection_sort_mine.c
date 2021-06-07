/*selection sort*/
#include <stdio.h>
void swap(int *a, int *b);

int main()
{
    int list[] = {9, 5, 2, 7, 4, 6, 3};
    int min, i, j;
    int n = sizeof(list)/sizeof(int);
    for(i = 0; i < n-1; i++)
    {
        min = i;
        for(j = i+1; j < n; j++)
            if(list[j] < list[min])
            {
                min = j;
            }
        swap(&list[i], &list[min]);    
    }

}
void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}