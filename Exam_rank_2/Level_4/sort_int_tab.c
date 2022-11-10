#include <stdio.h>

void sort_int_tab(int *tab, unsigned int size)
{
	unsigned int i = 0;
	int temp;
	while (i < (size - 1))
	{
		if (tab[i] < tab[i + 1])
		{
			temp = tab[i + 1];
			tab[i + 1] = tab[i];
			tab[i] = temp;
			i = 0;
		}
		else i++;
	}
}

int main()
{
	int arr[5] = {1, 7, 2, 5, 4};
	sort_int_tab(arr, 5);
	printf("%d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);

}