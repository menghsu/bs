#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>
MODULE_DESCRIPTION("Char Transform Kernel Module");
#define MAX_COOKIE_LENGTH       PAGE_SIZE
#define MODULE_NAME "transform"

static struct proc_dir_entry *proc_entry;
static char *cookie_pot;  // Space for strings
static int next_write_pos;  // Index to write next
static int next_read_pos;  // Index to read next

void transform(char * str) {
	char *p = str;
	while(*p){
		if((*p) >= 'a' && (*p) <= 'z'){
			*p = *p - 32;
		}else if( *p >= 'A' && *p <= 'Z'){
			*p = *p + 32;
		}
		++p;
	}
}

ssize_t procfs_write( struct file *filp, const char __user *buff,
                        unsigned long len, void *data )
{
	int space_available = (MAX_COOKIE_LENGTH-next_write_pos)+1;
	if (len > MAX_COOKIE_LENGTH) {
		printk(KERN_INFO "space is not enough!\n");
		return -ENOSPC;
	}
	if (copy_from_user( &cookie_pot[next_write_pos], buff, len )) {
		return -EFAULT;
	}
	transform(&cookie_pot[next_write_pos]);
	next_write_pos += len;
	cookie_pot[next_write_pos-1] = 0;
	return len;
}

int procfs_read( char *page, char **start, off_t off,
                   int count, int *eof, void *data )
{
  int len;
  if (off > 0) {
    *eof = 1;
    return 0;
  }
  /* Wrap-around */
  if (next_read_pos >= next_write_pos) next_read_pos = 0;
  len = sprintf(page, "%s\n", &cookie_pot[next_read_pos]);
  next_read_pos += len;
  return len;
}

int init_my_module( void )
{
  int ret = 0;
  cookie_pot = (char *)vmalloc( MAX_COOKIE_LENGTH );
  if (!cookie_pot) {
    ret = -ENOMEM;
  } else {
    memset( cookie_pot, 0, MAX_COOKIE_LENGTH );
    proc_entry = create_proc_entry( MODULE_NAME, 0666, NULL );
    if (proc_entry == NULL) {
      ret = -ENOMEM;
      vfree(cookie_pot);
      printk(KERN_INFO "Couldn't create proc entry\n");
    } else {
      next_write_pos = 0;
      next_read_pos = 0;
      proc_entry->read_proc = procfs_read;
      proc_entry->write_proc = procfs_write;
  //    proc_entry->owner = THIS_MODULE;
      printk(KERN_INFO "Module loaded.\n");
    }
  }
  return ret;
}

void cleanup_my_module( void )
{
  remove_proc_entry(MODULE_NAME, NULL);
  vfree(cookie_pot);
  printk(KERN_INFO "Module unloaded.\n");
}

// 注册
module_init( init_my_module );
module_exit( cleanup_my_module );
