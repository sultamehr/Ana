if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/minerva.opensciencegrid.org/minerva/software_releases/lcgcmake/lcg_61a/external/cmt/v1r20p20090520/x86_64-slc6-gcc49-opt/CMT/v1r20p20090520
endif
source ${CMTROOT}/mgr/setup.csh
set tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set tempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=CCQENu -version=${MINERVA_RELEASE} -path=/minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana $* >${tempfile}; source ${tempfile}
/bin/rm -f ${tempfile}

