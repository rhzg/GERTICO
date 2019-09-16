version=1.0
id=Master
out=FILE name=xyz
nrLogger=0
nrObserver=0
nrFormat=0
nrAppender=2
id=std enable=0 level=E out=FILE name=Error
id=hla enable=1 level=D out=STDOUT
nrLayout=2
id=lay_1 fmt="%tr %el %ev %er %eI %eC"
id=lay_2 fmt="%tr %el %ev %er %eI %eC"
nrConnectAppenderLayout=2
idAppender=hla idLayout=lay_1
idAppender=std idLayout=lay_2
nrConnectAppenderLoggerGlobal=0
nrConnectAppenderLoggerLocal=10
idAppender=stdout idRepository=HLAServices idLogger=lRTIambServices
idAppender=stdout idRepository=HLAServices idLogger=lFEDambServices
idAppender=stdout idRepository=GeRtiDDM idLogger=lGeRtiDDM
idAppender=stdout idRepository=GeRtiDM idLogger=lGeRtiDM
idAppender=stdout idRepository=GeRtiEC idLogger=lGeRtiEC
idAppender=stdout idRepository=GeRtiFM idLogger=lGeRtiFM
idAppender=stdout idRepository=GeRtiOM idLogger=lGeRtiOM
idAppender=stdout idRepository=GeRtiOWM idLogger=lGeRtiOWM
idAppender=stdout idRepository=GeRtiSS idLogger=lGeRtiSS
idAppender=stdout idRepository=GeRtiTM idLogger=lGeRtiTM

//Unused
idAppender=std idRepository=GeRtiEvents idLogger=lGeRtiEvents
idAppender=hla idRepository=SENDER idLogger=lSENDER
