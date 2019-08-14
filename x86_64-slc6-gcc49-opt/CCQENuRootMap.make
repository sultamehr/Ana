#-- start of make_header -----------------

#====================================
#  Document CCQENuRootMap
#
#   Generated Wed Aug 14 02:45:46 2019  by sultana
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_CCQENuRootMap_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_CCQENuRootMap_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_CCQENuRootMap

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENuRootMap = $(CCQENu_tag)_CCQENuRootMap.make
cmt_local_tagfile_CCQENuRootMap = $(bin)$(CCQENu_tag)_CCQENuRootMap.make

else

tags      = $(tag),$(CMTEXTRATAGS)

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENuRootMap = $(CCQENu_tag).make
cmt_local_tagfile_CCQENuRootMap = $(bin)$(CCQENu_tag).make

endif

include $(cmt_local_tagfile_CCQENuRootMap)
#-include $(cmt_local_tagfile_CCQENuRootMap)

ifdef cmt_CCQENuRootMap_has_target_tag

cmt_final_setup_CCQENuRootMap = $(bin)setup_CCQENuRootMap.make
#cmt_final_setup_CCQENuRootMap = $(bin)CCQENu_CCQENuRootMapsetup.make
cmt_local_CCQENuRootMap_makefile = $(bin)CCQENuRootMap.make

else

cmt_final_setup_CCQENuRootMap = $(bin)setup.make
#cmt_final_setup_CCQENuRootMap = $(bin)CCQENusetup.make
cmt_local_CCQENuRootMap_makefile = $(bin)CCQENuRootMap.make

endif

cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)CCQENusetup.make

#CCQENuRootMap :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'CCQENuRootMap'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = CCQENuRootMap/
#CCQENuRootMap::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
##
rootmapfile = CCQENu.rootmap
ROOTMAP_DIR = ../$(tag)
fulllibname = libCCQENu.$(shlibsuffix)

CCQENuRootMap :: ${ROOTMAP_DIR}/$(rootmapfile)
	@:

${ROOTMAP_DIR}/$(rootmapfile) :: $(bin)$(fulllibname)
	@echo 'Generating rootmap file for $(fulllibname)'
	cd ../$(tag);$(genmap_cmd) -i $(fulllibname) -o ${ROOTMAP_DIR}/$(rootmapfile) $(CCQENuRootMap_genmapflags)

install :: CCQENuRootMapinstall
CCQENuRootMapinstall :: CCQENuRootMap

uninstall :: CCQENuRootMapuninstall
CCQENuRootMapuninstall :: CCQENuRootMapclean

CCQENuRootMapclean ::
	@echo 'Deleting $(rootmapfile)'
	@rm -f ${ROOTMAP_DIR}/$(rootmapfile)

#-- start of cleanup_header --------------

clean :: CCQENuRootMapclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(CCQENuRootMap.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENuRootMap.make): $@: File no longer generated" >&2; exit 0; fi
else
.DEFAULT::
	$(echo) "(CCQENuRootMap.make) PEDANTIC: $@: No rule for such target" >&2
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENuRootMap.make): $@: File no longer generated" >&2; exit 0;\
	 elif test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_CCQENuRootMap)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuRootMap.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr $@ : '.*/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuRootMap.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuRootMap.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

CCQENuRootMapclean ::
#-- end of cleanup_header ---------------
