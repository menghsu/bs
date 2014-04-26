#include <linux/init.h>
#include <linux/module.h> 
#include <linux/moduleparam.h>

static char *tekkaman = "Tekkaman";
static int howmany = 1;
module_param(howmany, int, S_IRUGO);
module_param(tekkaman, charp, S_IRUGO);

static int hello_init(void)
{
	int i;

        printk(KERN_ALERT "Hello, Linux ！\n");
        
	for (i = 0; i < howmany; i++)	{
		printk(KERN_ALERT "(%d) Hello, %s\n", i, tekkaman);
    }

            return 0;
}

static void hello_exit(void)
{
        printk(KERN_ALERT "Goodbye, Linux ！\n");
}

module_init(hello_init);
module_exit(hello_exit);

EXPORT_SYMBOL(hello_init);

MODULE_DESCRIPTION("hello_linux test module");
MODULE_ALIAS("hello_world");
MODULE_INFO(tekkaman, "ninja");
MODULE_VERSION("v1.0");
MODULE_AUTHOR("Tekkaman");
MODULE_LICENSE("Dual BSD/GPL");
