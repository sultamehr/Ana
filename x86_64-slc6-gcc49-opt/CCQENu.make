#-- start of make_header -----------------

#====================================
#  Library CCQENu
#
#   Generated Mon Aug 12 17:19:18 2019  by sultana
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_CCQENu_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_CCQENu_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_CCQENu

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENu = $(CCQENu_tag)_CCQENu.make
cmt_local_tagfile_CCQENu = $(bin)$(CCQENu_tag)_CCQENu.make

else

tags      = $(tag),$(CMTEXTRATAGS)

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENu = $(CCQENu_tag).make
cmt_local_tagfile_CCQENu = $(bin)$(CCQENu_tag).make

endif

include $(cmt_local_tagfile_CCQENu)
#-include $(cmt_local_tagfile_CCQENu)

ifdef cmt_CCQENu_has_target_tag

cmt_final_setup_CCQENu = $(bin)setup_CCQENu.make
#cmt_final_setup_CCQENu = $(bin)CCQENu_CCQENusetup.make
cmt_local_CCQENu_makefile = $(bin)CCQENu.make

else

cmt_final_setup_CCQENu = $(bin)setup.make
#cmt_final_setup_CCQENu = $(bin)CCQENusetup.make
cmt_local_CCQENu_makefile = $(bin)CCQENu.make

endif

cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)CCQENusetup.make

#CCQENu :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'CCQENu'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = CCQENu/
#CCQENu::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

CCQENulibname   = $(bin)$(library_prefix)CCQENu$(library_suffix)
CCQENulib       = $(CCQENulibname).a
CCQENustamp     = $(bin)CCQENu.stamp
CCQENushstamp   = $(bin)CCQENu.shstamp

CCQENu :: dirs  CCQENuLIB
	$(echo) "CCQENu ok"

#-- end of libary_header ----------------
#-- start of libary ----------------------

CCQENuLIB :: $(CCQENulib) $(CCQENushstamp)
	$(echo) "CCQENu : library ok"

