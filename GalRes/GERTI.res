version=1.0
id=Master
out=STDOUT name=logger
nrLogger=0
nrObserver=0
nrFormat=0
nrAppender=2
id=std enable=1 level=I out=STDOUT
id=version enable=1 level=I out=STDOUT
nrLayout=2
id=lay fmt="%tr %el %ev"
id=info fmt="%Ev"
nrConnectAppenderLayout=2
idAppender=std idLayout=lay
idAppender=version idLayout=info
nrConnectAppenderLoggerGlobal=0
nrConnectAppenderLoggerLocal=8
idAppender=version idRepository=gertimain idLogger=lgertimain
idAppender=std idRepository=GeRtiDM idLogger=lGeRtiDM
idAppender=std idRepository=GeRtiDDM idLogger=lGeRtiDDM
idAppender=std idRepository=GeRtiFM idLogger=lGeRtiFM
idAppender=std idRepository=GeRtiOM idLogger=lGeRtiOM
idAppender=std idRepository=GeRtiOWM idLogger=lGeRtiOWM
idAppender=std idRepository=GeRtiSS idLogger=lGeRtiSS
idAppender=std idRepository=GeRtiTM idLogger=lGeRtiTM
