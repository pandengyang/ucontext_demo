CC = gcc
CPPFLAGS = -I./include
CFLAGS =
LDFLAGS =
LIBS=

RM = rm -rf
MKDIR = mkdir -p

DEPS = .dep

TARGET = demo

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

TARGET:$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJS):%.o:%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

sinclude $(patsubst %.c, $(DEPS)/%.d, $(SRCS))
$(DEPS)/%.d:%.c
	$(MKDIR) $(DEPS); \
	rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[: ]*,\1.o $@: ,g' < $@.$$$$ > $@; \
	$(RM) -f $@.$$$$

.PHONY:clean cleanall

clean:
	$(RM) $(TARGET) $(OBJS)

cleanall:
	$(RM) $(TARGET) $(OBJS) $(DEPS) .*.sw?
