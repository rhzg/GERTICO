version=1.0
id=GeRtiDDM
nrLogger=1
id=lGeRtiDDM enable=1 level=D group=ff ctxt="GeRtiDDM"
nrObserver=1
id=label fmt="%s"
nrFormat=1
id=f2 ctxt="step" vtxt="label label"
nrEvent=4
id=GeRti_DDM_d enable=1 level=D group=20 idLogger=lGeRtiDDM idFormat=f2 ctxtHead="" ctxt="debug"
id=GeRti_DDM_e enable=1 level=E group=20 idLogger=lGeRtiDDM idFormat=f2 ctxtHead="" ctxt="error"
id=GeRti_DDM_i enable=1 level=I group=20 idLogger=lGeRtiDDM idFormat=f2 ctxtHead="" ctxt="info"
id=GeRti_DDM_w enable=1 level=W group=20 idLogger=lGeRtiDDM idFormat=f2 ctxtHead="" ctxt="warning"
