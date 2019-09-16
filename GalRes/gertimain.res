version=1.0
id=gertimain
nrLogger=1
id=lgertimain enable=1 level=D group=ff ctxt="mainServer"
nrObserver=0
nrFormat=1
id=f0 ctxt="step"
nrEvent=5
id=r_m enable=1 level=I group=ff idLogger=lgertimain idFormat=f0 ctxtHead="" ctxt="enter"
id=r_d enable=1 level=D group=ff idLogger=lgertimain idFormat=f0 ctxtHead="" ctxt="debug"
id=r_e enable=1 level=E group=ff idLogger=lgertimain idFormat=f0 ctxtHead="" ctxt="error"
id=r_i enable=1 level=I group=ff idLogger=lgertimain idFormat=f0 ctxtHead="" ctxt="info"
id=r_w enable=1 level=W group=ff idLogger=lgertimain idFormat=f0 ctxtHead="" ctxt="warning"
