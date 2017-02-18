SOURCES= executeCD.c  executeCMD.c  parse.c  print.c  main.c executePWD.c executeECHO.c pinfo.c test.c setInput.c setOutput.c insert.c killall.c delete.c fg.c listjobs.c sendsig.c
INCLUDES= 
CFLAGS=
SLIBS= 
PROGRAM= main

OBJECTS= $(SOURCES.c:.c=.o)

.KEEP_STATE:

debug := CFLAGS= -g

all debug: $(PROGRAM)

# $(PROGRAM): $(INCLUDES) $(OBJECTS)
	# $(LINK.c)  -g -o $@ $(OBJECTS) $(SLIBS)

$(PROGRAM) : $(SOURCES)
	gcc $(SOURCES) -g -o main
clean:
	rm -f $(PROGRAM) $(OBJECTS)
