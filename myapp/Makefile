.PHONY: all clean

OBJS= myapp.o

CFLAGS= -std=c11 -pedantic -Wall -Wextra
CFLAGS+= -O1

MYLIB_PATH= ../mylib

INCLUDES+= -I $(MYLIB_PATH)/include

all: myapp

clean:
	$(RM) -f $(OBJS)
	$(RM) -f $(OBJS:.o=.d)
	$(RM) -f myapp myapp.exe

vpath %.c  \
    src
vpath %.a  \
    $(MYLIB_PATH)

# Не забудем зависимость от библиотеки!
# И компилятору, и make передается только название библиотеки, из него формируется имя файла библиотеки
myapp: $(OBJS) -lmylib
	gcc -o $@  $^

%.o: %.c
	gcc -MD $(CFLAGS) $(INCLUDES) -c -o $@ $<

-include $(OBJS:.o=.d)
