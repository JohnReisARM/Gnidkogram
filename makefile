#################
.PHONY: clean
#################

COMPCXX=g++

CXXFLAGS=-ggdb3 -Wall 

CINCLUDES=

CXXSTD=-std=c++17

#################
CLINAME=client
SRVNAME=server

SRC_PATH=src

OBJ_PATH=obj

INCLUDED_FILE=

BUILD_PATH=build

CCSRC=main.cc

LIBFLAGS=$(shell pkg-config --libs sfml-network)
################

CCSRCS=$(addprefix $(SRC_PATH)/,$(CCSRC))

CCOBJS=$(addprefix $(OBJ_PATH)/,$(notdir $(CCSRCS:.cc=.o)))

TARGETS=$(addprefix $(BUILD_PATH)/$(PRJNAME)_,$(notdir $(CCSRCS:.cc=))) 

################

all: client server
	@if [ ! -d $(BUILD_PATH) ]; then mkdir $(BUILD_PATH); fi
	$(COMPCXX) $(LDLIBS) -o $(BUILD_PATH)/client $(OBJ_PATH)_client/client.o $(LIBFLAGS) 
	$(COMPCXX) $(LDLIBS) -o $(BUILD_PATH)/server $(OBJ_PATH)_server/server.o $(LIBFLAGS)

run_client: client
	./$(BUILD_PATH)/client

run_server: server
	./$(BUILD_PATH)/server

client: client_app.o
	@if [ ! -d $(BUILD_PATH) ]; then mkdir $(BUILD_PATH); fi
	$(COMPCXX) $(LDLIBS) -o $(BUILD_PATH)/client $(OBJ_PATH)_client/client.o $(LIBFLAGS) 

server: server_app.o
	@if [ ! -d $(BUILD_PATH) ]; then mkdir $(BUILD_PATH); fi
	$(COMPCXX) $(LDLIBS) -o $(BUILD_PATH)/server $(OBJ_PATH)_server/server.o $(LIBFLAGS)

client_app.o: client/client.cc
	@if [ ! -d $(OBJ_PATH)_client ]; then mkdir $(OBJ_PATH)_client; fi
	$(COMPCXX) $(CXXFLAGS) $(CINCLUDES) $(CXXSTD) -c $< -o $(OBJ_PATH)_client/client.o


server_app.o: server/server.cc 
	@if [ ! -d $(OBJ_PATH)_server ]; then mkdir $(OBJ_PATH)_server; fi
	$(COMPCXX) $(CXXFLAGS) $(CINCLUDES) $(CXXSTD) -c $< -o $(OBJ_PATH)_server/server.o

####################

clean:
	@rm -rvf $(OBJ_PATH) $(BUILD_PATH) .*~ *~ \#*\# .d **/*~ **/*#
	@rm -rvf $(OBJ_PATH)_server $(OBJ_PATH)_client


prepareinstall:
	sudo echo "Включем судо"
	echo "y" | sudo apt install g++
	echo "y" | sudo apt install pkg-config
	echo "y" | sudo apt install libsfml-dev
	@echo "\n\nЕсли что-то встанет не так, то нужно "\
	"исправить направления к исходникам. Так что "\
	"стоит проверить где лежит SFML"\
	"\n\n"
