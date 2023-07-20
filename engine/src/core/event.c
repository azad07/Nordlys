/**
 * @file event.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-07-19
 * 
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 * 
 */

 #include "core/event.h"

 #include "core/nmemory.h"
 #include "core/logger.h"
 #include "core/asserts.h"
 #include "container/darray.h"
#include "logger.h"

 typedef struct registered_event
 {
    void* listener;
    PFN_on_event callback;
 }registered_event;

 typedef struct event_code_entry
 {
    registered_event* events;
 }event_code_entry;

/* Should be more than enough code. */
 #define MAX_MESSAGE_CODES 16384

 /* State structure. */
 typedef struct event_system_state
 {
    /* Lookup table for event codes. */
    event_code_entry registered[MAX_MESSAGE_CODES];
 }event_system_state;

 /**
  * Event system internal state.
  */

  static b8 is_initialized = FALSE;
  static event_system_state state;

  b8 event_initialize()
  {
    if( is_initialized == TRUE)
    {
        return FALSE;
    }

    is_initialized = FALSE;
    nzero_memory(&state, sizeof(state));
    is_initialized = TRUE;

    NDEBUG("Event System Initialized.");

    return TRUE;
  }

void event_shutdown()
{
   /* Free the events arrays. Objects pointed to should be destroyed on their own. */
   for(u16 i=0; i < MAX_MESSAGE_CODES; ++i)
   {
      if(state.registered[i].events != 0)
      {
         darray_destroy(state.registered[i].events);
         state.registered[i].events = NULL;
      }
   }
}

NAPI b8 event_register(u16 code, void* listener_instance, PFN_on_event on_event)
{
   NASSERT_MSG(on_event, "event callback function should not be NULL.");
   if(is_initialized == FALSE)
   {
      NWARN("Event system is not initialized. call event_initialized.");
      return FALSE;
   }

   /* Initialized dynamic array to track all the listener for the event. */
   if(state.registered[code].events == NULL)
   {
      state.registered[code].events = darray_create(registered_event);
   }

   /* events with duplicate listener/callback will not be registered again. */
   u64 registered_event_count = darray_length(state.registered[code].events);
   for(u64 i = 0; i < registered_event_count; ++i)
   {
      if(state.registered[code].events[i].listener == listener_instance)
      {
         NWARN("Listener already registered for the event. Duplicate registered not allowed.");
         return FALSE;
      }
   }

   /* no duplicate found. proceed with registration. */
   registered_event event;
   event.listener = listener_instance;
   event.callback = on_event;
   darray_push(state.registered[code].events, event);

   return TRUE;
}

b8 event_unregister(u16 code, void* listener_instance, PFN_on_event on_evnet)
{
   if(is_initialized == FALSE)
   {
      NWARN("Event system is not initialized. unregistration called with even registering.");
      return FALSE;
   }

   /* nothing is registered for the code, boot out. */
   if(state.registered[code].events == NULL)
   {
      NWARN("There is no listener for the code. %d", code);
      return FALSE;
   }

   u64 registered_events_count = darray_length(state.registered[code].events);
   for(u64 i = 0; i<registered_events_count; ++i)
   {
      registered_event e = state.registered[i].events[i];
      if(e.listener == listener_instance && e.callback == on_evnet)
      {
         /* found, remove it. */
         registered_event popped_event;
         darray_pop_at(state.registered[code].events, i, &popped_event);
         return TRUE;
      }
   }

   /* Not Fount. */
   return FALSE;
}

b8 event_fire(u16 code, void* sender, event_context eContext)
{
   if(is_initialized == FALSE)
   {
      NWARN("Event system is not initialized. call event_initialized.");
      return FALSE;
   }

   /* If nothing is registered for the code, boot out. */
   if(state.registered[code].events == NULL)
   {
      return FALSE;
   }

   u64 registered_events_count = darray_length(state.registered[code].events);
   for(u64 i = 0; i < registered_events_count; ++i)
   {
      registered_event e = state.registered[code].events[i];
      if(e.callback(code, sender, e.listener, eContext))
      {
         /* Message has been handled, do not send to other listener. */
         return TRUE;
      }
   }

   /* Not Found. */
   return FALSE;
}
