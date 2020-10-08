# unsigned to signed need take some attention, such like iinc.

# fix is_instance_of

# if_icmpge point set to -> frame->count > 21452,  
# ConcurrentHashMap.equals has effect a endless loop, 
# probably in method Traverser.advance. 
# need track and explain it.

# Properties fields is NULL , fix it


# ladd may be error, long type calc has some problem, set frame->count greater then 7984 , fix it
# look like the store type of the long type push to stack cause next error 

# if_icmpge set to 19742

# File.getName return a name ".", is not right
# point to ClassLoader.c findBuiltinLib and System.c mapLibraryName

# File( fs.resolve(parent, child) ) has some problem, set point to 99913 and find it.
# look like native method System.arraycopy is wrong, point at 100526

# AccessController_doPrivileged need a return value

# compete invokedynamic instruction, don't forget initPhase2 and 3

# LD_LIBRARY_PATH=/usr/lib/jvm/java-11-openjdk-amd64/lib/server

# Object.clone not complete
# Thread.isAlive not complete
# Thread.start0 not complete, need lock

# wait has some problem, may be the key is complete the synchronized invoke method.