version=1.0
id=GeRtiTM
nrLogger=1
id=lGeRtiTM enable=1 level=I group=ff ctxt="GeRtiTM"
nrObserver=1
id=label fmt="%s"
nrFormat=1
id=f2 ctxt="step" vtxt="label label"
nrEvent=5
id=GeRti_TM_d enable=1 level=D group=10 idLogger=lGeRtiTM idFormat=f2 ctxtHead="" ctxt="debug"
id=GeRti_TM_e enable=1 level=E group=10 idLogger=lGeRtiTM idFormat=f2 ctxtHead="" ctxt="error"
id=GeRti_TM_i enable=1 level=I group=10 idLogger=lGeRtiTM idFormat=f2 ctxtHead="" ctxt="info"
id=GeRti_TM_mu_d enable=1 level=D group=10 idLogger=lGeRtiTM idFormat=f2 ctxtHead="" ctxt="info"
id=GeRti_TM_w enable=1 level=W group=10 idLogger=lGeRtiTM idFormat=f2 ctxtHead="" ctxt="warning"
