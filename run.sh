export PATH="$HOME/opt/cross/bin:$PATH"

echo "Cleaning up..."

rm -r isodir/

echo "Building scripts..."


i686-elf-as sys/kernel/boot.s -o build/boot.o
i686-elf-gcc -c sys/kernel/core/kernel.cpp -o build/kernel.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c sys/kernel/video/videobuffer.cpp -o build/videobuffer.o -ffreestanding -O2 -Wall -Wextra

i686-elf-gcc -c sys/libraries/string/string.cpp -o build/string.o -ffreestanding -O2 -Wall -Wextra
cd build/

i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o videobuffer.o string.o -lgcc
cd ../
echo "Building ISO..."

mkdir -p isodir/boot/grub

cp build/myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o build/myos.iso isodir

echo "Running..."
qemu-system-i386 -kernel build/myos.bin
