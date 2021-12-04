Orignal solution uses vairable size arrays by copying over and using heap control, the rework uses a linked list

## Interesting time comparison:

### day3-binary-diagnostic 👉 time ./pt2.out
out: 1800151

./pt2.out  0.00s user 0.00s system 2% cpu 0.192 total

### day3-binary-diagnostic 👉 time ./pt2-rework1.out
out: 1800151

./pt2-rework1.out  0.00s user 0.00s system 69% cpu 0.008 total


