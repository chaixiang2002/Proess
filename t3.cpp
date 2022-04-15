#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
mutex p; //实例化m对象，不要理解为定义变量
int k_p = 0;
void proc1() {
  while (1) {
    lock_guard<mutex> g1(p);
    cout << "proc1函数正在改写a" << endl;
    --k_p;
  }
} //自动解锁

void proc2() {
  while (1) {
    lock_guard<mutex> g2(p); //自动锁定
    cout << "proc2函数正在a///////////////////" << endl;
    cout << "原始a为" << k_p << endl;
  }

} //自动解锁
int main() {
  thread proc11(proc1);
  thread proc22(proc2);
  proc11.join();
  proc22.join();
  return 0;
}