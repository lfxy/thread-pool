EXEC = thp

#MD5_LIB = libmd5hash
#FNV_LIB = libfnvhash

PLATFORM := linux

SRC_DIR := $(shell pwd)/

#vpath %.cpp  $(SRC_DIR)fnv_hash
#vpath %.cpp  $(SRC_DIR)md5_hash

#FNV_HASH_SRC = \
#  hash_32.cpp \
   

#MD5_HASH_SRC = md5.cpp 
  
COMMON_SRC = \
  main.cpp \
  TaskQueue.cpp \
  ThreadPool.cpp
  
CPPFLAGS = -DLinux
CXXFLAGS += -g -I./ -lboost_system -lboost_thread

#MD5_HASH_OBJS := $(patsubst %.cpp, %.o, $(MD5_HASH_SRC))

#FNV_HASH_OBJS += $(patsubst %.cpp, %.o, $(FNV_HASH_SRC))

COMMON_OBJS += $(patsubst %.cpp, %.o, $(COMMON_SRC))

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

all: $(COMMON_OBJS)
	$(CXX) -o $(EXEC) $(COMMON_OBJS) $(CXXFLAGS)
	@echo "Done!"
 
#lib: $(MD5_HASH_OBJS) $(FNV_HASH_OBJS) 
# rm -rf lib
# mkdir lib
# ar rc lib/$(MD5_LIB).a $(MD5_HASH_OBJS)
# ar rc lib/$(FNV_LIB).a $(FNV_HASH_OBJS)
 
  
.PHONY : clean 
clean:
	rm -f *.o
	rm -f $(EXEC)
	rm -f $(EXEC).exe
	rm -rf lib
