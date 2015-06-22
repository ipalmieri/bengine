# beng/Makefile.am

AUTOMAKE_OPTIONS = subdir-objects

# additional include pathes necessary to compile the C++ library
AM_CPPFLAGS = \
		-Iinclude \
		-I$(top_builddir)/modules/tools/include


#AM_LDFLAGS =  

###############################################################################
# THE LIBRARIES TO BUILD
###############################################################################

# the library names to build (note we are building static libs only)
noinst_LIBRARIES = libbeng.a


# where to install the headers on the system
libbeng_adir = $(includedir)/beng


# the list of header files that belong to the library (to be installed later)
libbeng_a_HEADERS = 	\
			include/beng.h \
			include/berror.h \
			include/camera.h \
			include/edefs.h \
			include/engnode.h \
			include/frustum.h \
			include/light.h \
			include/material.h \
			include/mesh.h \
			include/program.h \
			include/renderer.h \
			include/shader.h \
			include/texture.h \
			include/viewport.h


# the sources to add to the library and to add to the source distribution
libbeng_a_SOURCES =	\
			$(libbeng_a_HEADERS) \
			src/renderer.cpp \
			src/camera.cpp \
			src/material.cpp \
			src/viewport.cpp \
			src/frustum.cpp \
			src/light.cpp \
			src/engnode.cpp \
			src/mesh.cpp \
			src/shader.cpp \
			src/program.cpp \
			src/berror.cpp \
			src/texture.cpp 






###############################################################################
