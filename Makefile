# Makefile
# Date : Mercredi 18 janvier 2012
# 
# Cibles : 
#         - all     : Créé le programme executable
#         - strip   : Strip l'executable
#         - clean   : Nettoie les fichiers objets
#         - nuke    : Nettoie les fichiers objets
#                     et l'éxécutable
#         - deb     : Crée le paquet .deb (nécessite
#                     le programme makedeb)
#         - rebuild : nuke et reconstruit le projet
#         - dist    : Archive les sources en tgz
#         - manps   : Crée la page man en .ps
#         - mangz   : Crée la page man en .gz

# Réglages ###########################################

# Nom du compilateur
COMPILER=g++
# Répertoire des fichiers sources
SRCDIR=./src
INCLUDEDIR=./include
# Flags à passer au compilo
FLAGS=-Wall -I $(INCLUDEDIR) -I include/libluawrap -O2 $(shell pkg-config --cflags lua5.2)
# Flags à passer à l'édition de liens
LDFLAGS=$(shell pkg-config --libs lua5.2)
# Extention des fichiers source (ex 'cpp' pour le C++)
SRCEXT=cpp
# Nom de l'éxécutable
EXEC=libluawrap
LIB=libluawrap.a
VERSION_MAJOR=0
VERSION_MINOR=2
DLIB=libluawrap.so.$(VERSION_MAJOR)

# Man configuration
# Program's category, for instance 1 is a program
# And 3 a library.
CATEGORY=3
# The manpage filename
MANDEPS=man/$(EXEC).$(CATEGORY)
MANGZ=man/$(EXEC).$(CATEGORY).gz
MANPS=man/$(EXEC).$(CATEGORY).ps

# Installation
INSTALL_TOP=/usr/local
INSTALL_LIB=$(INSTALL_TOP)/lib
INSTALL_INC=$(INSTALL_TOP)/include
INSTALL_MAN=$(INSTALL_TOP)/man/man3
INSTALL_PC=$(INSTALL_TOP)/lib/pkgconfig

INSTALL= install -p
INSTALL_EXEC= $(INSTALL) -m 0755
INSTALL_DATA= $(INSTALL) -m 0644
INSTALL_DIR= cp -r 

MKDIR= mkdir -p
RM= rm -f
RMD= rm -fr

# Makedeb configuration
ifneq ("$(shell which makedeb)","")
USE_MAKEDEB=1
MAKEDEB_SUFFIX=$(shell makedeb --suffix)
PACKAGE_NAME=$(shell basename `pwd`)
else
USE_MAKEDEB=0
endif


# Fin des réglages ###################################

# Auto-options #######################################

