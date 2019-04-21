import time

curtime = time.time()
while True:
	print("time is ", int((time.time()-curtime)*10**6), "uS")
	curtime = time.time()
