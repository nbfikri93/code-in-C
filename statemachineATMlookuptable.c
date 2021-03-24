/*How to implement finite state machine in C by AMLENDRA*/
/*https://aticleworld.com/state-machine-using-c/*/
/*Edited by me to add functionality to ReadEvent function and make it compilable*/

#include <stdio.h>

//Different state of ATM machine
typedef enum
{
    Idle_State,
    Card_Inserted_State,
    Pin_Eentered_State,
    Option_Selected_State,
    Amount_Entered_State,
    last_State,
} eSystemState;

//Different type events
typedef enum
{
    Card_Insert_Event,
    Pin_Enter_Event,
    Option_Selection_Event,
    Amount_Enter_Event,
    Amount_Dispatch_Event,
    last_Event,
} eSystemEvent;

//typedef of 2d array
typedef eSystemState (*const afEventHandler[last_State][last_Event])(void);
//typedef of function pointer
typedef eSystemState (*pfEventHandler)(void);

//function call to dispatch the amount and return the ideal state
eSystemState AmountDispatchHandler(void)
{
    return Idle_State;
}

//function call to Enter amount and return amount enetered state
eSystemState EnterAmountHandler(void)
{
    return Amount_Entered_State;
}

//function call to option select and return the option selected state
eSystemState OptionSelectionHandler(void)
{
    return Option_Selected_State;
}

//function call to enter the pin and return pin entered state
eSystemState EnterPinHandler(void)
{
    return Pin_Eentered_State;
}

//function call to processing track data and return card inserted state
eSystemState InsertCardHandler(void)
{
    return Card_Inserted_State;
}

eSystemEvent ReadEvent()
{
    //the event shall be invoked by the user choice
    //the event can read from the user input such as button/screen touch
    //in this example, we only set the event to the first event
    return Card_Insert_Event;
}

int main(int argc, char *argv[])
{
    eSystemState eNextState = Idle_State;
    eSystemEvent eNewEvent;
    
    // Table to define valid states and event of finite state machine
    static afEventHandler StateMachine =
    {
        [Idle_State] ={[Card_Insert_Event]= InsertCardHandler },
        [Card_Inserted_State] ={[Pin_Enter_Event] = EnterPinHandler },
        [Pin_Eentered_State] ={[Option_Selection_Event] = OptionSelectionHandler},
        [Option_Selected_State] ={[Amount_Enter_Event] = EnterAmountHandler},
        [Amount_Entered_State] ={[Amount_Dispatch_Event] = AmountDispatchHandler},
    };
    
    while(1)
    {
        // assume API to read the next event
        eSystemEvent eNewEvent = ReadEvent();
        //Check NULL pointer and array boundary
        if( ( eNextState < last_State) && (eNewEvent < last_Event) && StateMachine[eNextState][eNewEvent]!= NULL)
        {
            printf("Current state is : %d\n", eNextState);
            // function call as per the state and event and return the next state of the finite state machine
            eNextState = (*StateMachine[eNextState][eNewEvent])();
            printf("Next state is : %d\n", eNextState);
        }
        else
        {
            //Invalid
        }
    }
    
    return 0;
}
