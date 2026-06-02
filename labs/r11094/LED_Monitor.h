#pragma once

#include "Monitor.h"

class LED_Monitor : public Monitor {
public:
    LED_Monitor() {
        // TODO: print "LED_Monitor constructor"
        cout<<"LED_Monitor constructor"<<endl;
    }

    ~LED_Monitor() override {
        // TODO: print "LED_Monitor destructor"
        cout<<"LED_Monitor destructor"<<endl;
    }

    void out() const override {
        // TODO: print "LED_Monitor rendering"
        cout<<"LED_Monitor rendering"<<endl;
    }
};
