version=1.0
id=GeRtiDM
nrLogger=1
id=lGeRtiDM enable=1 level=D group=ff ctxt="GeRtiDM"
nrObserver=1
id=label fmt="%s"
nrFormat=1
id=f2 ctxt="step" vtxt="label label"
nrEvent=4
id=GeRti_DM_d enable=1 level=D group=02 idLogger=lGeRtiDM idFormat=f2 ctxtHead="" ctxt="debug"
id=GeRti_DM_e enable=1 level=E group=02 idLogger=lGeRtiDM idFormat=f2 ctxtHead="" ctxt="error"
id=GeRti_DM_i enable=1 level=I group=02 idLogger=lGeRtiDM idFormat=f2 ctxtHead="" ctxt="info"
id=GeRti_DM_w enable=1 level=W group=02 idLogger=lGeRtiDM idFormat=f2 ctxtHead="" ctxt="warning"
