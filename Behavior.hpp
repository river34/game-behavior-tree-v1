//
//  Behavior.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Behavior_h
#define Behavior_h

#include "Status.hpp"
#include "Node.hpp"
#include "Task.hpp"

namespace BT
{
    class Behavior
    {
    protected:
        Task* m_pTask;
        Node* m_pNode;
        Status m_eStatus;
        
    public:
        Behavior() : m_eStatus(Status::BH_INVALID) { }
        virtual ~Behavior() { }
        virtual void onInitialize() { } /* called once immediately before the first call to onUpdate() */
        virtual Status onUpdate() = 0;  /* called once for each time the BT is updated */
        virtual void onTerminate(Status _statues) { } /* called once immediately after the last call to onUpdate */
        Status tick() /* single entry point for updating this behavior */
        {
            if (m_eStatus != Status::BH_RUNNING)
                onInitialize();
            
            m_eStatus = onUpdate();
            
            if (m_eStatus != Status::BH_RUNNING)
                onTerminate(m_eStatus);
            
            return m_eStatus;
        }
        inline Status getStatus() { return m_eStatus; }
        inline bool isTerminated() const { return m_eStatus == Status::BH_SUCCESS || m_eStatus == Status::BH_FAILURE; } /* success or failed */
        inline void reset() { m_eStatus = Status::BH_INVALID; }
        inline void abort() { onTerminate(Status::BH_ABORTED); m_eStatus = Status::BH_ABORTED; }
    };
}

#endif /* Behavior_h */
