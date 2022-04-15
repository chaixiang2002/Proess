#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
mutex p, a, o, at; //实例化m对象，不要理解为定义变量
int k_plate = 5;
int apple = 0;
int orange = 0;

void dad() {
  while (true) {
    // p.lock();
    // if (k_plate > 0) {
    //   --k_plate;
    //   p.unlock();
    //   ++apple;
    // } else {
    //   p.unlock();
    // }
    lock_guard<mutex> locker(p);
    --k_plate;
  }
}

void mom() {
  while (true) {
    p.lock();
    if (k_plate > 0) {
      --k_plate;
      p.unlock();
      ++orange;
    } else {
      p.unlock();
    }
  }
}
void son() {
  while (true) {
    a.lock();
    if (apple > 0) {
      apple--;
      a.unlock();
      ++k_plate;
    } else {
      a.unlock();
    }
  }
}
void nv() {
  while (true) {
    o.lock();
    if (orange > 0) {
      --orange;
      o.unlock();
      ++k_plate;
    } else {
      o.unlock();
    }
  }
}

void monitor() {
  while (true) {
    at.lock();
    cout << "k_plate:" << k_plate << "\tapple" << apple << "\torange" << orange
         << endl;
    at.unlock();
  }
}
int main() {
  // thread dads[2];
  // dads[1] = thread(dad);
  // dads[0] = thread(dad);
  // dads[1].join();
  // dads[0].join();
  // thread mom1(mom);
  // mom1.join();
  // thread child[20];
  // for (int i = 0; i < 20; ++i) {
  //   if (i < 10) {
  //     child[i] = thread(son);
  //   } else {
  //     child[i] = thread(nv);
  //   }
  //   child[i].join();
  // }
  // thread mm(monitor);
  // mm.join();

  thread dadd(dad);
  // thread ch(son);
  // ch.join();
  thread monn(monitor);
  monn.join();
  dadd.join();
}