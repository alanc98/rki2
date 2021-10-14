qemu-system-microblazeel \
-no-reboot \
-M microblaze-fdt-plnx \
-m 256 \
-serial mon:stdio \
-display none \
-dtb kcu105.dtb \
-kernel rki.elf 
