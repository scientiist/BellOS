echo "Cleaning up..."

rm -r isodir/

echo "Building scripts..."


i686-elf-as kernel/boot.s -o build/boot.o
i686-elf-gcc -c kernel/core/kernel.cpp -o build/kernel.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c kernel/core/terminal.cpp -o build/terminal.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c kernel/lib/string.cpp -o build/string.o -ffreestanding -O2 -Wall -Wextra
cd build/

i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib terminal.o boot.o kernel.o string.o -lgcc
cd ../
echo "Building ISO..."

mkdir -p isodir/boot/grub

cp build/myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o build/myos.iso isodir

echo "Running..."
qemu-system-i386 -cdrom build/myos.iso
