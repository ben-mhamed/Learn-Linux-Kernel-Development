/*
 * ch4/slab5_actualsz_wstg_plot/slab5_actualsz_wstg_plot.c
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Linux Kernel Development Cookbook"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *  GitHub repository:
 *  https://github.com/PacktPublishing/Linux-Kernel-Development-Cookbook
 *
 * From: Ch 4 : Linux Kernel Memory Allocation for Module Authors 
 ****************************************************************
 * Brief Description:
 * Here, we have slightly modified the ch4/slab5_actualsize LKM to print just
 * what's required in order to get a good data file, in order to plot a nice
 * graph with gnuplot(1) !
 *
 * For details, please refer the book, Ch 4.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

#define OURMODNAME   "slab5_actualsz_wstg_plot"

MODULE_AUTHOR("Kaiwan N Billimoria");
MODULE_DESCRIPTION("LKDC book:ch4/slab5_actualsz_wstg_plot: test slab alloc with the ksize()");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int stepsz = 20000;
module_param(stepsz, int, 0644);
MODULE_PARM_DESC(stepsz,
 "Amount to increase allocation by on each loop iteration (default=200000");

static int test_maxallocsz(void)
{
	/* This time, initialize size2alloc to 100 (not 0), as otherwise we'll
	 * likely get a divide error!
	 */
	size_t size2alloc = 100, actual_alloc;
	void *p;

	while (1) {
		p = kmalloc(size2alloc, GFP_KERNEL);
		if (!p) {
			pr_alert("kmalloc fail, size2alloc=%ld\n", size2alloc);
			return -ENOMEM;
		}
		actual_alloc = ksize(p);
		/* Only print the size2alloc (required) and the percentage of waste */
		pr_info("%ld  %3ld\n",
                        size2alloc, (((actual_alloc-size2alloc)*100/size2alloc)));
		kfree(p);
		size2alloc += stepsz;
	}
	return 0;
}

static int __init slab5_actualsz_wstg_plot_init(void)
{
	pr_debug("%s: inserted\n", OURMODNAME);
	return test_maxallocsz();
}
static void __exit slab5_actualsz_wstg_plot_exit(void)
{
	pr_debug("%s: removed\n", OURMODNAME);
}

module_init(slab5_actualsz_wstg_plot_init);
module_exit(slab5_actualsz_wstg_plot_exit);
