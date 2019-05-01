#
# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CXX = g++
CXXFLAGS += -std=c++11
CPPFLAGS += `pkg-config --cflags protobuf`

LDFLAGS += `pkg-config --libs protobuf` -lboost_system -lpthread -D_WEBSOCKETPP_CPP11_STL_
PROTOC = protoc

PROTOS_PATH = ./protos

vpath %.proto $(PROTOS_PATH)

all: system-check console-client test-client server

console-client: generated/common.pb.o generated/gameactions.pb.o generated/clientactions.pb.o generated/playeractions.pb.o generated/serveractions.pb.o generated/bicyclade.pb.o bom/Client.o client/network/MockUpSocketClient.o client/network/WebSocketClient.o client/application/BasicClientApplication.o client/lobby/BasicLobbyClient.o client/game/BasicGameClient.o client/CommandLineClient.o
	$(CXX) $^ $(LDFLAGS) -o client/console-client

test-client: generated/common.pb.o generated/gameactions.pb.o generated/clientactions.pb.o generated/playeractions.pb.o generated/serveractions.pb.o generated/bicyclade.pb.o bom/Client.o client/network/MockUpSocketClient.o client/network/WebSocketClient.o client/application/BasicClientApplication.o client/lobby/BasicLobbyClient.o client/game/BasicGameClient.o client/SimulatedClientSample.o
	$(CXX) $^ $(LDFLAGS) -o client/test-client

server: generated/common.pb.o generated/gameactions.pb.o generated/clientactions.pb.o generated/playeractions.pb.o generated/serveractions.pb.o generated/bicyclade.pb.o server/WebsocketServer.o bom/Client.o bom/Player.o server/Server.o server/main.o
	$(CXX) $^ $(LDFLAGS) -o server/server

.PRECIOUS: generated/%.pb.cc
generated/%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=./generated $<

clean:
	rm -f generated/* server/*.o client/*o client/*/*o bom/*.o client/old-client client/console-client client/test-client server/server


# The following is to test your system and ensure a smoother experience.
# They are by no means necessary to actually compile a grpc-enabled software.

PROTOC_CMD = which $(PROTOC)
PROTOC_CHECK_CMD = $(PROTOC) --version | grep -q libprotoc.3
HAS_PROTOC = $(shell $(PROTOC_CMD) > /dev/null && echo true || echo false)
ifeq ($(HAS_PROTOC),true)
HAS_VALID_PROTOC = $(shell $(PROTOC_CHECK_CMD) 2> /dev/null && echo true || echo false)
endif

SYSTEM_OK = false
ifeq ($(HAS_VALID_PROTOC),true)
SYSTEM_OK = true
endif

system-check:
ifneq ($(HAS_VALID_PROTOC),true)
	@echo " DEPENDENCY ERROR"
	@echo
	@echo "You don't have protoc 3.0.0 installed in your path."
	@echo "Please install Google protocol buffers 3.0.0 and its compiler."
	@echo "You can find it here:"
	@echo
	@echo "   https://github.com/google/protobuf/releases/tag/v3.0.0"
	@echo
	@echo "Here is what I get when trying to evaluate your version of protoc:"
	@echo
	-$(PROTOC) --version
	@echo
	@echo
endif
ifneq ($(SYSTEM_OK),true)
	@false
endif
