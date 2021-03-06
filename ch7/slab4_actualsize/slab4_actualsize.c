/*
 * ch7/slab4_actualsize/slab4_actualsize.c
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Learn Linux Kernel Development"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *  GitHub repository:
 *  https://github.com/PacktPublishing/Learn-Linux-Kernel-Development
 *
 * From: Ch 7 : Linux Kernel Memory Allocation for Module Authors Part 1
 ****************************************************************
 * Brief Description:
 *
 * For details, please refer the book, Ch 7.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

#define OURMODNAME   "slab4_actualsize"

MODULE_AUTHOR("Kaiwan N Billimoria");
MODULE_DESCRIPTION("LLKD book:ch5/slab4_actualsize: test slab alloc with the ksize()");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int stepsz = 200000;
module_param(stepsz, int, 0644);
MODULE_PARM_DESC(stepsz,
 "Amount to increase allocation by on each loop iteration (default=200000");

static int test_maxallocsz(void)
{
	/* This time, initialize size2alloc to 100, as otherwise we'll get a
	 * divide error! */
	size_t size2alloc = 100, actual_alloced;
	void *p;

	pr_info("kmalloc(      n) :  Actual : Wastage : Waste %%\n");
	while (1) {
		p = kmalloc(size2alloc, GFP_KERNEL);
		if (!p) {
			pr_alert("kmalloc fail, size2alloc=%ld\n", size2alloc);
			return -ENOMEM;
		}
		actual_alloced = ksize(p);
		/* Print the size2alloc, the amount actually allocated,
	         * the delta between the two, and the percentage of waste
		 * (integer arithmetic, of course :-)
		 */
		pr_info("kmalloc(%7ld) : %7ld : %7ld : %3ld%%\n",
                        size2alloc, actual_alloced, (actual_alloced-size2alloc),
			(((actual_alloced-size2alloc)*100)/size2alloc));
		kfree(p);
		size2alloc += stepsz;
	}
	return 0;
}

static int __init slab4_actualsize_init(void)
{
	pr_debug("%s: inserted\n", OURMODNAME);
	return test_maxallocsz();
}
static void __exit slab4_actualsize_exit(void)
{
	pr_debug("%s: removed\n", OURMODNAME);
}

module_init(slab4_actualsize_init);
module_exit(slab4_actualsize_exit);
