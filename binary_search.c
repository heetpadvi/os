binary search
#include<stdio.h>
3 #include<stdlib.h>
4 #include<unistd.h>
5 #include<sys/wait.h>
6
7 void bubbleSort(int arr[], int n) {
8 for (int i = 0; i < n - 1; i++) {
9 for (int j = 0; j < n - i - 1; j++) {
10 if (arr[j] > arr[j + 1]) {
11 int temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
12 }
13 }
14 }
15 }
16
17 int main() {
18 int arr[] = { 2, 3, 1, 9 }, key = 9;
19 int n = sizeof(arr) / sizeof(arr[0]);
20 pid_t pid = fork();
21
22 if (pid < 0)
23 exit(EXIT_FAILURE);
24
25 if (pid == 0) {
26
27 bubbleSort(arr, n);
28 printf("Sorted array: \n[ ");
29 for (int i = 0; i < n; i++) {
30 printf("%d ", arr[i]);
31 }
32 printf("]");
33
34 char *argv[n + 2];
35 for (int i = 0; i < n; i++) {
36 argv[i + 1] = malloc(sizeof(int));
37 sprintf(argv[i + 1], "%d", arr[i]);
38 }
39 sprintf(argv[n + 1], "%d", key);
40
41 argv[0] = "./binary";
42 execv(argv[0], argv);
43
44 } else // parent
45 wait(NULL);
46 return 0;
47 }


#include <stdio.h>
3 #include <stdlib.h>
4 #include <string.h>
5
6 int binarySearch(int arr[], int key, int start, int end) {
7 if (start <= end) {
8 int mid = start + (end - start) / 2;
9 if (arr[mid] == key) return mid;
10 else if (arr[mid] > key) return binarySearch(arr, key, start, mid - 1)
;
11 else return binarySearch(arr, key, mid + 1, end);
12 }
13 return -1;
14 }
15
16 int main(int argc, char* argv[]) {
17 if (argc < 3) return 1;
18
19 int arr[argc - 2];
20 for (int i = 0; i < argc - 2; i++) arr[i] = atoi(argv[i + 1]);
21
22 int key = atoi(argv[argc - 1]);
23 printf("Element %d found at %d.\n", key, binarySearch(arr, key, 0, argc-2)
);
24
25 return 0;
26 }
