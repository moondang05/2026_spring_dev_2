#pragma once

#include <iostream>
using namespace std;

class OutputDevice {
public:
    OutputDevice() {
        // TODO: print "OutputDevice constructor"
        cout<<"OutputDevice constructor"<<endl;
    }

    virtual ~OutputDevice() {
        // TODO: print "OutputDevice destructor"
        cout<<"OutputDevice destructor"<<endl;
    }

    virtual void out() const = 0;
};
