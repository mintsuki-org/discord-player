.PHONY: all clean install uninstall distclean dist-clean

all:
	$(MAKE) -C generic-webplayer all

clean:
	$(MAKE) -C generic-webplayer clean

install:
	$(MAKE) -C generic-webplayer install

uninstall:
	$(MAKE) -C generic-webplayer uninstall

distclean:
	rm -rf generic-webplayer

dist-clean: distclean
