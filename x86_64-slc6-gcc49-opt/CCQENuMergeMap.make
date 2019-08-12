#-- start of make_header -----------------

#====================================
#  Document CCQENuMergeMap
#
#   Generated Mon Aug 12 17:20:08 2019  by sultana
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_CCQENuMergeMap_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_CCQENuMergeMap_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_CCQENuMergeMap

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENuMergeMap = $(CCQENu_tag)_CCQENuMergeMap.make
cmt_local_tagfile_CCQENuMergeMap = $(bin)$(CCQENu_tag)_CCQENuMergeMap.make

else

tags      = $(tag),$(CMTEXTRATAGS)

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENuMergeMap = $(CCQENu_tag).make
cmt_local_tagfile_CCQENuMergeMap = $(bin)$(CCQENu_tag).make

endif

include $(cmt_local_tagfile_CCQENuMergeMap)
#-include $(cmt_local_tagfile_CCQENuMergeMap)

ifdef cmt_CCQENuMergeMap_has_target_tag

cmt_final_setup_CCQENuMergeMap = $(bin)setup_CCQENuMergeMap.make
#cmt_final_setup_CCQENuMergeMap = $(bin)CCQENu_CCQENuMergeMapsetup.make
cmt_local_CCQENuMergeMap_makefile = $(bin)CCQENuMergeMap.make

else

cmt_final_setup_CCQENuMergeMap = $(bin)setup.make
#cmt_final_setup_CCQENuMergeMap = $(bin)CCQENusetup.make
cmt_local_CCQENuMergeMap_makefile = $(bin)CCQENuMergeMap.make

endif

cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)CCQENusetup.make

#CCQENuMergeMap :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'CCQENuMergeMap'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = CCQENuMergeMap/
#CCQENuMergeMap::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
# File: cmt/fragments/merge_rootmap_header
# Author: Sebastien Binet (binet@cern.ch)

# Makefile fragment to merge a <library>.rootmap file into a single
# <project>.rootmap file in the (lib) install area
# If no InstallArea is present the fragment is dummy


.PHONY: CCQENuMergeMap CCQENuMergeMapclean

# default is already '#'
#genmap_comment_char := "'#'"

rootMapRef    := ../$(tag)/CCQENu.rootmap

ifdef CMTINSTALLAREA
rootMapDir    := ${CMTINSTALLAREA}/$(tag)/lib
mergedRootMap := $(rootMapDir)/$(project).rootmap
stampRootMap  := $(rootMapRef).stamp
else
rootMapDir    := ../$(tag)
mergedRootMap := 
stampRootMap  :=
endif

CCQENuMergeMap :: $(stampRootMap) $(mergedRootMap)
	@:

.NOTPARALLEL : $(stampRootMap) $(mergedRootMap)

$(stampRootMap) $(mergedRootMap) :: $(rootMapRef)
	@echo "Running merge_rootmap  CCQENuMergeMap" 
	$(merge_rootmap_cmd) --do-merge \
         --input-file $(rootMapRef) --merged-file $(mergedRootMap)

CCQENuMergeMapclean ::
	$(cleanup_silent) $(merge_rootmap_cmd) --un-merge \
         --input-file $(rootMapRef) --merged-file $(mergedRootMap) ;
	$(cleanup_silent) $(remove_command) $(stampRootMap)
libCCQENu_so_dependencies = ../x86_64-slc6-gcc49-opt/libCCQENu.so
#-- start of cleanup_header --------------

clean :: CCQENuMergeMapclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(CCQENuMergeMap.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENuMergeMap.make): $@: File no longer generated" >&2; exit 0; fi
else
.DEFAULT::
	$(echo) "(CCQENuMergeMap.make) PEDANTIC: $@: No rule for such target" >&2
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENuMergeMap.make): $@: File no longer generated" >&2; exit 0;\
	 elif test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_CCQENuMergeMap)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuMergeMap.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr $@ : '.*/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuMergeMap.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuMergeMap.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

CCQENuMergeMapclean ::
#-- end of cleanup_header ---------------
