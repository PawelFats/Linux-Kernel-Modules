/*
* kbleds.c – мигает светодиодами клавиатуры, взависимости от того какой параметр задан в переменной "test" (по умолчанию - 7)
*/
#include <linux/init.h>
#include <linux/kd.h> /* Для KDSETLED. */
#include <linux/module.h>
#include <linux/tty.h> /* Для tty_struct. */
#include <linux/vt.h> /* Для MAX_NR_CONSOLES. */
#include <linux/vt_kern.h> /* Для fg_console. */
#include <linux/console_struct.h> /* Для vc_cons. */
#include <linux/printk.h> 
#include <linux/kobject.h> 
#include <linux/sysfs.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/string.h>

MODULE_DESCRIPTION("Example module illustrating the use of Keyboard LEDs.");
MODULE_LICENSE("GPL");

static struct timer_list my_timer;
static struct tty_driver *my_driver;

static int kbledstatus = 0;
static int test = 7;// cod

static struct kobject *example_kobject;

#define BLINK_DELAY HZ / 5
#define ALL_LEDS_ON 0x07
#define RESTORE_LEDS 0xFF


/* Функция my_timer_func периодически мигает светодиодами,
* вызывая для драйвера клавиатуры команду управления вводом-выводом
* KDSETLED. Дополнительную информацию по командам ввода-вывода
* смотрите в функции vt_ioctl() файла drivers/tty/vt/vt_ioctl.c.
*
* Аргумент KDSETLED попеременно устанавливается то на 7 (что приводит к
* активации режима LED_SHOW_IOCTL и загоранию всех светодиодов), то на
* 0xFF (любое значение выше 7 переключает режим обратно на
* LED_SHOW_FLAGS, в результате чего светодиоды отображают фактически
* статус клавиатуры). Подробности смотрите в функции setledstate() файла
* drivers/tty/vt/keyboard.c.
*/

static ssize_t test_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", test);
}

static ssize_t test_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    sscanf(buf, "%d", &test);
    return count;
}

 

static struct kobj_attribute test_attribute = __ATTR(test, 0660, test_show, test_store);

                                                   

static void my_timer_func(struct timer_list *unused)
{
	struct tty_struct *t = vc_cons[fg_console].d->port.tty;
	int *pstatus = &kbledstatus;
	if (*pstatus == test)
		*pstatus = RESTORE_LEDS;
   	else
   		*pstatus = test;
		
	(my_driver->ops->ioctl)(t, KDSETLED, *pstatus);
	my_timer.expires = jiffies + BLINK_DELAY;
	add_timer(&my_timer);
}

static int __init kbleds_init(void)
{
	int i;
	
	example_kobject = kobject_create_and_add("kbleds", kernel_kobj);
	if (!example_kobject)
		return -ENOMEM;

	if (sysfs_create_file(example_kobject, &test_attribute.attr)) {
		pr_debug("Failed to create the test file in /sys/kernel/kbleds\n");
		kobject_put(example_kobject);
		return -ENOMEM;
	}

	pr_info("kbleds: loading\n");
	pr_info("kbleds: fgconsole is %x\n", fg_console);
	
	for (i = 0; i < MAX_NR_CONSOLES; i++) {
		if (!vc_cons[i].d)
			break;
		pr_info("poet_atkm: console[%i/%i] #%i, tty %p\n", i, MAX_NR_CONSOLES,
				vc_cons[i].d->vc_num, (void *)vc_cons[i].d->port.tty);
	}
	
	pr_info("kbleds: finished scanning consoles\n");
	my_driver = vc_cons[fg_console].d->port.tty->driver;
	pr_info("kbleds: tty driver magic %x\n", my_driver->magic);
	/* Первая настройка таймера мигания светодиодов. */
	timer_setup(&my_timer, my_timer_func, 0);
	my_timer.expires = jiffies + BLINK_DELAY;
	add_timer(&my_timer);
	return 0;
}

static void __exit kbleds_cleanup(void)
{
	pr_debug ("Module un initialized successfully \n");
    kobject_put(example_kobject);
	pr_info("kbleds: unloading...\n");
	del_timer(&my_timer);
	(my_driver->ops->ioctl)(vc_cons[fg_console].d->port.tty, KDSETLED,RESTORE_LEDS);
}

module_init(kbleds_init);
module_exit(kbleds_cleanup);
