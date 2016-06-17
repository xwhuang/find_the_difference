GCC		:= gcc
YACC	:= bison -d -v 
LEX		:= flex
#------------------------------------------------------------
top      := ${PWD}
target   := cli
CLI_INC  := lib/include
CLI_OBJS := parser.tab.o lexer.o banner.o util.o
C_FLAGS  := -O2 -MD -W -Wno-unused-parameter -Wunused-result\
	 -I$(CLI_INC)	
LD_FLAGS := -Llib/lib  -lreadline -ltermcap

PRE_LIST := parser.tab.c lexer.c
CLEAN_LIST := $(CLI_OBJS) $(target)

DEPS_$(d) := $(CLI_OBJS:.o=.d)
CLEAN_LIST += $(DEPS_$(d))
#------------------------------------------------------------

.PHONY: prepare clean
.SECONDARY: parser.tab.c lexer.c

#prepare:$(PRE_LIST)

all:prepare $(target)

-include $(DEPS_$(d))

dir:=$(top)/lib
include $(dir)/lib.mk

$(target):$(CLI_OBJS)
	$(GCC) -o $@ $^ $(LD_FLAGS) 

%.c:%.l
	$(LEX) -t $< > $@

%.tab.c:%.y
	$(YACC) $< -o $@

%.o:%.c
	$(GCC) $(C_FLAGS) -c $<

prepare:$(PRE_LIST)
#-include $(DEPS_$(d))

clean:
	rm -rf $(CLEAN_LIST)
	rm -f parser.tab.* lexer.c parser.output
