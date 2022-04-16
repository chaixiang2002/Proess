#include <mutex>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>
#include <string>
//#include <windows.h>
struct Plate{
    std::string name;
    enum State{
        None,
        Apple,
        Orange
    }state=None;
};
class PlateHelper{
    Plate* plate;
    std::mutex* mutex;
public:
    PlateHelper(Plate* plate,std::mutex* mutex)
        :plate(plate)
        ,mutex(mutex){}

    ~PlateHelper(){
        if(mutex!=nullptr){
            mutex->unlock();
            plate=nullptr;
        }

    }
    bool apply_apple(){
        if(Plate::None==plate->state){
            plate->state=Plate::Apple;
            return true;
        }
        return false;
    }
    bool take_apple(){
        if(Plate::Apple==plate->state){
            plate->state=Plate::None;
            return true;
        }
        return false;
    }
    bool apply_orange(){
        if (Plate::None==plate->state) {
            plate->state=Plate::Orange;
            return true;
        }
        return false;
    }
    bool take_orange(){
        if(Plate::Orange==plate->state){
            plate->state=Plate::None;
            return true;
        }
        return false;
    }
    std::string& get_name(){
        return plate->name;
    }
    auto& get_state(){
        return plate->state;
    }
};

class PlateMutex{
    std::mutex mutex;
    Plate plate;
public:
    PlateMutex(const std::string& name){
        plate.name=name;
    }

    PlateHelper lock(){
        mutex.lock();
        return {&plate,&mutex};
    }
    std::pair<bool, PlateHelper> try_lock(){
        if(mutex.try_lock()){
            return {true,{&plate,&mutex}};
        }
        return {false,{nullptr,nullptr}};
    }
    auto lock_(){//
        mutex.lock();
        return plate.state;
    }
    void unlock_(){//
        mutex.unlock();
    }
};


int main(){
    PlateMutex plate1("a");
    PlateMutex plate2("b");
    PlateMutex plate3("c");
    PlateMutex plate4("d");

    std::vector<PlateMutex*>plates
    {
        &plate1,&plate2,&plate3,&plate4
    };

    auto father=[&](){
        while (true) {
            for(auto& plate:plates){
                auto sum=plate->try_lock();
                if(sum.first==true){
                    auto plate=sum.second;
                    if(plate.apply_apple()){
                        std::string tmp="Father apply apple sucessfully on "
                            +plate.get_name()+"\n";
                        std::cout<<tmp;
                        break;
                    }
                }
            }
        }
    };
    auto boy=[&](){
        while (true) {
        for(auto& plate:plates){
                auto sum=plate->try_lock();
                if(sum.first==true){
                    auto plate=sum.second;
                    if(plate.take_apple()){
                        std::string tmp="Boy take apple sucessfully on "
                            +plate.get_name()+"\n";
                        std::cout<<tmp;
                        break;
                    }
                }
            }
        }
    };
    auto mother=[&](){
        while (true) {
        for(auto& plate:plates){
                auto sum=plate->try_lock();
                if(sum.first==true){
                    auto plate=sum.second;
                    if(plate.apply_orange()){
                        std::string tmp="Mother apply orange sucessfully on "
                            +plate.get_name()+"\n";
                        std::cout<<tmp;
                        break;
                    }
                }
            }
        }
    };
    auto girl=[&](){
        while (true) {
        for(auto& plate:plates){
                auto sum=plate->try_lock();
                if(sum.first==true){
                    auto plate=sum.second;
                    if(plate.take_orange()){
                        std::string tmp="Girl take orange sucessfully on "
                            +plate.get_name()+"\n";
                        std::cout<<tmp;
                        break;
                    }
                }
            }
        }
    };

auto monitor_=[&](){
        while (true) {
            int k_plate=0,apple=0,orange=0;
            for(auto& plate:plates){
                auto sum=plate->try_lock();
                if(sum.first==true){
                    auto plate=sum.second;
                    if(plate.get_state()==Plate::None)
                        k_plate++;
                    else if (plate.get_state()==Plate::Apple)
                        apple++;
                    else
                        orange++;
                }
            }
            std::string ch =
                "\t \t \t \t \t \t k_plates: " + std::to_string(k_plate) +
                "\tapple: " + std::to_string(apple) + R"(orange: )" +
                std::to_string(orange) + "\n";
            std::cout<<ch;
        }
    };
    std::thread father_thread(father);
    std::thread boy_thread(boy);
    std::thread mother_thread(mother);
    std::thread girl_thread(girl);
    std::thread monitor_threag(monitor_);
    while (true) {}
    return 0;
}

