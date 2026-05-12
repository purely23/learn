#include <stddef.h>

typedef struct {
	int id;
	char name[50];
} Student;

typedef Student Data;  //typedef是给一个已经存在的数据类型起一个新名字

typedef struct {
	Data* data;
	size_t size;
	size_t capacity;
} DynamicArray;

//创建并初始化一个动态数组
DynamicArray* create_array(size_t initial_capacity);

//销毁数组，释放内存
void destory_array(DynamicArray* arr);

//在数组末尾追加元素
void array_append(DynamicArray* arr, Data value);

//读取指定的索引元素
//返回一个指针,以便能够检查是否成功，若索引无效，返回NULL
Data* array_read(DynamicArray* arr, size_t index);

//更新指定索引的元素
//返回0表示成功，返回-1表示失败
int array_update(DynamicArray* arr, size_t index, Data value);

int array_insert(DynamicArray* arr, size_t index, Data value);

//删除指定索引的元素
int array_delete(DynamicArray* arr, size_t index);

void print_array(const DynamicArray* arr, void(*print_func) (const void* data));