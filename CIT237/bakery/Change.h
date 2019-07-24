#ifndef NEWMONEYCLASS_CHANGE_H
#define NEWMONEYCLASS_CHANGE_H
#include <iostream>
using namespace std;

class Change {
private:

    float change;
    const int SIZE = 5;
    int *change_count = nullptr;
public:
    void setChange(float ch){
        if(ch > 0)
            change = ch;
    }

    void getChange(float chng);
    void toString(){
        for (int i = 0; i < 5; i++) {
            cout << change_count[i] << ',';
        }
    }

    Change(){
        change = 0;
    }
    ~Change(){
        delete(change_count);
    }
};


#endif //NEWMONEYCLASS_CHANGE_H
