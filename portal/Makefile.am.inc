libexec_PROGRAMS += \
	flatpak-portal \
	$(NULL)

service_in_files += portal/flatpak-portal.service.in
systemduserunit_DATA += portal/flatpak-portal.service

service_in_files += portal/org.freedesktop.portal.Flatpak.service.in
dbus_service_DATA += portal/org.freedesktop.portal.Flatpak.service

portal_built_sources = portal/flatpak-portal-dbus.c portal/flatpak-portal-dbus.h

portal/flatpak-portal-dbus.c: data/org.freedesktop.portal.Flatpak.xml Makefile
	mkdir -p $(builddir)/portal
	$(AM_V_GEN) $(GDBUS_CODEGEN)				\
		--interface-prefix org.freedesktop.portal	\
		--c-namespace Portal				\
		--generate-c-code $(builddir)/portal/flatpak-portal-dbus	\
		$(srcdir)/data/org.freedesktop.portal.Flatpak.xml  \
		$(NULL)

portal/%-dbus.h: portal/%-dbus.c
	@true # Built as a side-effect of the rules for the .c

flatpak_portal_SOURCES = \
	$(portal_built_sources)		\
	portal/flatpak-portal.c		\
	portal/flatpak-portal.h		\
	portal/flatpak-portal-app-info.c		\
	portal/flatpak-portal-app-info.h		\
	portal/flatpak-portal-error.c	\
	portal/flatpak-portal-error.h	\
	$(NULL)

BUILT_SOURCES += $(portal_built_sources)
CLEANFILES += $(portal_built_sources)

flatpak_portal_LDADD = $(AM_LDADD) $(BASE_LIBS)
flatpak_portal_CFLAGS = $(AM_CFLAGS) $(BASE_CFLAGS)
flatpak_portal_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/portal
