# Используем символ - "@" для того, чтобы не выводить в консоль команды целей.

all: static_lib dynamic_lib

ALL_OBJS = main.c f1.c f2.c
#FUNC = f1.c f2.c

# Ф-ия очистки
.PHONY: clean 


static_lib:
	# Использование статической библиотеки

	@# Компиляция
	@gcc -c ${ALL_OBJS}
	@# Арихивируем наши ф-ия для библиотеки
	@ar rc libfs.a f1.o f2.o
	@# Добавляем индекс символов
	@ranlib libfs.a
	@# Компилируем и собираем
	@gcc main.c -L. -lfs -o rezult_static
	
	@./rezult_static


dynamic_lib:
	# Использование динамической библиотеки
	
	@# Компиляция
	@gcc -c main.c
	@gcc -fPIC -c f1.c f2.c
	@# Создаем динамическую библиотеку
	@gcc -shared -o libfsdyn.so f1.o f2.o
	@# Собираем файл
	@gcc main.o -L. -lfsdyn -o rezult_dynamic
	
	@#LD_LIBRARY_PATH=/home/pavel/5module/5LR     Эти три строки не будут работать, т.к. в Makefile 
	@#export LD_LIBRARY_PATH                      каждая строка выполняется отдельном процессе, которые
	@#./rezult_dynamic                            наследуют собственные переменные среды, установленные в его области видимости

	@# Устанавливаем переменную среды и вызываем наш файл
	@LD_LIBRARY_PATH=/home/pavel/5module/5LR ./rezult_dynamic
	@# Обнуляем переменную среды
	@LD_LIBRARY_PATH=" "

# Ф-ия очистки
clean:
	@rm -f *.o *.a *.so rezult_static rezult_dynamic

