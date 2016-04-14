# Main Makefile.am

#AM_CPPFLAGS= \
#	     -I$(top_builddir)/modules/tools/include \
#            -I$(top_builddir)/modules/beng/include 


AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

SUBDIRS = \
	modules/tools \
	modules/beng 


bin_PROGRAMS = engine


engine_SOURCES = src/main.cpp 


engine_LDADD = \
		modules/beng/libbeng.a \
		modules/tools/libtools.a \
		$(RT_LIBS) \
		$(JPEG_LIBS) \
		$(GLUT_LIBS) \
		$(GLEW_LIBS) \
		$(GL_LIBS)


#dist_noinst_SCRIPTS = autogen.sh
