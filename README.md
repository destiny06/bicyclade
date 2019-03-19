# Coucou

### For now server which is broadcasting messages from clients (chat)

### Compilation

#### Required

apt-get update  
apt-get upgrade  
apt-get install gcc g++ cmake python pkg-config  
apt-get install libboost-all-dev  
apt-get install libwebsocketpp-dev

#### How to compile

g++ -std=c++11 echo_client.cpp -lboost_system -lpthread -D_WEBSOCKETPP_CPP11_STL_ -o client  
g++ -std=c++11 broadcast_server.cpp -lboost_system -lpthread -D_WEBSOCKETPP_CPP11_STL_ -o server

### How to use the client

connect // to connect  
send <id> message // to send message  
close <id> reason // to close  
show <id> // to show stuff about the connect  
quit // to quit

And it should compile and work.

#### Normally not needed but we never know:

apt-get install libbz2-dev zlib1g-dev libssl-dev libstdc++6 libminiupnpc-dev libnatpmp-dev libtbb-dev libmaxminddb-dev libboost1.58-dev libboost-regex1.58 libboost-thread1.58 libboost-system1.58 libleveldb-dev libwebsocketpp-dev

#### To do

instruction to compile and run grpc (will include protocol buffer)  
create makefile  
send/receive basic protobuf message