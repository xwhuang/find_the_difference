sp              :=  $(sp).x
dirstack_$(sp)  :=  $(d)
d               :=  $(dir)
#------------------------------------------------------------

PREFIX_DIR := $(top)/lib

####readline
READLINE_SRC = $(top)/lib/readline-6.2.tar.gz 
READLINE_DIR = $(top)/lib/readline-6.2
READLINE_LIB = $(PREFIX_DIR)/lib/libreadline.a

####termcap
TERMCAP_SRC = $(top)/lib/termcap-1.3.1.tar.gz
TERMCAP_DIR = $(top)/lib/termcap-1.3.1
TERMCAP_LIB = $(PREFIX_DIR)/lib/libtermcap.a

PRE_LIST := $(PRE_LIST) $(TERMCAP_LIB) $(READLINE_LIB)
ifdef CLEAN_ALL
	CLEAN_LIST := $(CLEAN_LIST) $(PREFIX_DIR)/lib \
				  $(PREFIX_DIR)/include  \
				  $(READLINE_DIR) $(TERMCAP_DIR)
endif	

$(READLINE_LIB):
	tar -C $(top)/lib/ -zxvf $(READLINE_SRC)
	cd $(READLINE_DIR);./configure --prefix=$(PREFIX_DIR);\
	make;make install

$(TERMCAP_LIB):
	tar -C $(top)/lib/ -zxvf $(TERMCAP_SRC)
	cd $(TERMCAP_DIR);./configure --prefix=$(PREFIX_DIR);\
	make;make install

#------------------------------------------------------------
d   :=  $(dirstack_$(sp))
sp  :=  $(basename $(sp))
