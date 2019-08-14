#-- start of make_header -----------------

#====================================
#  Document CCQENuConf
#
#   Generated Wed Aug 14 02:45:48 2019  by sultana
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_CCQENuConf_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_CCQENuConf_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_CCQENuConf

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENuConf = $(CCQENu_tag)_CCQENuConf.make
cmt_local_tagfile_CCQENuConf = $(bin)$(CCQENu_tag)_CCQENuConf.make

else

tags      = $(tag),$(CMTEXTRATAGS)

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENuConf = $(CCQENu_tag).make
cmt_local_tagfile_CCQENuConf = $(bin)$(CCQENu_tag).make

endif

include $(cmt_local_tagfile_CCQENuConf)
#-include $(cmt_local_tagfile_CCQENuConf)

ifdef cmt_CCQENuConf_has_target_tag

cmt_final_setup_CCQENuConf = $(bin)setup_CCQENuConf.make
#cmt_final_setup_CCQENuConf = $(bin)CCQENu_CCQENuConfsetup.make
cmt_local_CCQENuConf_makefile = $(bin)CCQENuConf.make

else

cmt_final_setup_CCQENuConf = $(bin)setup.make
#cmt_final_setup_CCQENuConf = $(bin)CCQENusetup.make
cmt_local_CCQENuConf_makefile = $(bin)CCQENuConf.make

endif

cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)CCQENusetup.make

#CCQENuConf :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'CCQENuConf'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = CCQENuConf/
#CCQENuConf::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
# File: cmt/fragments/genconfig_header
# Author: Wim Lavrijsen (WLavrijsen@lbl.gov)

# Use genconf.exe to create configurables python modules, then have the
# normal python install procedure take over.

.PHONY: CCQENuConf CCQENuConfclean

confpy  := CCQENuConf.py
conflib := $(bin)$(library_prefix)CCQENu.$(shlibsuffix)
dbpy    := CCQENu_confDb.py
instdir := $(CMTINSTALLAREA)$(shared_install_subdir)/python/$(package)
product := $(instdir)/$(confpy)
initpy  := $(instdir)/__init__.py

ifdef GENCONF_ECHO
genconf_silent =
else
genconf_silent = $(silent)
endif

CCQENuConf :: CCQENuConfinstall

install :: CCQENuConfinstall

CCQENuConfinstall : /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu/$(confpy)
	@echo "Installing /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu in /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/InstallArea/x86_64-slc6-gcc49-opt/python" ; \
	 $(install_command) --exclude="*.py?" --exclude="__init__.py" /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/InstallArea/x86_64-slc6-gcc49-opt/python ; \

/minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu/$(confpy) : $(conflib) /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu
	$(genconf_silent) $(genconfig_cmd)  -o /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu -p $(package) \
	  --configurable-module=GaudiKernel.Proxy \
	  --configurable-default-name=Configurable.DefaultName \
	  --configurable-algorithm=ConfigurableAlgorithm \
	  --configurable-algtool=ConfigurableAlgTool \
	  --configurable-auditor=ConfigurableAuditor \
          --configurable-service=ConfigurableService \
	  -i ../$(tag)/$(library_prefix)CCQENu.$(shlibsuffix)

/minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu:
	@ if [ ! -d /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu ] ; then mkdir -p /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu ; fi ;

CCQENuConfclean :: CCQENuConfuninstall
	$(cleanup_silent) $(remove_command) /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu/$(confpy) /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu/$(dbpy)

uninstall :: CCQENuConfuninstall

CCQENuConfuninstall ::
	@$(uninstall_command) /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/InstallArea/x86_64-slc6-gcc49-opt/python
libCCQENu_so_dependencies = ../x86_64-slc6-gcc49-opt/libCCQENu.so
#-- start of cleanup_header --------------

clean :: CCQENuConfclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(CCQENuConf.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENuConf.make): $@: File no longer generated" >&2; exit 0; fi
else
.DEFAULT::
	$(echo) "(CCQENuConf.make) PEDANTIC: $@: No rule for such target" >&2
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENuConf.make): $@: File no longer generated" >&2; exit 0;\
	 elif test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_CCQENuConf)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuConf.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr $@ : '.*/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuConf.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuConf.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

CCQENuConfclean ::
#-- end of cleanup_header ---------------