# Répertoire temporaire pour l'archivage
DISTDIR=$(shell basename `pwd`)-src-$(VERSION_MAJOR).$(VERSION_MINOR)
# Fichiers sources
SRC=$(wildcard $(SRCDIR)/*.$(SRCEXT))
# Fichiers objet
OBJ=$(SRC:.$(SRCEXT)=.o)

# Fin auto-options ###################################

# Cibles spéciales

all: $(EXEC) $(LIB) $(DLIB).$(VERSION_MINOR) $(MANGZ)
rebuild: nuke all
strip: all
	strip -s $(DLIB).$(VERSION_MINOR)

# install
install: strip $(EXEC) $(DLIB).$(VERSION_MINOR) $(MANGZ)
	$(MKDIR) $(INSTALL_BIN) $(INSTALL_INC) $(INSTALL_LIB) $(INSTALL_MAN) $(INSTALL_PC)
	$(INSTALL_DIR) include/libluawrap $(INSTALL_INC)
	$(INSTALL_DATA) include/libluawrap.h $(INSTALL_INC)
	$(INSTALL_DATA) $(DLIB).$(VERSION_MINOR) $(INSTALL_LIB)
	$(INSTALL_DATA) man/libluawrap.3.gz $(INSTALL_MAN)
	cat pkgconfig/libluawrap.pc | awk '//{gsub("prefix=/usr/local", "prefix=$(INSTALL_TOP)"); print $0; }' > $(INSTALL_PC)/libluawrap.pc
	ln -sf $(INSTALL_LIB)/$(DLIB).$(VERSION_MINOR) $(INSTALL_LIB)/$(DLIB)
	ln -sf $(INSTALL_LIB)/$(DLIB) $(INSTALL_LIB)/$(shell basename $(DLIB) .$(VERSION_MAJOR))

uninstall:
	cd $(INSTALL_INC) && $(RMD) libluawrap/
	cd $(INSTALL_INC) && $(RM) libluawrap.h
	cd $(INSTALL_LIB) && $(RM) libluawrap.so
	cd $(INSTALL_LIB) && $(RM) libluawrap.so.$(VERSION_MAJOR)
	cd $(INSTALL_LIB) && $(RM) libluawrap.so.$(VERSION_MAJOR).$(VERSION_MINOR)
	cd $(INSTALL_MAN) && $(RM) libluawrap.3.gz
	cd $(INSTALL_PC) && $(RM) libluawrap.pc

# Executable

$(EXEC): $(OBJ)
	$(COMPILER) -o $(EXEC) $(OBJ) $(LDFLAGS)


$(LIB): $(OBJ)
	ar -q $(LIB) $(SRCDIR)/lua_*.o

$(DLIB).$(VERSION_MINOR): $(OBJ)
	g++ -shared -Wl,-soname,$(DLIB) -fPIC $(SRCDIR)/lua_*.o -o $(DLIB).$(VERSION_MINOR)

# Fichiers objets

%.o: %.$(SRCEXT)
	$(COMPILER) $(FLAGS) -c $< -o $@

# Package deb

ifeq ($(USE_MAKEDEB),1)
deb: all strip
	makedeb
	if [ "`makedeb --autoexec`" = "0" ]; then \
		./$(PACKAGE_NAME)$(MAKEDEB_SUFFIX); \
	fi;
endif

# Pages de man
mangz: $(MANGZ)
$(MANGZ): $(MANDEPS)
	gzip -c $(MANDEPS) > $(MANGZ)

ifneq ($(shell which groff),)
# Alias :
manps: $(MANPS)
$(MANPS): $(MANDEPS)
	groff -K utf8 -t -e -mandoc -Tps $(MANDEPS) > $(MANPS)
endif

# Clean & nuke

clean:
	rm -f $(SRCDIR)/*.o
	rm -f man/*.gz man/*.ps
ifeq ($(USE_MAKEDEB),1)
	if [ -e ./$(PACKAGE_NAME)$(MAKEDEB_SUFFIX) ]; then \
		 ./$(PACKAGE_NAME)$(MAKEDEB_SUFFIX) --clean; \
	fi;
endif

nuke: clean
	rm -f $(EXEC)
	rm -f $(LIB)
	rm -f $(DLIB)
	rm -f $(DLIB).$(VERSION_MINOR)
	rm -f $(DISTDIR).tgz

# Archivage

dist: nuke
	if ! [ -d $(DISTDIR) ]; then \
		mkdir $(DISTDIR); \
	fi;\
	if ! [ -d $(DISTDIR)/$(SRCDIR) ]; then \
		mkdir $(DISTDIR)/$(SRCDIR); \
	fi;\
	if ! [ -d $(DISTDIR)/$(INCLUDEDIR) ]; then \
		mkdir $(DISTDIR)/$(INCLUDEDIR); \
	fi;\
	if [ -e "INSTALL" ]; then cp INSTALL $(DISTDIR); fi;
	if [ -e "LICENSE" ]; then cp LICENSE $(DISTDIR); fi;
	if [ -e "AUTHORS" ]; then cp AUTHORS $(DISTDIR); fi;
	if [ -e "COPYING" ]; then cp COPYING $(DISTDIR); fi;
	if [ -d "man"     ]; then cp -r man  $(DISTDIR); fi;
ifeq ($(USE_MAKEDEB),1)
	if [ -e "$(PACKAGE_NAME).xml"   ]; then cp *.xml   $(DISTDIR); fi;
endif
	cp $(SRCDIR)/*.$(SRCEXT) $(DISTDIR)/$(SRCDIR)
	cp -r $(INCLUDEDIR) $(DISTDIR)
	cp -r pkgconfig $(DISTDIR)
	cp -r scripts $(DISTDIR)
	cp Makefile $(DISTDIR)
	tar zcvf $(DISTDIR).tgz $(DISTDIR)/
	rm -r $(DISTDIR)
