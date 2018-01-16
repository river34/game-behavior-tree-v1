//
//  Repeater.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  RepeatDecorator is a Decorator that executes it child
//      until a limit is reached.
//      if the child fails, the decorator fails;
//      if the child succeeds, it is executed again in the same
//      update after the reset.

#ifndef Repeat_h
#define Repeat_h

#include "Decorator.hpp"
#include "Behavior.hpp"

namespace BT
{
    class Repeater : public Decorator
    {
    private:
        unsigned int m_iCounter;
        unsigned int m_iLimit;
        
    public:
        Repeater(Behavior* _child) : Decorator(_child) { }
        virtual ~Repeater() { }
        inline void onInitialize() { m_iCounter = 0; }
        inline void setLimit(unsigned int _limit) { m_iLimit = _limit; }
        Status update()
        {
            for (;;)
            {
                m_pChild->tick();
                if (m_pChild->getStatus() == Status::BH_RUNNING) break;
                if (m_pChild->getStatus() == Status::BH_FAILURE) return Status::BH_FAILURE;
                if (++m_iCounter == m_iLimit) return Status::BH_SUCCESS;
                m_pChild->reset();
            }
            return Status::BH_INVALID;
        }
    };
}


#endif /* Repeat_h */
