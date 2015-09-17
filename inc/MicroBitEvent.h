#ifndef MICROBIT_EVENT_H
#define MICROBIT_EVENT_H

#include "mbed.h"

enum MicroBitEventLaunchMode
{
    CREATE_ONLY,                        
    CREATE_AND_QUEUE,
    CREATE_AND_FIRE
};

#define MICROBIT_EVENT_DEFAULT_LAUNCH_MODE     CREATE_AND_QUEUE

/**
  * Class definition for a MicrobitEvent
  * It represents a common event that is generated by the various components on the MB.
  */
class MicroBitEvent
{
    public:

    //These are public at the moment for backwards compatability with old code
    //will be refactored in the future!
    
    uint16_t source;         // ID of the MicroBit Component that generated the event e.g. MICROBIT_ID_BUTTON_A. 
    uint16_t value;          // Component specific code indicating the cause of the event.
    uint32_t timestamp;      // Time at which the event was generated. ms since power on.

    /**
      * Constructor. 
      * @param src ID of the MicroBit Component that generated the event e.g. MICROBIT_ID_BUTTON_A.
      * @param value Component specific code indicating the cause of the event.
      * @param mode optional definition of how the event should be processed after construction (if at all):
      *
      * CREATE_ONLY: MicroBitEvent is initialised, and no further processing takes place.
      * CREATE_AND_QUEUE: MicroBitEvent is initialised, and queued on the MicroBitMessageBus.
      * CREATE_AND_FIRE: MicroBitEvent is initialised, and its event handlers are immediately fired (not suitable for use in interrupts!).
      * 
      * Example: Create and launch an event using the default configuration
      * @code 
      * MicrobitEvent evt(id,MICROBIT_BUTTON_EVT_CLICK); 
      * @endcode
      *
      * Example: Create and launch an event and process all registered event handlers immediately.
      * @code 
      * MicrobitEvent evt(id,MICROBIT_BUTTON_EVT_CLICK,CREATE_AND_FIRE); 
      * @endcode
      */
   
    MicroBitEvent(uint16_t source, uint16_t value, MicroBitEventLaunchMode mode = MICROBIT_EVENT_DEFAULT_LAUNCH_MODE);  
    
    /**
      * Default constructor - initialises all values, and sets timestamp to the current time.
      */ 
    MicroBitEvent(); 

    /**
      * Fires the represented event onto the message bus using the default configuration.
      */
    void fire();

    /**
      * Fires the represented event onto the message bus.
      * @param mode Configuration of how the event is processed.
      */
    void fire(MicroBitEventLaunchMode mode);
};

/**
  * Enclosing class to hold a chain of events.
  */
struct MicroBitEventQueueItem
{
    MicroBitEvent evt;
    MicroBitEventQueueItem *next;

    /**
      * Constructor. 
      * Creates a new MicroBitEventQueueItem.
      * @param evt The event that is to be queued.
      */
    MicroBitEventQueueItem(MicroBitEvent evt);
};

#endif

