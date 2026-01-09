
// this is a simple gazebo transport subscriber node to receive gz.msg.Int32 msg
#include <google/protobuf/message.h>
#include <iostream>
#include <string>
#include <gz/transport.hh>

void cb(const google::protobuf::Message &_msg,
        const gz::transport::MessageInfo &_info)
{
  std::cout << "Topic: [" << _info.Topic() << "]" << std::endl;
  std::cout << _msg.DebugString() << std::endl;
}
 
int main(int argc, char **argv)
{
  gz::transport::Node node;
  std::string topic = "/joy";
  // Subscribe to a topic by registering a callback.
  if (!node.Subscribe(topic, cb))
  {
    std::cerr << "Error subscribing to topic [" << topic << "]" << std::endl;
    return -1;
  }
 
  // Zzzzzz.
  gz::transport::waitForShutdown();
 
  return 0;
}