$(CCQENulib) :: $(bin)CCQENu.o $(bin)CCQENuRecoUtils.o
	$(lib_echo) "static library $@"
	$(lib_silent) [ ! -f $@ ] || \rm -f $@
	$(lib_silent) $(ar) $(CCQENulib) $(bin)CCQENu.o $(bin)CCQENuRecoUtils.o
	$(lib_silent) $(ranlib) $(CCQENulib)
	$(lib_silent) cat /dev/null >$(CCQENustamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

#
# We add one level of dependency upon the true shared library 
# (rather than simply upon the stamp file)
# this is for cases where the shared library has not been built
# while the stamp was created (error??) 
#

$(CCQENulibname).$(shlibsuffix) :: $(CCQENulib) requirements $(use_requirements) $(CCQENustamps)
	$(lib_echo) "shared library $@"
	$(lib_silent) if test "$(makecmd)"; then QUIET=; else QUIET=1; fi; QUIET=$${QUIET} bin=$(bin) $(make_shlib) "$(tags)" CCQENu $(CCQENu_shlibflags)

$(CCQENushstamp) :: $(CCQENulibname).$(shlibsuffix)
	$(lib_silent) if test -f $(CCQENulibname).$(shlibsuffix) ; then cat /dev/null >$(CCQENushstamp) ; fi

CCQENuclean ::
	$(cleanup_echo) objects CCQENu
	$(cleanup_silent) /bin/rm -f $(bin)CCQENu.o $(bin)CCQENuRecoUtils.o
	$(cleanup_silent) /bin/rm -f $(patsubst %.o,%.d,$(bin)CCQENu.o $(bin)CCQENuRecoUtils.o) $(patsubst %.o,%.dep,$(bin)CCQENu.o $(bin)CCQENuRecoUtils.o) $(patsubst %.o,%.d.stamp,$(bin)CCQENu.o $(bin)CCQENuRecoUtils.o)
	$(cleanup_silent) cd $(bin); /bin/rm -rf CCQENu_deps CCQENu_dependencies.make

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/lib
CCQENuinstallname = $(library_prefix)CCQENu$(library_suffix).$(shlibsuffix)

CCQENu :: CCQENuinstall

install :: CCQENuinstall

CCQENuinstall :: $(install_dir)/$(CCQENuinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(CCQENuinstallname) :: $(bin)$(CCQENuinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(CCQENuinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##CCQENuclean :: CCQENuuninstall

uninstall :: CCQENuuninstall

CCQENuuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(CCQENuinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#-- end of libary -----------------------
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),CCQENuclean)
ifneq ($(MAKECMDGOALS),uninstall)

#$(bin)CCQENu_dependencies.make :: dirs

ifndef QUICK
$(bin)CCQENu_dependencies.make : $(src)CCQENu.cpp $(src)CCQENuRecoUtils.cpp $(use_requirements) $(cmt_final_setup_CCQENu)
	$(echo) "(CCQENu.make) Rebuilding $@"; \
	  $(build_dependencies) CCQENu -all_sources -out=$@ $(src)CCQENu.cpp $(src)CCQENuRecoUtils.cpp
endif

#$(CCQENu_dependencies)

-include $(bin)CCQENu_dependencies.make

endif
endif
#-- end of dependency -------------------
#-- start of cpp_library -----------------

ifneq ($(MAKECMDGOALS),CCQENuclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)CCQENu.d
endif
endif


$(bin)$(binobj)CCQENu.o $(bin)$(binobj)CCQENu.d : $(src)CCQENu.cpp  $(use_requirements) $(cmt_final_setup_CCQENu)
	$(cpp_echo) $(src)CCQENu.cpp
	@mkdir -p $(@D)
	$(cpp_silent) $(cppcomp) $(use_pp_cppflags) $(CCQENu_pp_cppflags) $(app_CCQENu_pp_cppflags) $(CCQENu_pp_cppflags) $(use_cppflags) $(CCQENu_cppflags) $(lib_CCQENu_cppflags) $(app_CCQENu_cppflags) $(CCQENu_cppflags) $(CCQENu_cpp_cppflags)  -MP -MMD -MT $(bin)$(binobj)CCQENu.o -MT $(bin)$(binobj)CCQENu.d -MF $(bin)$(binobj)CCQENu.d -o $(bin)$(binobj)CCQENu.o $(src)CCQENu.cpp


#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq ($(MAKECMDGOALS),CCQENuclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)CCQENuRecoUtils.d
endif
endif


$(bin)$(binobj)CCQENuRecoUtils.o $(bin)$(binobj)CCQENuRecoUtils.d : $(src)CCQENuRecoUtils.cpp  $(use_requirements) $(cmt_final_setup_CCQENu)
	$(cpp_echo) $(src)CCQENuRecoUtils.cpp
	@mkdir -p $(@D)
	$(cpp_silent) $(cppcomp) $(use_pp_cppflags) $(CCQENu_pp_cppflags) $(app_CCQENu_pp_cppflags) $(CCQENuRecoUtils_pp_cppflags) $(use_cppflags) $(CCQENu_cppflags) $(lib_CCQENu_cppflags) $(app_CCQENu_cppflags) $(CCQENuRecoUtils_cppflags) $(CCQENuRecoUtils_cpp_cppflags)  -MP -MMD -MT $(bin)$(binobj)CCQENuRecoUtils.o -MT $(bin)$(binobj)CCQENuRecoUtils.d -MF $(bin)$(binobj)CCQENuRecoUtils.d -o $(bin)$(binobj)CCQENuRecoUtils.o $(src)CCQENuRecoUtils.cpp


#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: CCQENuclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(CCQENu.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENu.make): $@: File no longer generated" >&2; exit 0; fi
else
.DEFAULT::
	$(echo) "(CCQENu.make) PEDANTIC: $@: No rule for such target" >&2
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENu.make): $@: File no longer generated" >&2; exit 0;\
	 elif test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_CCQENu)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENu.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr $@ : '.*/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENu.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENu.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

CCQENuclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library CCQENu
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)CCQENu$(library_suffix).a $(library_prefix)CCQENu$(library_suffix).s? CCQENu.stamp CCQENu.shstamp
#-- end of cleanup_library ---------------
