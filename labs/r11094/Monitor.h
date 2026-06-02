#pragma once

#include "OutputDevice.h"

class Monitor : public OutputDevice {
public:
    Monitor() {
        // TODO: print "Monitor constructor"
        cout<<"Monitor constructor"<<endl;
    }

    ~Monitor() override {
        // TODO: print "Monitor destructor"
        cout<<"Monitor destructor"<<endl;
    }

    void out() const override {
        // TODO: print "Monitor rendering"
        cout<<"Monitor rendering"<<endl;
    }
};
