/***************************************************************************
***
***    Copyright 2008  Hon Hai Precision Ind. Co. Ltd.
***    All Rights Reserved.
***    No portions of this material shall be reproduced in any form without the
***    written permission of Hon Hai Precision Ind. Co. Ltd.
***
***    All information contained in this document is Hon Hai Precision Ind.  
***    Co. Ltd. company private, proprietary, and trade secret property and 
***    are protected by international intellectual property laws and treaties.
***
****************************************************************************/


#include <linux/version.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#include <typedefs.h>
#include <bcmutils.h>
#include <siutils.h>
#include <bcmdevs.h>

#include "wps_led.h"

/*#define _DEBUG*/


#ifdef CONFIG_DEVFS_FS
static int wps_led_major;
devfs_handle_t wps_leddev_handle;
#endif /* CONFIG_DEVFS_FS */

extern int wps_led_pattern;
extern int wps_led_state;
extern int is_wl_secu_mode; /* foxconn added, zacker, 09/17/2009, @wps_led */
/*Foxconn add start by Hank 05/31/2013*/
#if (defined CONFIG_SMP)
extern int wps_led_state_smp;
extern int is_wl_secu_mode_smp;
#endif
/*Foxconn add end by Hank 05/31/2013*/

#ifdef WIFI_LED_BLINKING
extern int wifi_2g_led_state_smp;
extern int wifi_5g_led_state_smp;
#endif

static int
wps_led_open(struct inode *inode, struct file * file)
{
    MOD_INC_USE_COUNT;
    return 0;
}

static int
wps_led_release(struct inode *inode, struct file * file)
{
    MOD_DEC_USE_COUNT;
    return 0;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36)   
static int
#else
static long
#endif
wps_led_ioctl(
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36)   
struct inode *inode, 
#endif
struct file *file, 
unsigned int cmd, 
unsigned long arg)
{
	
    /* Foxconn added start pling 02/26/2010 */
    /* Add USB LED support.
     * Note: need to add at the beginning the 'arg' check below.
     *       Otherwise, we might change the wireless LED
     *       by accident.
    */
    
#if (defined INCLUDE_USB_LED)
    if (cmd == USB_LED_STATE_ON || cmd == USB_LED_STATE_OFF)
    {
        /* Foxconn modified start, Wins, 04/11/2011 */
#if defined(R6300v2) || defined(R6250) || defined(R6200v2)
        extern int usb1_led_state;

        if (cmd == USB_LED_STATE_ON)
            usb1_led_state = 1;
        else
            usb1_led_state = 0;

		/* Foxconn added start pling 12/26/2011, for WNDR4000AC */
#elif defined WNDR4000AC 
		/* Do nothing here */
		/* Foxconn added end pling 12/26/2011, for WNDR4000AC */

#else /* R6300v2 */
        extern int usb1_led_state,usb1_led_state_smp;
        if (cmd == USB_LED_STATE_ON)
            usb1_led_state = 1;
        else
            usb1_led_state = 0;
        usb1_led_state_smp=usb1_led_state;
#endif /* R6300v2 */
        /* Foxconn modified end, Wins, 04/11/2011 */
        return 0;
    }

    /* Foxconn added start, Wins, 04/11/2011 */
#if defined(R6300v2) || defined(R7000)
    if (cmd == USB2_LED_STATE_ON || cmd == USB2_LED_STATE_OFF)
    {
        extern int usb2_led_state,usb2_led_state_smp;

        if (cmd == USB2_LED_STATE_ON)
            usb2_led_state = 1;
        else
            usb2_led_state = 0;
        usb2_led_state_smp = usb2_led_state;
        return 0;
    }
#endif /* R6300v2 */
#endif
    /* Foxconn added end, Wins, 04/11/2011 */
#ifdef WIFI_LED_BLINKING
    if (cmd == WLAN_N_RADIO_ON)
    {
    	wifi_2g_led_state_smp=1;
    	return 0;
    }        
    else if(cmd == WLAN_N_RADIO_OFF)
    {
    	wifi_2g_led_state_smp=0;
    	return 0;
    }
    else if(cmd == WLAN_G_RADIO_ON)
    {
    	wifi_5g_led_state_smp=1;
    	return 0;
    }
    else if(cmd == WLAN_G_RADIO_OFF)
    {
    	wifi_5g_led_state_smp=0;
    	return 0;
    }

#endif
    /* Foxconn added end pling 02/26/2010 */

    /* foxconn added start, zacker, 09/17/2009, @wps_led */
	/*Foxconn add start by Hank 05/31/2013*/
	/*change led state value on open SMP*/
    if (arg){
#if (defined CONFIG_SMP)
		is_wl_secu_mode_smp = 1;
        is_wl_secu_mode = 1;
#else
        is_wl_secu_mode = 1;
#endif
    }else{
#if (defined CONFIG_SMP)
		is_wl_secu_mode_smp = 0;
        is_wl_secu_mode = 0;
#else
        is_wl_secu_mode = 0;
#endif
	}
	/*Foxconn add start by Hank 05/31/2013*/
    /* foxconn added end, zacker, 09/17/2009, @wps_led */
	/*Foxconn add start by Hank 05/31/2013*/
	/*change led state value on open SMP*/
    switch (cmd)
    {
        case WPS_LED_BLINK_NORMAL:
#if (defined CONFIG_SMP)
			wps_led_state_smp = 1;
#else
            wps_led_state = 1;
#endif
#ifdef _DEBUG
            printk("%s: blink normal\n", __FUNCTION__);
#endif
            break;

        case WPS_LED_BLINK_QUICK:
#if (defined CONFIG_SMP)
			wps_led_state_smp = 2;
#else
			wps_led_state = 2;
#endif
#ifdef _DEBUG
            printk("%s: blink WPS\n", __FUNCTION__);
#endif
            break;

        case WPS_LED_BLINK_OFF:
#if (defined CONFIG_SMP)
			if(wps_led_state_smp !=2 )
				wps_led_state_smp = 0;
#else
            /* foxconn added start, zacker, 09/17/2009, @wps_led */
            /* wps_led_state will change to 0 automatically after
             * blinking a few seconds if it's 2 currently
             */
            if (wps_led_state != 2)
            /* foxconn added end, zacker, 09/17/2009, @wps_led */
                wps_led_state = 0;
#endif
#ifdef _DEBUG
            printk("%s: blink OFF\n", __FUNCTION__);
#endif
            break;

        case WPS_LED_CHANGE_GREEN:
            break;

        case WPS_LED_CHANGE_AMBER:
            break;

        case WPS_LED_BLINK_QUICK2:
#if (defined CONFIG_SMP)
			wps_led_state_smp = 3;
#else
            wps_led_state = 3;
#endif
            break;
            
        case WPS_LED_BLINK_AP_LOCKDOWN:
#if (defined CONFIG_SMP)
			wps_led_state_smp = 4;
#else
            wps_led_state = 4;
#endif
		/*Foxconn add end by Hank 05/31/2013*/
            break;

        default:
            break;
    }

    return 0;
}

