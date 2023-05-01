# Данный проект демнострирует простейший модуль ядра Linux
Исходный код модуля Hello World, хранится в файле - **hello.c**.

**Makefile** нужен для компиляции модуля ядра.

Используйте команду **make** для компиляции модуля ядра Hello World.

```
pavel@pavel:~/1lr$ make
make -C /lib/modules/5.19.0-41-generic/build M=/home/pavel/1lr modules
make[1]: вход в каталог «/usr/src/linux-headers-5.19.0-41-generic»
warning: the compiler differs from the one used to build the kernel
  The kernel was built by: x86_64-linux-gnu-gcc (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0
  You are using:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
  CC [M]  /home/pavel/1lr/hello.o
  MODPOST /home/pavel/1lr/Module.symvers
  CC [M]  /home/pavel/1lr/hello.mod.o
  LD [M]  /home/pavel/1lr/hello.ko
  BTF [M] /home/pavel/1lr/hello.ko
Skipping BTF generation for /home/pavel/1lr/hello.ko due to unavailability of vmlinux
make[1]: выход из каталога «/usr/src/linux-headers-5.19.0-41-generic»
```

>Команда "make" является инструментом для автоматизации сборки программного обеспечения. Когда вы запускаете "make", он анализирует содержимое файлов Makefile и определяет, какие исходные файлы (например, исходный код программы) должны быть скомпилированы и какие объектные файлы и исполняемые файлы должны быть созданы.
В процессе компиляции программы создаются временные файлы, такие как объектные файлы (.o), которые затем объединяются в итоговый исполняемый файл. Кроме того, в процессе сборки могут быть созданы файлы зависимостей (.d), файлы архивов (.a) и т.д. Эти файлы необходимы для правильной работы "make", чтобы он знал, какие файлы >должны быть перекомпилированы при изменении исходного кода.

Будет создан файл hello.ko, который является нашим образцом модуля ядра.

### Вставим и удалим образцы модуля ядра ###
Теперь, когда у нас есть наш файл hello.ko, мы можем вставить этот модуль в ядро с помощью команды insmod.

```
# insmod hello.ko

# dmesg | tail -1
[ 8394.731865] Hello world!

# rmmod hello.ko

# dmesg | tail -1
[ 8707.989819] Cleaning up module.
```

Когда модуль вставляется в ядро, будет вызван макрос module_init, который вызовет функцию hello_init. Аналогично, когда модуль удаляется с помощью rmmod, будет вызван макрос module_exit, который вызовет hello_exit. Используя команду dmesg, мы можем увидеть выходные данные образца модуля ядра.
