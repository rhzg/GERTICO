version=1.0
id=GeRtiFM
nrLogger=1
id=lGeRtiFM enable=1 level=I group=81 ctxt="GeRtiFM"
nrObserver=1
id=label fmt="%s"
nrFormat=1
id=f2 ctxt="step" vtxt="label label"
nrEvent=7
id=GeRti_FM_feds_i enable=1 level=I group=01 idLogger=lGeRtiFM idFormat=f2 ctxtHead="" ctxt="debug"
id=GeRti_FM_sync_i enable=0 level=I group=01 idLogger=lGeRtiFM idFormat=f2 ctxtHead="" ctxt="debug"
id=GeRti_FM_save_restore_i enable=0 level=I group=01 idLogger=lGeRtiFM idFormat=f2 ctxtHead="" ctxt="debug"
id=GeRti_FM_d enable=1 level=D group=01 idLogger=lGeRtiFM idFormat=f2 ctxtHead="" ctxt="debug"
id=GeRti_FM_e enable=1 level=E group=01 idLogger=lGeRtiFM idFormat=f2 ctxtHead="" ctxt="error"
id=GeRti_FM_i enable=1 level=I group=01 idLogger=lGeRtiFM idFormat=f2 ctxtHead="" ctxt="info"
id=GeRti_FM_w enable=1 level=W group=01 idLogger=lGeRtiFM idFormat=f2 ctxtHead="" ctxt="warning"
