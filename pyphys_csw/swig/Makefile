# Any questions ? > 8-800-200-8002

MODULENAME := kmp

SPREF := ../src
SDIRS := $(addprefix $(SPREF)/, math shared)
SDIRS += $(SPREF)

IPREF :=
IDIRS := $(addprefix $(IPREF), math shared)
#IDIRS += .

BPREF := module
BDIRS := $(patsubst $(SPREF)%, $(BPREF)%, $(SDIRS))

SRCHWILDCARDS := $(addsuffix /*.i, $(IDIRS))

IFILES := $(wildcard $(SRCHWILDCARDS))

SFILES := $(patsubst $(IPREF)%.i, %.c, $(IFILES))
SFILES := $(addprefix $(SPREF)/, $(SFILES))

ADDSF := $(MODULENAME).c $(MODULENAME)_wrap.c
OFILES := $(patsubst $(SPREF)%.c, $(BPREF)%.o, $(SFILES))
SFILES += $(ADDSF)
ADDSF := $(patsubst %.c, %.o, $(ADDSF))
OFILES += $(ADDSF)


#INC := -I/usr/include/python2.6/

#CF := -Wall $(CFLAGS)
#override CF += -pipe -fPIC $(INC)
#LF := -shared -lm

SF := -python -shadow -classic
# -debug-module 4

all: swig mkdirs pydistutils #module
	@echo ":-)"

swig: $(MODULENAME).i
	@echo "[SWIG] $(SF) $^"
	swig $(SF) $^

$(MODULENAME)_wrap.c: swig

EMPTY :=
SPACE :=$(EMPTY) $(EMPTY)
COMMA :=,
SLASH :=/
BSLASH :=\/
SCFILES :=$(subst $(SPACE),'$(COMMA) ',$(SFILES))
SCFILES :=$(subst $(SLASH),$(BSLASH),$(SCFILES))
SCFILES :='$(SCFILES)'

pydistutils: $(SFILES) setup.py
	@echo "[SED] Updating setup.py for python distutils"
	sed  -i -e "s/sources=\[.*\]/sources=\[$(SCFILES)\]/" setup.py #\\> setup.py
	@echo "[PYTHON] setu.py build_ext --inplace"
	python setup.py build_ext --inplace

module: $(OFILES)
	@echo "[LD] $^ => $@"
	gcc $(CF) $(LF) $^ -o _$(MODULENAME).so

#$(BPREF)/%.o: $(SPREF)/%.c
#	@echo "[CC] $< -> $@"
#	gcc $(CF) -c $< -o $@
#$(MODULENAME).o: $(MODULENAME).c
#	@echo "[CC] $< -> $@"
#	gcc $(CF) -c $< -o $@
#$(MODULENAME)_wrap.o: $(MODULENAME)_wrap.c
#	@echo "[CC] $< -> $@"
#	gcc $(CF) -c $< -o $@


.PHONY: clean showvars mkdirs rebuild

clean:
	@echo cleaning...
#	@echo [RM] $(OFILES)
#	@rm $(OFILES)
	@echo [RM] -r build
	rm -r build
	@echo [RM] _$(MODULENAME).so
	rm _$(MODULENAME).so

showvars:
	@echo $(SPREF)
	@echo $(SDIRS)
	@echo $(BPREF)
	@echo $(BDIRS)
	@echo $(IFILES)
	@echo $(SFILES)
	@echo $(OFILES)

mkdirs:
#	@echo [MKDIR] -p $(BDIRS)
#	@mkdir -p $(BDIRS)

rebuild: clean all

