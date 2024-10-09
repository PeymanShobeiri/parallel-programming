JAVA_HOME = /usr/lib/jvm/java-11-openjdk-amd64
SIMGRID_PATH = /home/peyman/Desktop/simgrid/install

CC = g++
CFLAGS = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(SIMGRID_PATH)/include -fPIC
LDFLAGS = -shared -o libTopologyBuilder.so
LIBS = -L$(SIMGRID_PATH)/lib -lsimgrid

# Source and Object files
SRCS = src/main/jni/TopologyBuilder.cpp
OBJS = src/main/jni/TopologyBuilder.o

all: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS)

src/main/jni/%.o: src/main/jni/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) libTopologyBuilder.so

