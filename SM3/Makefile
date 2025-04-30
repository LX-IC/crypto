linux: sm3.c sm3test.c
	gcc sm3.c sm3test.c sm3.h -o sm3
     
arm: sm3.c sm3test.c
	arm-linux-gnueabi-gcc -static sm3.c sm3test.c sm3.h -o sm3
     
linux-sim:
	./sm3

qemu-sim:
	qemu-arm sm3
       
gem5-sim:
	/home/x/gem5/build/ARM/gem5.opt /home/x/qemu-arm-test/sm3_qemu_gem5/simple-arm.py	 

clean:
	rm -f sm3
