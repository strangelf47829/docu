


cc = gcc
cx = g++
gg = gracp

CFLAGS = -c -g
CXFLAGS = -c -g
GGFLAGS = -c

src = src
bin = bin
lib = lib
inc = inc

tgt = docu
installLocation = /var/www/html/docu/tests/index.html


all: clean src/html/html src/app
#	$(cx) -E $(wildcard $(lib)/*.o)
	$(cx) -o $(bin)/$(tgt).out $(wildcard $(lib)/*.o)
#	gdb $(bin)/$(tgt).out
#	clear
	$(bin)/$(tgt).out
	sudo cp web.html $(installLocation)
	cat web.html

clean:
	clear

%: %.cpp
	$(cx) $(CXFLAGS) $^ -o $(lib)/$(notdir $@.o) -I $(inc)/ -L $(lib)

%: %.c
	$(cc) $(CFLAGS) $^ -o $(lib)/c_$(notdir $@.o) -I $(inc)/ -L $(lib)

%.c: %.cpp
	@ mkdir temp
	$(gg) $(GGFLAGS) $^ temp/$(notdir $(patsubst %.cpp, %.c, $@))
	@ cp temp/$(notdir $(patsubst %.c, %.c, $@)) $(src)/auto/$(notdir $(patsubst %.c, %.c, $@))
	@ rm temp/$(notdir $(patsubst %.c, %.c, $@))
	@ cp temp/$(notdir $(patsubst %.c, %.h, $@)) $(inc)/$(notdir $(patsubst %.c, %.h, $@))
	@ rm temp/$(notdir $(patsubst %.c, %.h, $@))
	@ rm -r temp
	@ echo [make]: Files copied successfuly
