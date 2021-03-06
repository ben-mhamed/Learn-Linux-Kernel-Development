/*
 * ch5/cross/helloworld_lkm.c
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Learn Linux Kernel Development"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *  GitHub repository:
 *  https://github.com/PacktPublishing/Learn-Linux-Kernel-Development
 *
 * From: Ch 5: Writing your First Kernel Module - LKMs Part 2
 ****************************************************************
 * Brief Description:
 * Our very first kernel module, the 'Hello, world' of course! The
 * idea being to explain the essentials of the Linux kernel's LKM
 * framework.
 * This time, we're attempting to cross compile and run it on the
 * Raspberry Pi SBC! This does not affect the code in any major way, of course,
 * but *does* affect the Makefile. Check out the new and enhanced Makefile
 * carefully.
 *
 * For details, please refer the book, Ch 5.
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("<insert your name here>");
MODULE_DESCRIPTION("LLKD book:ch5/cross: hello, world, our first Raspberry Pi LKM");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int __init helloworld_lkm_init(void)
{
	printk(KERN_INFO "Hello, Raspberry Pi world\n");
	return 0;		/* success */
}

static void __exit helloworld_lkm_exit(void)
{
	printk(KERN_INFO "Goodbye, Raspberry Pi world\n");
}

module_init(helloworld_lkm_init);
module_exit(helloworld_lkm_exit);
