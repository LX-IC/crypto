linux: sm4.c
	gcc sm4.c sm4.h -o sm4
     
arm: sm4.c
	arm-linux-gnueabi-gcc -static sm4.c sm4.h -o sm4
     
linux-sim:
	./sm4

qemu-sim:
	qemu-arm sm4
       
gem5-sim:
	/home/x/gem5/build/ARM/gem5.opt /home/x/qemu-arm-test/sm4_qemu_gem5/simple-arm.py	 

clean:
	rm -f sm4
