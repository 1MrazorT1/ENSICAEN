PILOT_NAME = droitAuBut.exe

CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -Wpedantic -g
LDLIBS = -lm

SANITIZE=off
ifeq ($(SANITIZE),on)
CFLAGS += -fsanitize=address
endif

.PHONY: all clean distclean install try

DRIVERS_PATH = ..\drivers

all: $(PILOT_NAME)

install: $(DRIVERS_PATH)\$(PILOT_NAME)

try: install
	cd .. & .\GrandPrix

$(DRIVERS_PATH)\$(PILOT_NAME): $(PILOT_NAME)
	if not exist "$(DRIVERS_PATH)" mkdir "$(DRIVERS_PATH)"
	xcopy /Y /I $(PILOT_NAME) $(DRIVERS_PATH)\

$(PILOT_NAME): $(PILOT_NAME).c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

distclean: clean
	del /Q /F $(PILOT_NAME)

clean:
	del /Q /F *~ *.o
