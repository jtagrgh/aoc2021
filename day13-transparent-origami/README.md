This one was gentle and relaxing.

Used a nice way for making bigger than stack allowed arrays,

Instead of: `int arr[SIZE][SIZ];`
You can do: 
```
int* arr[SIZE];
for (int i = 0; i < SIZE; i++) {
    arr[i] = malloc(sizeof(int) * SIZE);
}

