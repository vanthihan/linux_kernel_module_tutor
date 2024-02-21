# linux_kmod

Check linux kernel header version:

`uname -r`


Install kernel header:

```undefined
sudo apt-get install kmod linux-headers-6.5.0-17-generic
```

```undefined
sudo apt install gcc-12
```

Simple Makefile:

```undefined
obj-m += hello-1.o

PWD := $(CURDIR)

all:
	make -C /lib/modules/5.4.0-80-generic/build M=$(PWD) modules

clean:
	make -C /lib/modules/5.4.0-80-generic/build M=$(PWD) clean

```

Commands:

`modinfo hello-1.ko`

`lsmod | grep hello`

`insmod hello-1.ko`

`rmmod hello-1.ko`


Build warning with:

`Skipping BTF generation for /home/work_dir/hello-1/hello-1.ko due to unavailability of vmlinux`

```undefined
ls -la /sys/kernel/ | grep btf

sudo apt install dwarves
sudo cp /sys/kernel/btf/vmlinux /usr/lib/modules/`uname -r`/build/
```
