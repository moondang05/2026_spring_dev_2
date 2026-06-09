#pragma once

#include "Monitor.h"

class LCD_Monitor : public Monitor {
public:
    LCD_Monitor() {
        // TODO: print "LCD_Monitor constructor"
        cout<<"LCD_Monitor constructor"<<endl;
    }

    ~LCD_Monitor() override {
        // TODO: print "LCD_Monitor destructor"
        cout<<"LCD_Monitor destructor"<<endl;
    }

    void out() const override {
        // TODO: print "LCD_Monitor rendering"
        cout<<"LCD_Monitor rendering"<<endl;
    }
};
