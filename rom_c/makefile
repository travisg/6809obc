# relies on a few different projects:
# gcc6809
# lwtools
# srecord
# 6809DASM (optional)
#
# ubuntu packages can be found at https://launchpad.net/~tormodvolden/+archive/ubuntu/m6809

BUILDDIR:=build

SRCS:=$(wildcard *.S *.c)
OBJS:=$(SRCS:%c=%o)
OBJS:=$(OBJS:%S=%o)

OBJS := $(addprefix $(BUILDDIR)/,$(OBJS))

DEPS := $(OBJS:.o=.d)

#$(info $(SRCS))
#$(info $(OBJS))

RESULT := result.srec result.ihx result.bin result.c000.bin result.map
RESULT := $(addprefix $(BUILDDIR)/,$(RESULT))

CFLAGS:=-ffreestanding -nostdlib -Wall -W -fomit-frame-pointer -I. -Os

LIBGCC:=$(shell m6809-unknown-gcc -print-libgcc-file-name)

.PHONY: all
all: $(RESULT)

$(BUILDDIR)/result.srec $(BUILDDIR)/result.map: $(OBJS) link.ld
	@$(MKDIR)
	@echo linking $@
	$(NOECHO)lwlink --format=srec \
		-s link.ld \
		--map=$(BUILDDIR)/result.map -o $@ $(OBJS) -lgcc -L$(dir $(LIBGCC))

$(BUILDDIR)/result.ihx: $(BUILDDIR)/result.srec
	@$(MKDIR)
	@echo generating $@
	$(NOECHO)srec_cat -Disable_Sequence_Warnings $< -Output $@ -Intel -address_length=2

$(BUILDDIR)/result.bin: $(BUILDDIR)/result.srec
	@$(MKDIR)
	@echo generating $@
	$(NOECHO)srec_cat -Disable_Sequence_Warnings $< -Output $@ -Binary

$(BUILDDIR)/result.c000.bin: $(BUILDDIR)/result.srec
	@$(MKDIR)
	@echo generating $@
	$(NOECHO)srec_cat -Disable_Sequence_Warnings $< -offset -0xc000 -Output $@ -Binary

$(BUILDDIR)/result.lst: $(BUILDDIR)/result.bin
	@echo generating $@
	$(NOECHO)./6809dasm -i$<  > $@

link.ld: # force changes to this to cause a re-link

.PHONY: clean
clean:
	rm -f $(OBJS) $(DEPS) $(RESULT)

# makes sure the target dir exists
MKDIR = if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
NOECHO ?= @

$(BUILDDIR)/%.o: %.c
	@$(MKDIR)
	@echo compiling $<
	$(NOECHO)m6809-unknown-gcc $(CFLAGS) -MD -MT $@ -MF $(@:%o=%d) -c $< -o $@

$(BUILDDIR)/%.o: %.S
	@$(MKDIR)
	@echo compiling $<
	$(NOECHO)m6809-unknown-gcc $(CFLAGS) -MD -MT $@ -MF $(@:%o=%d) -c $< -o $@

ifeq ($(filter $(MAKECMDGOALS), clean), )
-include $(DEPS)
endif

