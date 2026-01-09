
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <gz/msgs/stringmsg.pb.h>

#include <gz/transport/CIface.h>
#include <atomic>
#include <chrono>
#include <csignal>
#include <string>
#include <thread>
#include <gz/msgs.hh>
#include <gz/transport.hh>

#include <gz/msgs/int32.pb.h>
/**
 * Reads a joystick event from the joystick device.
 *
 * Returns 0 on success. Otherwise -1 is returned.
 */

// Below are the standard namespaces to shorten the code.
And
using namespace std;
using namespace std::chrono_literals;
static std::atomic<bool> g_terminatePub(false);
 
 // node msg is created.
 // below is the struct for the joystick values create
 // This node only uses the button values for this node but you can use more if you want to
 //but i recommend to  look for this repo as a example to add more functionality: https://github.com/t-kiyozumi/joystick_on_linux.git

 void signal_handler(int _signal)
{
  if (_signal == SIGINT || _signal == SIGTERM)
    g_terminatePub = true;
}

 typedef struct
{
  uint16_t X;
  uint16_t Y;
  uint16_t A;
  uint16_t B;
  uint16_t LB;
  uint16_t LT;
  uint16_t RB;
  uint16_t RT;
  uint16_t start;
  uint16_t back;
  int16_t axes1_x;
  int16_t axes1_y;
  int16_t axes0_x;
  int16_t axes0_y;
} controler_state;

void write_controler_state(controler_state *controler, js_event event) // this fuction writes the controller state and publish the node
{
     gz::transport::Node node;
  std::string topic = "/joy";

auto pub = node.Advertise<gz::msgs::Int32>(topic);
  gz::msgs::Int32 msg;
  msg.set_data(50);
 
 
 

  switch (event.type)
  {
  case JS_EVENT_BUTTON:


       
    if (event.number == 1)
    {
      controler->B = event.value;

     
 msg.set_data(30);
 pub.Publish(msg);
 cout << "the button" <<"B"<<"sends model backwards" << endl;
}
    if (event.number == 0)
    {
      controler->A = event.value;
    
     msg.set_data(50);
        pub.Publish(msg);
cout << "the button" <<"A"<<"sends model to stop" << endl;

    }
    if (event.number == 3)
    {
      controler->X = event.value;

 
     msg.set_data(0);
        pub.Publish(msg);
        cout << "the button" <<"x"<<"does nothing at the moment but you can decide for yoursel" << endl;
    }
    if (event.number == 4)
    {
      controler->Y = event.value;
    
  
     msg.set_data(40);
        pub.Publish(msg);
    cout << "the button" <<"A"<<"sends model forwards" << '\n';
    }
         if (event.number == 6)
    {
      controler->LB = event.value;
    
  
     msg.set_data(20);
        pub.Publish(msg);
       cout << "the button" <<"LB"<<"sends model leftwards" << '\n';
    }
    if (event.number == 7)
    {
      controler->RB = event.value;

     msg.set_data(10);
        pub.Publish(msg);
cout << "the button" <<"RB"<<"sends model to rightwards" << '\n'; }



  
    }}

int main(int argc, char * argv[])
{
   // Install a signal handler for SIGINT and SIGTERM.
  std::signal(SIGINT,  signal_handler);
  std::signal(SIGTERM, signal_handler);
  // The basics for the joystick are set below
  int fd = open("/dev/input/js0", O_RDONLY); 
  struct js_event event;
  controler_state *controler;
  controler = (controler_state *)malloc(sizeof(controler_state));


  while (1) // now the code publish msgs created by a button presses in a loop.
  {
    read(fd, &event, sizeof(event));
    write_controler_state(controler, event);
  

     usleep(1000);

  
  

   }
return 0;
}
  
