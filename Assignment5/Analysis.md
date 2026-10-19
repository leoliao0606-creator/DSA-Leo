# Performance Analysis

**Pure Strassen is slower than conventional multiplication.** At n = 512, conventional took 0.54 s and Strassen (recursing down to 1x1) took 39.2 s. Strassen adds extra additions, splits and joins, and each one builds a new matrix. For tiny blocks the cost of runnningthose extra steps is likely outweighs the multiplication it saves.

**A hybrid of regular and strassen fixes this.** Strassen is used while the block size is above a threshold; at or below it, conventional multiplication is used. At n = 1024 (conventional: about 5.1 s):

| threshold | 2    | 4    | 8    | 16   | 32   | 64             | 128  | 256  | 512 |
| --------- | ---- | ---- | ---- | ---- | ---- | -------------- | ---- | ---- | --- |
| time (s)  | 59.9 | 18.4 | 7.25 | 4.03 | 3.03 | **2.86** | 3.04 | 3.33 | 3.8 |

- Best threshold was 64: about 1.8x faster than conventional.
- Too small a threshold means many recursion levels with heavy overhead. Too large means conventional multiplication on blocks that are still big enough for Strassen to help.
