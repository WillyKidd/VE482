# VE482 hw5 ex 3

## Banker's Algorithm

### Usage

`banker.cpp` implements the banker's algorithm to see whether a state is safe or not. The algorithm runs on a case where 4 processes are competing for 4 different resources, and the default case are defined by the maximum, request, possess and available matrices as follows.

```c++
int M[PS_CNT][RT_CNT] = {
  {7,5,2,4},
  {3,3,2,3},
  {6,2,3,4},
  {10,3,4,2}
}; // maximum matrix

int R[PS_CNT][RT_CNT] = {
  {6,4,1,3},
  {1,3,0,2},
  {3,1,1,2},
  {9,1,0,0}
}; // request matrix

int P[PS_CNT][RT_CNT] = {
  {1,1,1,1},
  {2,0,2,1},
  {3,1,2,2},
  {1,2,4,2}
}; // possess matrix

```

You may modify the values to do further testing. To build and run,

```shell
make
./banker

```





