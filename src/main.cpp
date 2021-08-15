
#include "../include/Session.h"
#include "iostream"

using namespace std;

int main(int argc, char** argv){

    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
    }

    Session sess(argv[1]);
    sess.simulate();
    return 0;
}

