CC=g++
CFLAGS= -Wall -Wextra 
INCLUDEFLAGS=-I/usr/include/libxml2 -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/libxml++-2.6 -I/usr/lib/libxml++-2.6/include -I/usr/include/curl 
LDLIBS=-L/opt/local/lib  -lcurl -lxml++-2.6 -lxml2 -lglibmm-2.4 -lgobject-2.0 -lsigc-2.0 -lglib-2.0 -lxslt

all: testParsers

testParsers: testParsers.o LwSaxParser.o FromXMLToGoogleMapHTTPRequest.o FromGoogleMapXMLToDistanceTable.o SortVisits.o Address.o RO.o
	$(CC) RO.o Address.o SortVisits.o FromGoogleMapXMLToDistanceTable.o FromXMLToGoogleMapHTTPRequest.o LwSaxParser.o testParsers.o -o testParsers $(LDLIBS)

testParsers.o : FromXMLToGoogleMapHTTPRequest.o LwSaxParser.o testParsers.c
	$(CC) -c $(CFLAGS) $(INCLUDEFLAGS) testParsers.c -o testParsers.o

LwSaxParser.o : LwSaxParser.h LwSaxParser.cpp
	$(CC) -c $(CFLAGS) $(INCLUDEFLAGS) LwSaxParser.cpp -o LwSaxParser.o

FromXMLToGoogleMapHTTPRequest.o :  Address.h FromXMLToGoogleMapHTTPRequest.h FromXMLToGoogleMapHTTPRequest.cpp LwSaxParser.h LwSaxParser.cpp
	$(CC) -c $(CFLAGS) $(INCLUDEFLAGS) FromXMLToGoogleMapHTTPRequest.cpp -o FromXMLToGoogleMapHTTPRequest.o

FromGoogleMapXMLToDistanceTable.o : FromGoogleMapXMLToDistanceTable.h FromGoogleMapXMLToDistanceTable.cpp LwSaxParser.h LwSaxParser.cpp
	$(CC) -c $(CFLAGS) $(INCLUDEFLAGS) FromGoogleMapXMLToDistanceTable.cpp -o FromGoogleMapXMLToDistanceTable.o

SortVisits.o : SortVisits.h SortVisits.cpp Address.h
	$(CC) -c $(CFLAGS) $(INCLUDEFLAGS) SortVisits.cpp -o SortVisits.o	
Address.o : Address.h Address.cpp
	$(CC) -c $(CFLAGS) $(INCLUDEFLAGS) Address.cpp -o Address.o
	
RO.o : RO.cpp
	$(CC) -c $(CFLAGS) $(INCLUDEFLAGS) RO.cpp -o RO.o

clean:
	rm -rf *o 
	rm -rf *~
	rm -rf #*

realclean: clean
	rm -rf testParsers
