MAKE = make
IPASRC = src/ipa
PMSSRC = src/pms

.PHONY: all clean ipa pms

all: pms ipa

pms ipa:
	$(MAKE) --directory=src/$@ $@

clean:
	$(MAKE) clean --directory=$(IPASRC)
	$(MAKE) clean --directory=$(PMSSRC)

