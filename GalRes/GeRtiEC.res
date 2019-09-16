version=1.0
id=GeRtiEC
nrLogger=1
id=lGeRtiEC enable=0 level=D group=ff ctxt="GeRtiEC"
nrObserver=1
id=label fmt="%s"
nrFormat=1
id=f2 ctxt="step" vtxt="label label"
nrEvent=4
id=GeRti_EC_d enable=1 level=D group=80 idLogger=lGeRtiEC idFormat=f2 ctxtHead="" ctxt="debug"
id=GeRti_EC_e enable=1 level=E group=80 idLogger=lGeRtiEC idFormat=f2 ctxtHead="" ctxt="error"
id=GeRti_EC_i enable=1 level=I group=80 idLogger=lGeRtiEC idFormat=f2 ctxtHead="" ctxt="info"
id=GeRti_EC_w enable=1 level=W group=80 idLogger=lGeRtiEC idFormat=f2 ctxtHead="" ctxt="warning"
