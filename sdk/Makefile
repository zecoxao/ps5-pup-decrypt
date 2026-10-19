# Builds ps5_pup_decrypt.elf with ps5-payload-sdk (https://github.com/ps5-payload-dev/sdk).
#
#   export PS5_PAYLOAD_SDK=/opt/ps5-payload-sdk
#   make            # build
#   make test       # send to the ELF loader (PS5_HOST / PS5_PORT)

PS5_HOST ?= ps5
PS5_PORT ?= 9021

ifdef PS5_PAYLOAD_SDK
    include $(PS5_PAYLOAD_SDK)/toolchain/prospero.mk
else
    $(error PS5_PAYLOAD_SDK is undefined)
endif

ELF  := ps5_pup_decrypt.elf
SRCS := $(wildcard source/*.c)

CFLAGS := -Wall -Wno-format -Wno-format-security -Iinclude -lSceNotification

all: $(ELF)

$(ELF): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(ELF)

test: $(ELF)
	$(PS5_DEPLOY) -h $(PS5_HOST) -p $(PS5_PORT) $^
