version=1.0
id=GeRtiOM
nrLogger=1
id=lGeRtiOM enable=1 level=D group=ff ctxt="GeRtiOM"
nrObserver=1
id=label fmt="%s"
nrFormat=1
id=f2 ctxt="step" vtxt="label label"
nrEvent=4
id=GeRti_OM_d enable=1 level=D group=04 idLogger=lGeRtiOM idFormat=f2 ctxtHead="" ctxt="debug"
id=GeRti_OM_e enable=1 level=E group=04 idLogger=lGeRtiOM idFormat=f2 ctxtHead="" ctxt="error"
id=GeRti_OM_i enable=1 level=I group=04 idLogger=lGeRtiOM idFormat=f2 ctxtHead="" ctxt="info"
id=GeRti_OM_w enable=1 level=W group=04 idLogger=lGeRtiOM idFormat=f2 ctxtHead="" ctxt="warning"
