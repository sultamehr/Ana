#-- start of make_header -----------------

#====================================
#  Document CCQENuConfDbMerge
#
#   Generated Mon Oct  7 06:03:08 2019  by sultana
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_CCQENuConfDbMerge_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_CCQENuConfDbMerge_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_CCQENuConfDbMerge

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENuConfDbMerge = $(CCQENu_tag)_CCQENuConfDbMerge.make
cmt_local_tagfile_CCQENuConfDbMerge = $(bin)$(CCQENu_tag)_CCQENuConfDbMerge.make

else

tags      = $(tag),$(CMTEXTRATAGS)

CCQENu_tag = $(tag)

#cmt_local_tagfile_CCQENuConfDbMerge = $(CCQENu_tag).make
cmt_local_tagfile_CCQENuConfDbMerge = $(bin)$(CCQENu_tag).make

endif

include $(cmt_local_tagfile_CCQENuConfDbMerge)
#-include $(cmt_local_tagfile_CCQENuConfDbMerge)

ifdef cmt_CCQENuConfDbMerge_has_target_tag

cmt_final_setup_CCQENuConfDbMerge = $(bin)setup_CCQENuConfDbMerge.make
#cmt_final_setup_CCQENuConfDbMerge = $(bin)CCQENu_CCQENuConfDbMergesetup.make
cmt_local_CCQENuConfDbMerge_makefile = $(bin)CCQENuConfDbMerge.make

else

cmt_final_setup_CCQENuConfDbMerge = $(bin)setup.make
#cmt_final_setup_CCQENuConfDbMerge = $(bin)CCQENusetup.make
cmt_local_CCQENuConfDbMerge_makefile = $(bin)CCQENuConfDbMerge.make

endif

cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)CCQENusetup.make

#CCQENuConfDbMerge :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'CCQENuConfDbMerge'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = CCQENuConfDbMerge/
#CCQENuConfDbMerge::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
# File: cmt/fragments/merge_genconfDb_header
# Author: Sebastien Binet (binet@cern.ch)

# Makefile fragment to merge a <library>_confDb.py file into a single
# <project>_merged_confDb.py file in the (python) install area
# Note that <project> is massaged to get a valid python module name
# (ie: remove dots and dashes)

.PHONY: CCQENuConfDbMerge CCQENuConfDbMergeclean

# default is already '#'
#genconfDb_comment_char := "'#'"

instdir      := ${CMTINSTALLAREA}$(shared_install_subdir)
confDbRef    := /minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana/CCQENu/genConf/CCQENu/CCQENu_confDb.py
stampConfDb  := $(confDbRef).stamp
mergedConfDb := $(instdir)/python/$(subst .,_,$(subst -,_,$(project)))_merged_confDb.py

CCQENuConfDbMerge :: $(stampConfDb) $(mergedConfDb)
	@:

.NOTPARALLEL : $(stampConfDb) $(mergedConfDb)

$(stampConfDb) $(mergedConfDb) :: $(confDbRef)
	@echo "Running merge_genconfDb  CCQENuConfDbMerge"
	$(merge_genconfDb_cmd) \
          --do-merge \
          --input-file $(confDbRef) \
          --merged-file $(mergedConfDb)

CCQENuConfDbMergeclean ::
	$(cleanup_silent) $(merge_genconfDb_cmd) \
          --un-merge \
          --input-file $(confDbRef) \
          --merged-file $(mergedConfDb)	;
	$(cleanup_silent) $(remove_command) $(stampConfDb)
libCCQENu_so_dependencies = ../x86_64-slc6-gcc49-opt/libCCQENu.so
#-- start of cleanup_header --------------

clean :: CCQENuConfDbMergeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(CCQENuConfDbMerge.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENuConfDbMerge.make): $@: File no longer generated" >&2; exit 0; fi
else
.DEFAULT::
	$(echo) "(CCQENuConfDbMerge.make) PEDANTIC: $@: No rule for such target" >&2
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(CCQENuConfDbMerge.make): $@: File no longer generated" >&2; exit 0;\
	 elif test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_CCQENuConfDbMerge)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuConfDbMerge.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr $@ : '.*/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuConfDbMerge.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(CCQENuConfDbMerge.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

CCQENuConfDbMergeclean ::
#-- end of cleanup_header ---------------
