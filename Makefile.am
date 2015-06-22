AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

SUBDIRS = \
	modules/beng \
	modules/tools 



bin_PROGRAMS = engine

engine_SOURCES = src/main.cpp 


AM_CPPFLAGS = \
	-Imodules/beng/include \
	-Imodules/tools/include 



AM_CXXFLAGS = @AM_CXXFLAGS@ 


engine_LDADD = \
		modules/beng/libbeng.a \
		modules/tools/libtools.a \
		$(LIBOBJS)


AM_LDFLAGS = -ljpeg -lglut -lGLEW -lrt 



#dist_noinst_SCRIPTS = autogen.sh
