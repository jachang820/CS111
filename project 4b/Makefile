#
# NAME: Jonathan Chang
# EMAIL: j.a.chang820@gmail.com
# ID: 104853981
#

.SILENT:

CC = gcc
CFLAGS = -g -lmraa -lm
TAR = lab4b-104853981.tar.gz
LAB = lab4b
EDISON = EdisonSensors
TIMER = PreciseTimer
INPUT = README Makefile $(LAB).c $(TIMER).h $(TIMER).c $(EDISON).h \
	$(EDISON).c
FAILED = 0
.PHONY: check dist clean

# (default)
all: build
build: $(LAB)
lab4b: $(LAB).c $(TIMER).c $(EDISON).c
	$(CC) -o $@ $(TIMER).c $(EDISON).c $(LAB).c $(CFLAGS)

check: build
	@{ printf "PERIOD=0.6\n"; sleep 1.5; printf "STOP\n"; sleep 2; \
	printf "PERIOD=0.9\nSTART\n"; sleep 2; printf "OFF\n"; } | \
	./$(LAB) --period=1.5 --scale=C --log=logfile104853981 \
	> output104853981 2>&1 ; \
	FAILED=0; \
	if [ `wc -l < ./logfile104853981` -ne 11 ]; then \
		echo "Incorrect number of lines detected."; \
		FAILED=1; \
	fi; \
	if [ `grep "OFF" < ./output104853981` ]; then \
		echo "Log should contain OFF."; \
		FAILED=1; \
	fi; \
	if [ `grep -e "Failed" -e "failed" < ./output104853981` ]; then \
		echo "Failed in initializing or reading MRAA objects."; \
		FAILED=1; \
	fi; \
	rm logfile104853981; \
	rm output104853981; \
	if [ $$FAILED -eq 1 ]; then \
		echo "Check failed."; \
	else \
		echo "Check passed."; \
	fi

dist: build check create_tar
create_tar:
	tar -czvf $(TAR) $(INPUT)

clean:
	rm -f $(TAR) $(LAB)
