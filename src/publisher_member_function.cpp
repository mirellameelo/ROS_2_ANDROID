// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


using namespace std;
// mspm

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

#include "rclcpp/rclcpp.hpp"
 
int main(int argc, char *argv[]) {


  int listening = socket(AF_INET, SOCK_STREAM, 0);

  if (listening == -1)
  {
      cerr << "Can't create a socket! Quitting" << endl;
      return -1;
  }

  // Bind the ip address and port to a socket
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(6000);
  inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

  bind(listening, (sockaddr*)&hint, sizeof(hint));

  // Tell Winsock the socket is for listening
  listen(listening, SOMAXCONN);

  // Wait for a connection
  sockaddr_in client;
  socklen_t clientSize = sizeof(client);

  int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

  char host[NI_MAXHOST];      // Client's remote name
  char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on

  memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
  memset(service, 0, NI_MAXSERV);
  // Close listening socket
  close(listening);
 
  // While loop: accept and echo message back to client
  char buf[4096];

  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("minimal_publisher");
  auto message = std_msgs::msg::String();
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  publisher_ = node->create_publisher<std_msgs::msg::String>("topic", 10);



while (true)
    {
        memset(buf, 0, 4096);
 
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            //cout << "Error in recv(). Quitting" << endl;
            break;
        }
 
        if (bytesReceived == 0)
        {
            //cout << "Client disconnected " << endl;
            break;
        }
        //RCLCPP_INFO(node->get_logger(), buf);
        message.data = buf;
        RCLCPP_INFO(node->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
         
        // Echo message back to client
        //send(clientSocket, buf, bytesReceived + 1, 0);
    }


 
  rclcpp::shutdown();
  return 0;
}