/*insertion sort-youtube*/
void insertion_sort(A, n)
{
	int value, i, j, hole;
	for(i = 1; i < n-1; i++)
	{
		value = A[i];
		hole = i;
		while(hole > 0 && value < A[hole-1])
		{
			A[hole] = A[hole-1];
			hole--;
		}
		A[hole] = value;
	}
}
/*insertion sort-book*/
void insertion_sort(int list [], int n)
{
	int i, j, next;
	for(i = 1; i < n-1; i++)
	{
		next = list[i];
		for(j = i-1; j >= 0 && next < list[j]; j--)
			list[j+1] = list[j];
		list[j+1] = next;
	}
}