#-- start of make_header -----------------

#====================================
#  Document CCQENu_python_init
#
#   Generated Sun Jun  9 16:06:33 2019  by sultana
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_CCQENu_python_init_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_CCQENu_python_init_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_CCQENu_python_init

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENu_python_init = $(CCQENu_tag)_CCQENu_python_init.make
cmt_local_tagfile_CCQENu_python_init = $(bin)$(CCQENu_tag)_CCQENu_python_init.make

else

tags      = $(tag),$(CMTEXTRATAGS)

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENu_python_init = $(CCQENu_tag).make
cmt_local_tagfile_CCQENu_python_init = $(bin)$(CCQENu_tag).make

endif

include $(cmt_local_tagfile_CCQENu_python_init)
#-include $(cmt_local_tagfile_CCQENu_python_init)

ifdef cmt_CCQENu_python_init_has_target_tag

cmt_final_setup_CCQENu_python_init = $(bin)setup_CCQENu_python_init.make
#cmt_final_setup_CCQENu_python_init = $(bin)CCQENu_CCQENu_python_initsetup.make
cmt_local_CCQENu_python_init_makefile = $(bin)CCQENu_python_init.make

else

cmt_final_setup_CCQENu_python_init = $(bin)setup.make
#cmt_final_setup_CCQENu_python_init = $(bin)CCQENusetup.make
cmt_local_CCQENu_python_init_makefile = $(bin)CCQENu_python_init.make

endif

cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)CCQENusetup.make

#CCQENu_python_init :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'CCQENu_python_init'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = CCQENu_python_init/
#CCQENu_python_init::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of python_init_header ------

installarea = ${CMTINSTALLAREA}$(shared_install_subdir)
install_python_dir = $(installarea)/python/CCQENu
init_file = $(install_python_dir)/__init__.py


CCQENu_python_init :: CCQENu_python_initinstall

install :: CCQENu_python_initinstall

CCQENu_python_initinstall :: $(init_file)

$(init_file) ::
	@if [ -e $(install_python_dir) -a ! -e $(init_file) ]; then \
	  echo "Installing __init__.py file from ${GAUDIPOLICYROOT}" ; \
	  $(install_command) ${GAUDIPOLICYROOT}/cmt/fragments/__init__.py $(install_python_dir) ; \
	fi

CCQENu_python_initclean :: CCQENu_python_inituninstall

uninstall :: CCQENu_python_inituninstall

CCQENu_python_inituninstall ::
	@$(uninstall_command) $(init_file)


#-- end of python_init_header ------
#-- start of cleanup_header --------------

clean :: CCQENu_python_initclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(CCQENu_python_init.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
	if echo $@ | grep 'CCQENusetup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENu_python_init.make): $@: File no longer generated" >&2; exit 0; fi
else
.DEFAULT::
	$(echo) "(CCQENu_python_init.make) PEDANTIC: $@: No rule for such target" >&2
	if echo $@ | grep 'CCQENusetup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENu_python_init.make): $@: File no longer generated" >&2; exit 0;\
	 elif test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_CCQENu_python_init)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENu_python_init.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr $@ : '.*/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENu_python_init.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENu_python_init.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

CCQENu_python_initclean ::
#-- end of cleanup_header ---------------
