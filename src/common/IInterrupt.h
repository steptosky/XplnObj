#pragma once

/*
**  Copyright (C) 2018, StepToSky and FlightFactor
**  All rights reserved
**
**  Contacts: www.steptosky.com or www.flightfactor.aero
*/

#include <atomic>

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class IInterrupt {
public:
    virtual ~IInterrupt() = default;
    virtual bool isInterrupted() const = 0;
    virtual void interrupt(bool state) = 0;
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class NoInterrupt : public IInterrupt {
public:
    virtual ~NoInterrupt() = default;
    bool isInterrupted() const override { return false; }
    void interrupt(bool) override {}
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class DefaultInterrupt : public IInterrupt {
public:
    virtual ~DefaultInterrupt() = default;
    bool isInterrupted() const override { return mInterrupt.load(); }
    void interrupt(const bool state = true) override { mInterrupt.store(state); }
private:
    std::atomic_bool mInterrupt;
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
