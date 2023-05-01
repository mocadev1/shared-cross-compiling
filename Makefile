APP_NAME = miniBusybox

LIB_PATH = lib
INC_PATH = include

# Libraries being used
CAT_LIB_NAME  = cat
COPY_LIB_NAME  = copy
UNAME_LIB_NAME  = uname

LIBS = $(CAT_LIB_NAME) $(COPY_LIB_NAME) $(UNAME_LIB_NAME)
LIBS_H = $(CAT_LIB_NAME)/$(CAT_LIB_NAME).h \
					$(COPY_LIB_NAME)/$(COPY_LIB_NAME).h \
					$(UNAME_LIB_NAME)/$(UNAME_LIB_NAME).h

# Libraries shared objects
CAT_LIB_SO = lib$(CAT_LIB_NAME).so
COPY_LIB_SO = lib$(COPY_LIB_NAME).so
UNAME_LIB_SO = lib$(UNAME_LIB_NAME).so

# All shared objects
LIBS_SO = $(CAT_LIB_SO) $(COPY_LIB_SO) $(UNAME_LIB_SO)

OBJS = main.o cat.o copy.o uname.o

# Compiler options
CROSS_COMPILE ?=
CROSS_PRE ?=

ifeq ($(CROSS_COMPILE),)
CC = gcc
else
CC = $(CROSS_COMPILE)gcc
endif

CFLAGS = -g -Wall
SO_FLAGS = -shared -fPIC


# ======= Makefile =======

.PHONY: all install clean

all: $(LIBS_SO) $(APP_NAME)

# 												path/libName
$(CAT_LIB_SO): $(CAT_LIB_NAME)/$(CAT_LIB_NAME).c
	$(CC) $(CFLAGS) $(SO_FLAGS) $^ -o $@

$(COPY_LIB_SO): $(COPY_LIB_NAME)/$(COPY_LIB_NAME).c
	$(CC) $(CFLAGS) $(SO_FLAGS) $^ -o $@

$(UNAME_LIB_SO): $(UNAME_LIB_NAME)/$(UNAME_LIB_NAME).c
	$(CC) $(CFLAGS) $(SO_FLAGS) $^ -o $@

$(APP_NAME): $(OBJS)
# Linking header files
	$(CC) $(CFLAGS) $(OBJS) \
		-l$(CAT_LIB_NAME)			\
		-l$(COPY_LIB_NAME)		\
		-l$(UNAME_LIB_NAME)		\
		-L$(PWD)							\
		-o $@

install: $(LIBS_SO) $(LIBS_H)
	@cp $(LIBS_SO) /usr/$(LIB_PATH)/
	@cp $(LIBS_H) /usr/$(INC_PATH)/
	@ldconfig

clean:
	@rm -f $(OBJS) $(LIBS_SO) $(APP_NAME) 