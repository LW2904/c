#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int remove_array_item(void *array, int index, int length,
	size_t item_size);

int main()
{
	int arr_len = 5;
	int *arr = malloc(sizeof(int) * arr_len);

	for (int i = 0; i < arr_len; i++) {
		arr[i] = i + 1;
	}

	arr_len = remove_array_item(arr, 2, arr_len, sizeof(int));

	for (int i = 0; i < arr_len; i++) {
		printf("%d\n", arr[i]);
	}

	return 0;
}

static inline int remove_array_item(void *array, int index, int length,
	size_t item_size)
{
	size_t byte_offset = item_size * index;
	size_t new_size = item_size * (length - index - 1);

	memmove(array + byte_offset, array + byte_offset + item_size, new_size);

	return length - 1;
};