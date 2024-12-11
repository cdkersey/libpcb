PREFIX ?= /usr/local
CXXFLAGS += '-DDEFAULT_FONT_PATH="$(PREFIX)/share/libpcb/FONT"' -std=c++11 -fPIC

HEADERS = component.h error.h layer.h pin.h text.h via.h drawable.h gerber.h \
          net.h point.h track.h poly.h basic.h
OBJS = point.o error.o gerber.o net.o drawable.o via.o pin.o track.o poly.o \
       text.o

all: libpcb.so libpcb.a

libpcb.a: $(OBJS)
	ar q $@ $(OBJS)

libpcb.so: $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) -shared $(OBJS) $(LDLIBS)

%.o : %.cpp $(HEADERS)

install: libpcb.so $(HEADERS)
	if [ ! -e $(PREFIX)/lib ]; then mkdir -p $(PREFIX)/lib; fi
	cp libpcb.so libpcb.a $(PREFIX)/lib
	if [ ! -e $(PREFIX)/include/libpcb ]; \
          then mkdir -p $(PREFIX)/include/libpcb; fi
	cp $(HEADERS) $(PREFIX)/include/libpcb
	if [ ! -e $(PREFIX)/share/libpcb ]; \
          then mkdir -p $(PREFIX)/share/libpcb; fi
	cp FONT $(PREFIX)/share/libpcb

clean:
	$(RM) libpcb.so libpcb.a $(OBJS) *~
