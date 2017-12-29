include device.mak

all:
	for i in $(TYPES); do \
		for j in $(PLL_SETTINGS); do \
			$(MAKE) -C build TYPE=$${i} PLL_SETTING=$${j} all; \
		done \
	done

clean:
	for i in $(TYPES); do \
		for j in $(PLL_SETTINGS); do \
			$(MAKE) -C build TYPE=$${i} PLL_SETTING=$${j} clean; \
		done \
	done

%::
	for i in $(TYPES); do \
		for j in $(PLL_SETTINGS); do \
			$(MAKE) -C build TYPE=$${i} PLL_SETTING=$${j} $@; \
		done \
	done

		
