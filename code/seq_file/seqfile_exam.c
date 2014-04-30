#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

/* 内核数据结构 */
struct _mydrv_struct
{
    struct list_head list; /* 指向下一个节点 */
    char info[20];
    /* ... */
};
static LIST_HEAD(mydrv_list);

/* start() method */
static void * mydrv_seq_start(struct seq_file *seq, loff_t *pos)
{
	struct _mydrv_struct *p;
	loff_t off = 0;
	list_for_each_entry(p, &mydrv_list, list) {
		if (*pos == off++) return p;
	}
	return NULL;
}

/* next() method */
static void * mydrv_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct list_head *n = ((struct _mydrv_struct *)v)->list.next;
	++*pos;
	return(n != &mydrv_list) ?
		list_entry(n, struct _mydrv_struct, list) : NULL;
}

/* show() method */
static int mydrv_seq_show(struct seq_file *seq, void *v)
{
	const struct _mydrv_struct *p = v;
	seq_printf(seq, p->info);
	return 0;
}

/* stop() method */
static void mydrv_seq_stop(struct seq_file *seq, void *v)
{
}

static struct seq_operations mydrv_seq_ops = {
	.start = mydrv_seq_start,
	.next = mydrv_seq_next,
	.stop = mydrv_seq_stop,
	.show = mydrv_seq_show,
};
static int mydrv_seq_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &mydrv_seq_ops);
}
static struct file_operations mydrv_proc_fops = {
	.owner   = THIS_MODULE,
	.open    = mydrv_seq_open,
	.read    = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

static int test_proc_init_module(void)
{

	int i;
	static struct proc_dir_entry *entry = NULL ;
	struct _mydrv_struct * mydrv_new;

	/* Create /proc/readme */
	entry = create_proc_entry("seqfile_exam", S_IWUSR, NULL);
	if (entry)
	{
	   entry->proc_fops = &mydrv_proc_fops;
	}
	for (i=0;i<500;i++)
	{
		mydrv_new = kmalloc(sizeof(struct _mydrv_struct), GFP_ATOMIC);
		sprintf(mydrv_new->info, "Node No: %d\n", i);
		list_add_tail(&mydrv_new->list, &mydrv_list);
	}
	return 0;
}
static void test_proc_exit_module(void)
{
	remove_proc_entry("seqfile_exam",0);
}
module_init(test_proc_init_module);
module_exit(test_proc_exit_module);
