int getMaximum(int arr[]) {
int n = sizeof(arr)/sizeof(arr[0]);
// Find the maximum value of arr
int max = arr[0];
for (int i = 1; i < n; i++) {
if (arr[i] > max) {
max = arr[i];
}
}
// Perform the operation until the maximum value is minimized
while (max > 1) {
for (int i = n - 1; i >= 2; i--) {
if (arr[i] > 1) {
arr[i - 1]++;
arr[i]--;
}
}
// Find the new maximum value of arr
max = arr[0];
for (int i = 1; i < n; i++) {
if (arr[i] > max) {
max = arr[i];
}
}
}
// Return the minimized maximum value
return max;
}



