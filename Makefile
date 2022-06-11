CC = clang
CXX = clang++

.PHONY: all

all: out/magiskboot.exe
	
out/magiskboot.exe: out/cygwin1.dll
	@mkdir -p out
	@cd native/jni && $(MAKE) -f magiskboot.mk
	@echo -e "\t    COPY\t    $@"
	@cp native/jni/bin/magiskboot ./out/magiskboot.exe

out/cygwin1.dll:
	@mkdir -p out
	@echo -e "\t    COPY\t    $@"
	@cp /bin/cygwin1.dll ./out/

clean:
	@echo -e "\t    RM\t    out"
	@rm -rf out
	@cd native/jni && $(MAKE) -f magiskboot.mk clean

