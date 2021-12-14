qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio \
 -machine virt,gic-version=3 -cpu cortex-a53 -m 128M -kernel rki.elf 
