#include <iostream>

#define PS_CNT 4 // process count
#define RT_CNT 4 // resource type

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

int A[RT_CNT] = {3,2,1,3}; // available matrix

bool findState(int grant, int *process_state) {
  if (!process_state[grant]) return false;
  for (int i = 0; i < RT_CNT; i++) {
    if (R[grant][i] > A[i]) return false;
  }
  // process grant is granted the request
  // runs until process finishes
  for (int i = 0; i < RT_CNT; i++) {
    A[i] += P[grant][i];  // released resources added to available
    P[grant][i] = 0;   // release possessed resources
    R[grant][i] = 0;   // requests nothing
  }
  process_state[grant] = 0;
  std::cout << "Process " << grant << " finished!" << std::endl;
  std::cout << "=> Available resources: ";
  for (int i = 0; i < RT_CNT; i++) std::cout << A[i] << ' ';
  std::cout << std::endl;
  return true;
}

int main() {
  int process_cnt = PS_CNT;
  int process_state[PS_CNT];
  std::fill_n(process_state, PS_CNT, 1);
  bool locked = 0;
  while (process_cnt > 0 && locked == 0) {
    locked = 1;
    for (int i = 0; i < PS_CNT; i++) {
      if (!findState(i, process_state)) continue;
      else {
        locked = 0;
        process_cnt--;
        break;
      }
    }
  }
  std::cout << "==========================================" << std::endl;
  if (locked) {
    std::cout << "The state is unsafe!" << std::endl;
    for (int i = 0; i < PS_CNT; i++) {
      if (process_state[i] == 0) continue;
      std::cout << "Process " << i << " requires: ";
      for (int j = 0; j < RT_CNT; j++) std::cout << R[i][j] << ' ';
      std::cout << std::endl;
    }
  } else {
    std::cout << "All processes finished, the state is safe!" << std::endl;
  }
  return 0;
}
