# unsigned to signed need take some attention, such like iinc.

# fix is_instance_of

# if_icmpge point set to -> frame->count > 21452,  
# ConcurrentHashMap.equals has effect a endless loop, 
# probably in method Traverser.advance. 
# need track and explain it.