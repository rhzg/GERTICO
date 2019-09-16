version=1.0
id=Ut
nrLogger=4
id=lUt enable=1 level=I group=ff ctxt="Ut"
id=lUtTrigger enable=1 level=I group=ff ctxt="Ut"
id=lUtError enable=1 level=E group=ff ctxt="Ut"
id=lUtAdmin enable=1 level=I group=ff ctxt="Ut"
nrObserver=1
id=id fmt=%s
nrFormat=1
id=f1 fmt=ctxt="id" vtxt="id"
nrEvent=11
id=serviceSS enable=1 level=I group=ff idLogger=lUt idFormat=f1 ctxt="service-SEND"
id=serviceSR enable=1 level=I group=ff idLogger=lUt idFormat=f1 ctxt="service-RECV"
id=serviceSA enable=1 level=I group=ff idLogger=lUt idFormat=f1 ctxt="service-ATTR"
id=comment enable=1 level=I group=ff idLogger=lUt idFormat=f1 ctxt="comment     "
id=resume enable=1 level=I group=ff idLogger=lUt idFormat=f1 ctxt="resume      "
id=admin enable=1 level=I group=ff idLogger=lUtAdmin idFormat=f1 ctxt="admin       "
id=error enable=1 level=E group=ff idLogger=lUtError idFormat=f1 ctxt="exp. error  "
id=uerror enable=1 level=E group=ff idLogger=lUtError idFormat=f1 ctxt="unexp. error"
id=nerror enable=1 level=E group=ff idLogger=lUtError idFormat=f1 ctxt="undet. error"
id=dataerror enable=1 level=E group=ff idLogger=lUtError idFormat=f1 ctxt="data error  "
id=trigger enable=1 level=I group=ff idLogger=lUtTrigger idFormat=f1 ctxt="trigger     "

