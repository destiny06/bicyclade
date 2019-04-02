# Bicyclades
A Cyclades board game clone

### Currently working
Server broadcasting messages from clients (chat)

#### Dependencies
For ubuntu:
- apt-get update  
- apt-get upgrade  
- apt-get install gcc g++ cmake python pkg-config autoconf automake libtool curl libprotobuf-dev protobuf-compiler libboost-all-dev libwebsocketpp-dev

#### Compilation

cd src/  
make

### How to use the client

```
connect //to connect  
send <id> message //to send message  
close <id> reason //to close  
show <id> //to show stuff about the connect  
quit //to quit
```

#### Extra dependencies (normally not needed but we never know)

apt-get install libbz2-dev zlib1g-dev libssl-dev libstdc++6 libminiupnpc-dev libnatpmp-dev libtbb-dev libmaxminddb-dev libboost1.58-dev libboost-regex1.58 libboost-thread1.58 libboost-system1.58 libleveldb-dev libwebsocketpp-dev

#### TODO

instruction to compile and run grpc (will include protocol buffer)  
create makefile  
send/receive basic protobuf message
