version=1.0
id=GeRtiSS
nrLogger=1
id=lGeRtiSS enable=1 level=D group=ff ctxt="GeRtiSS"
nrObserver=1
id=label fmt="%s"
nrFormat=1
id=f2 ctxt="step" vtxt="label label"
nrEvent=4
id=GeRti_SS_d enable=1 level=D group=40 idLogger=lGeRtiSS idFormat=f2 ctxtHead="" ctxt="debug"
id=GeRti_SS_e enable=1 level=E group=40 idLogger=lGeRtiSS idFormat=f2 ctxtHead="" ctxt="error"
id=GeRti_SS_i enable=1 level=I group=40 idLogger=lGeRtiSS idFormat=f2 ctxtHead="" ctxt="info"
id=GeRti_SS_w enable=1 level=W group=40 idLogger=lGeRtiSS idFormat=f2 ctxtHead="" ctxt="warning"
