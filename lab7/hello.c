/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>


MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint number = 1;

module_param(number, uint, 0660);
MODULE_PARM_DESC(number, "Number of printed 'Hello, world!'\n");

struct time_struct {
	struct list_head list;
	ktime_t time;
};

LIST_HEAD(my_list);

static int __init hello_init(void)
{
	int i;

	BUG_ON(number > 10);
	//if (number > 10) {
		//printk(KERN_ERR "ERROR!\n");
		//return -EINVAL;
	//}
	if (number == 0 || (number >= 5 && number <= 10))
			printk(KERN_WARNING "Warning! Danger value of variable.\n");
	for (i = 0; i < number; i++) {
		struct time_struct *time_inst = kmalloc(sizeof(struct time_struct *), GFP_KERNEL);

		time_inst->time = ktime_get();
		printk(KERN_EMERG "Hello, world!\n");
		list_add_tail(&time_inst->list, &my_list);
		WARN(i == number-1, "kmalloc() return 0\n");
	}
	return 0;
}

static void __exit hello_exit(void)
{
	struct time_struct *md, *tmp;
	uint i = 1;

	list_for_each_entry_safe(md, tmp, &my_list, list) {
		printk(KERN_EMERG "Time of (%i) 'Hello, world!': %lld\n", i,  md->time);
		list_del(&md->list);
		kfree(md);
		i++;
	}

}

module_init(hello_init);
module_exit(hello_exit);
