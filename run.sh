echo "Cleaning up..."

rm -r isodir/

echo "Building scripts..."

i686-elf-as boot.s -o boot.o
i686-elf-gcc -c kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c terminal.cpp -o terminal.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c keyboard.cpp -o keyboard.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c string.cpp -o string.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib terminal.o keyboard.o boot.o kernel.o string.o -lgcc

echo "Building ISO..."

mkdir -p isodir/boot/grub

cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir

echo "Running..."
qemu-system-i386 -cdrom myos.iso
