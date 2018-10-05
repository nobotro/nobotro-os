
all:
	nasm -f bin ../boot/bootloader.asm -o bootloader.bin
	gcc -ffreestanding -c kernel.c -o kernel.o
	gcc -ffreestanding -c ../lib/stdio.c -o stdio.o
	gcc -ffreestanding -c ../lib/stdlib.c -o stdlib.o
	gcc -ffreestanding -c ../lib/string.c -o string.o
	nasm -f elf64 kernel_head.asm -o kernel_head.o
	ld -o kernel.bin -Ttext 0x1000 kernel_head.o kernel.o stdlib.o stdio.o string.o --oformat binary
	cat bootloader.bin kernel.bin > nobotro_os.img
	rm *.bin *.o

all2:
	nasm -f bin ../boot/bootloader.asm -o bootloader.bin
	gcc  -ffreestanding -fno-stack-protector  -fno-pie -c kernel.c -o kernel.o -m32
	gcc -ffreestanding -fno-stack-protector  -fno-pie -c ../lib/stdio.c -o stdio.o  -m32
	gcc -ffreestanding -fno-stack-protector  -fno-pie -c ../lib/stdlib.c -o stdlib.o  -m32
	gcc  -ffreestanding -fno-stack-protector  -fno-pie -c ../lib/string.c -o string.o  -m32
	gcc  -ffreestanding -fno-stack-protector  -fno-pie -c ../drivers/video.c -o video.o  -m32
	gcc  -ffreestanding -fno-stack-protector  -fno-pie -c ../drivers/keyboard.c -o keyboard.o  -m32
	nasm  -f elf32 kernel_head.asm -o kernel_head.o 
	ld  -melf_i386 -o kernel.bin -Ttext 0x1000 kernel_head.o kernel.o stdlib.o stdio.o string.o video.o keyboard.o --oformat binary -T link.ld
	cat bootloader.bin kernel.bin > ../nobotro_os.img
	rm *.bin *.o


all3:
	nasm -f bin bootloader.asm -o bootloader.bin
	gcc -ffreestanding  -fno-pie -c kernel.c -o kernel.o -m64
	gcc -ffreestanding  -fno-pie -c lib/stdio.c -o stdio.o  -m64
	gcc -ffreestanding  -fno-pie -c lib/stdlib.c -o stdlib.o  -m64
	gcc -ffreestanding  -fno-pie -c lib/string.c -o string.o  -m64
	nasm -f elf64 kernel_head.asm -o kernel_head.o
	ld -melf_x86_64 -o kernel.bin -Ttext 0x1000 kernel_head.o kernel.o stdlib.o stdio.o string.o --oformat binary
	cat bootloader.bin kernel.bin > nobotro_os.img
	rm *.bin *.o

flash:
	dd if=/dev/zero bs=512  count=200 of=/dev/sdb
	dd if=../nobotro_os.img of=/dev/sdb


emu: 
	qemu-system-x86_64 ../nobotro_os.img