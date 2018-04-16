#include <linux/kernel.h> 
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static int devinfo_show(struct seq_file *f, void *v)
{
	panic("We reached unpopular paths in fs/proc/devices.c: line 9 \n"); 
	int i = *(loff_t *) v;

	if (i < CHRDEV_MAJOR_HASH_SIZE) {
		if (i == 0)
			seq_puts(f, "Character devices:\n");
		chrdev_show(f, i);
	}
#ifdef CONFIG_BLOCK
	else {
		i -= CHRDEV_MAJOR_HASH_SIZE;
		if (i == 0)
			seq_puts(f, "\nBlock devices:\n");
		blkdev_show(f, i);
	}
#endif
	return 0;
}

static void *devinfo_start(struct seq_file *f, loff_t *pos)
{
	panic("We reached unpopular paths in fs/proc/devices.c: line 30 \n"); 
	if (*pos < (BLKDEV_MAJOR_HASH_SIZE + CHRDEV_MAJOR_HASH_SIZE))
		return pos;
	return NULL;
}

static void *devinfo_next(struct seq_file *f, void *v, loff_t *pos)
{
	panic("We reached unpopular paths in fs/proc/devices.c: line 38 \n"); 
	(*pos)++;
	if (*pos >= (BLKDEV_MAJOR_HASH_SIZE + CHRDEV_MAJOR_HASH_SIZE))
		return NULL;
	return pos;
}

static void devinfo_stop(struct seq_file *f, void *v)
{
	panic("We reached unpopular paths in fs/proc/devices.c: line 47 \n"); 
	/* Nothing to do */
}

static const struct seq_operations devinfo_ops = {
	.start = devinfo_start,
	.next  = devinfo_next,
	.stop  = devinfo_stop,
	.show  = devinfo_show
};

static int devinfo_open(struct inode *inode, struct file *filp)
{
	panic("We reached unpopular paths in fs/proc/devices.c: line 60 \n"); 
	return seq_open(filp, &devinfo_ops);
}

static const struct file_operations proc_devinfo_operations = {
	.open		= devinfo_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= seq_release,
};

static int __init proc_devices_init(void)
{
	proc_create("devices", 0, NULL, &proc_devinfo_operations);
	return 0;
}
fs_initcall(proc_devices_init);