static struct file_operations wps_led_fops = {
#ifndef CONFIG_DEVFS_FS
    .owner      = THIS_MODULE,
    .open       = wps_led_open,
    .release    = wps_led_release,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36)    
    .ioctl      = wps_led_ioctl,
#else    
    .unlocked_ioctl = wps_led_ioctl,
#endif    
#else /* CONFIG_DEVFS_FS */
    owner:      THIS_MODULE,
    open:       wps_led_open,
    release:    wps_led_release,
    ioctl:      wps_led_ioctl,
#endif /* CONFIG_DEVFS_FS */
    };

static int __init
wps_led_init(void)
{
#ifndef CONFIG_DEVFS_FS
    int ret_val;
    /*
    * Register the character device (atleast try)
    */
    ret_val = register_chrdev(WPS_LED_MAJOR_NUM, "wps_led", &wps_led_fops);
    /*
    * Negative values signify an error
    */
    if (ret_val < 0) 
    {
        printf("%s failed with %d\n","Sorry, registering the character device wps_led", ret_val);
        return ret_val;
    } 
#else /* CONFIG_DEVFS_FS */
    if ((wps_led_major = devfs_register_chrdev(WPS_LED_MAJOR_NUM, "wps_led", &wps_led_fops)) < 0)
        return wps_led_major;

    wps_leddev_handle = devfs_register(NULL, "wps_led", DEVFS_FL_DEFAULT,
                                    wps_led_major, 0, S_IFCHR | S_IRUGO | S_IWUGO,
                                    &wps_led_fops, NULL);
#endif /* CONFIG_DEVFS_FS */
    return 0;
}

static void __exit
wps_led_exit(void)
{
#ifndef CONFIG_DEVFS_FS

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36)
    int ret_val;
    ret_val = unregister_chrdev(WPS_LED_MAJOR_NUM, "wps_led");
#else
	unregister_chrdev(WPS_LED_MAJOR_NUM, "wps_led");
#endif    
#else /* CONFIG_DEVFS_FS */
    if (wps_leddev_handle != NULL)
        devfs_unregister(wps_leddev_handle);
    wps_leddev_handle = NULL;
    devfs_unregister_chrdev(wps_led_major, "wps_led");
#endif /* CONFIG_DEVFS_FS */
}

module_init(wps_led_init);
module_exit(wps_led_exit);
