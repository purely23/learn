#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"

#define INITIAL_CAPACITY 10

//内部辅助函数:当容量不足时，进行扩容

static int resize_array(DynamicArray* arr, size_t new_capacity) {
	Data* new_data = (Data*)realloc(arr->data, new_capacity * sizeof(Data));

	if (!new_data) {
		//扩容失败
		return -1;
		//这里返回，意味着原先的arr->data还在
	}
	
	//realloc成功后，才会用新的地址更新结构体

	arr->data = new_data;

	arr->capacity = new_capacity;

	return 0;

}

//创建并初始化一个动态数组
DynamicArray* create_array(size_t initial_capacity) {
	if (initial_capacity = 0) {
		initial_capacity = INITIAL_CAPACITY;
	}
	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));

	if (!arr) 
		return NULL;
	arr->data = (Data*)malloc(initial_capacity * sizeof(Data));

	if (!arr->data) {
		free(arr);
		return NULL;
	}

	arr->size = 0;
	arr->capacity = initial_capacity;

	return arr;

}

//销毁数组，释放内存
void destory_array(DynamicArray* arr) {
	if (arr) {
		free(arr->data);
		free(arr);
	}
}

//在数组末尾追加元素
void array_append(DynamicArray* arr, Data value) {
	//检查数组是否要扩容
	if (arr->size >= arr->capacity) {
		size_t new_capacity = arr->capacity * 2;

		resize_array(arr, new_capacity);
	}
	arr->data[arr->size] = value;

	arr->size++;
}

//读取指定的索引元素
//返回一个指针,以便能够检查是否成功，若索引无效，返回NULL
Data* array_read(DynamicArray* arr, size_t index) {
	if (index >= arr->size) {
		return NULL;
	}
	return &arr->data[index];
}

//更新指定索引的元素
//返回0表示成功，返回-1表示失败
int array_update(DynamicArray* arr, size_t index, Data value) {
	if (index >= arr->size) {
		return -1;
	}
	arr->data[index] = value;

	return 0;
}

int array_insert(DynamicArray* arr, size_t index, Data value) {
	if (index > arr->size) {
		return -1;
	}
	//检查是否要扩容
	if (arr->size >= arr->capacity) {
		if (resize_array(arr, arr->capacity * 2) != 0) {
			return -1;
		}
	}
	for (size_t i = arr->size; i > index; --i) {
		arr->data[i] = arr->data[i - 1];
	}
	arr->data[index] = value;
	arr->size++;

	return 0;
}


//删除指定索引的元素
int array_delete(DynamicArray* arr, size_t index) {
	if (index >= arr->size) {
		return -1;
	}
	for (size_t i = index; i < arr->size; ++i) {
		arr->data[i] = arr->data[i + 1];
	}
	arr->size--;

	if (arr->size > 0 && arr->size <= arr->capacity / 4 && arr->capacity > INITIAL_CAPACITY) {
		size_t new_capacity = arr->capacity / 2;
		//保证缩容后的容量仍能装下所有元素，并且不小于初始容量

		if (new_capacity < arr->size) {
			new_capacity = arr->size;
		}
		if (new_capacity < INITIAL_CAPACITY) {
			new_capacity = INITIAL_CAPACITY;
		}

		printf("\n---> [缩容警告!] Size (%zu) <= Capacity/4 (%zu). 准备缩容至 %zu. \n",arr->size, arr->capacity / 4, new_capacity);

		resize_array(arr, new_capacity);
	}

	return 0;
}