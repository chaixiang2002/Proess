#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>
using namespace std;
 //实例化m对象，不要理解为定义变量
class plate{
private:
    int apple;
    int k_plate;
    int orange;

public:
    mutex m;
    plate(int k_plate,int apple,int orange)
        :k_plate(k_plate),apple(apple)
        ,orange(orange){}

}
void dad(&plate) {
  while (1) {
    at.lock();
    if (k_plate > 0) {
      --k_plate;
      p.unlock();
      ++apple;
    } else {
      p.unlock();
    }

    // usleep(500000);
  }
}

void mom() {
  while (1) {
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
  while (1) {
    a.lock();
    if (apple > 0) {
      apple--;
      a.unlock();
      ++k_plate;
    } else {
      a.unlock();
    }
    // usleep(700000);
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
  while (1) {
    cout << "k_plate:" << k_plate
        << "\tapple" << apple << "\torange"
        << orange
        << endl;
    // usleep(900000);
  }
}
int main() {

    plate myple(5,0,0);


  thread d(dad);
  thread s(son);
  thread m(monitor);
  d.join();
  s.join();
  m.join();
  return 0;
}