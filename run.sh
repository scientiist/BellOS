export PATH="$HOME/opt/cross/bin:$PATH"

echo "Cleaning up..."

rm -r isodir/
rm -r build/

echo "Building scripts..."

mkdir build/

i686-elf-as sys/kernel/boot.s -o build/boot.o
i686-elf-gcc -c sys/kernel/core/kernel.cpp -o build/kernel.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c sys/kernel/video/videobuffer.cpp -o build/videobuffer.o -ffreestanding -O2 -Wall -Wextra

i686-elf-gcc -c sys/libraries/string/string.cpp  -o build/string.o -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c sys/libraries/time/time.cpp  -o build/time.o -ffreestanding -O2 -Wall -Wextra

i686-elf-gcc -c sys/opt/terminal/terminal.cpp -o build/terminal.o -ffreestanding -O2 -Wall -Wextra


i686-elf-gcc -T sys/kernel/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib build/*.o -lgcc
echo "Building ISO..."

mkdir -p isodir/boot/grub

cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir

echo "Running..."
qemu-system-i386 -kernel myos.bin
