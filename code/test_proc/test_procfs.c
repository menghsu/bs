#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define PROC_NAME "yzy_test"
struct proc_dir_entry *my_proc_fs;
static char kernel_buf[128];

int read_proc(char *page, char **start, off_t off,int count, int *eof, void *data);

int write_proc(struct file *file, const char __user *buffer,unsigned long count, void *data);

static int __init module_test_init(void)
{
     memset(kernel_buf,0x00,128);
      my_proc_fs=create_proc_entry(PROC_NAME,0666,NULL);
       my_proc_fs->read_proc=read_proc;
        my_proc_fs->write_proc=write_proc;
         return 0;
}

static void __exit module_test_exit(void)
{
     remove_proc_entry(PROC_NAME,0);
}

int read_proc(char *page, char **start, off_t off,int count, int *eof, void *data)
{
     int len=strlen(kernel_buf);
      if(count>len-off)
           {
                 *eof=1;
                  }
      if( count>strlen(kernel_buf)-off )
      {
            count=strlen(kernel_buf)-off;
      }
       memcpy(page+off,kernel_buf+off,count);
        printk("read:%s\n",page);
         return count;
}

int write_proc(struct file *file, const char __user *buffer,unsigned long count, void *data)
{
     int len=strlen(kernel_buf);
      if(count>len)
           {
                 count=len-1;
                  }
       if(!copy_from_user(kernel_buf,buffer,count))//成功返回0,失败返回拷贝失败的字节数.
            {
                  return -1;
                   }
        kernel_buf[count]=0;
         printk("write:%s\n",kernel_buf);
          return count;
}

module_init(module_test_init);
module_exit(module_test_exit);

MODULE_AUTHOR("yanzhiyao");
MODULE_DESCRIPTION("procfs test module");
MODULE_LICENSE("GPL");
