.PHONY: all clean

OBJS= mytests.o

CFLAGS= -std=c11 -pedantic -Wall -Wextra
CFLAGS+= -O1

MYLIB_PATH= ../mylib

# Включаемые файлы следует искать в каталогах "include" библиотеки и программы
INCLUDES+= -I $(MYLIB_PATH)/include
INCLUDES+= -I ./include

all: mytests


clean:
	$(RM) -f $(OBJS)
	$(RM) -f $(OBJS:.o=.d)
	$(RM) -f mytests mytests.exe

# Make должна искать файлы *.h в каталоге include
# ..., а файлы *.c - в каталоге src
vpath %.h include
vpath %.c  \
    src
vpath %.a  \
    $(MYLIB_PATH)

# Не забудем зависимость от библиотеки!
# И компилятору, и make передается только название библиотеки, из него формируется имя файла библиотеки
mytests: $(OBJS) -lmylib
	gcc -o $@  $^

%.o: %.c
	gcc -MD $(CFLAGS) $(INCLUDES) -c -o $@ $<

-include $(OBJS:.o=.d)
