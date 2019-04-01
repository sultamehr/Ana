if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/minerva.opensciencegrid.org/minerva/software_releases/lcgcmake/lcg_61a/external/cmt/v1r20p20090520/x86_64-slc6-gcc49-opt/CMT/v1r20p20090520; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=CCQENu -version=${MINERVA_RELEASE} -path=/minerva/app/users/sultana/cmtuser/Minerva_v21r1p1/Ana $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

