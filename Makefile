CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O2
LDFLAGS = -shared
PAMDIR = /lib/security
PREFIX = /usr

all: libhive.so pam_hive.so hive-init hive-shell hive-test

libhive.so: hive-personality.o
	$(CC) $(LDFLAGS) -o $@ $^

pam_hive.so: pam_hive.o hive-personality.o
	$(CC) $(LDFLAGS) -lpam -o $@ $^

hive-init: hive-init.o hive-personality.o
	$(CC) -o $@ $^

hive-shell: hive-shell.o hive-personality.o
	$(CC) -o $@ $^

hive-test: hive-test.o hive-personality.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	install -d $(DESTDIR)$(PAMDIR)
	install -m 644 pam_hive.so $(DESTDIR)$(PAMDIR)/
	install -d $(DESTDIR)/usr/include/hive
	install -m 644 hive-personality.h $(DESTDIR)/usr/include/hive/
	install -d $(DESTDIR)/usr/bin
	install -m 755 hive-init hive-shell $(DESTDIR)/usr/bin/

clean:
	rm -f *.o *.so hive-init hive-shell hive-test

.PHONY: all install clean