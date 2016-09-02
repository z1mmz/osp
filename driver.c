#include "driver.h"
#define SUCCESS 0
#define DEVICE_NAME "s3495671Device"
#define BUF_LEN 80
MODULE_LICENSE("GPL");
// Ops that are avail
static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

// device from assignment spec
struct virtual_device {
char data[100];
struct semaphore sem;
}myDevice;


int init_module(){
//TODO Find out how to create Dev node in c
// alloc_chrdev_region()
alloc = alloc_chrdev_region(&devNum,0,1,DEVICE_NAME);

//Check if alloc worked
if( alloc < 0){
	printk(KERN_INFO "Could not register - alloc_chrdev_region failed\n");
}
if ( (cl = class_create( THIS_MODULE, DEVICE_NAME) ) == NULL )
{
		printk( KERN_ALERT "Class creation failed\n" );
		unregister_chrdev_region( devNum, 1 );
		return -1;
}

device_create(cl,NULL,devNum,NULL,DEVICE_NAME);

cdev_init(&c_dev,&fops);

cdev_add(&c_dev,devNum,1);


// init the semaphore
 sema_init(&myDevice.sem,1);
printk(KERN_INFO "s3495671 device diver initalised \n");


return SUCCESS;

}
void cleanup_module(void){
  // unregister driver
	printk(KERN_INFO "Cleaning up!\n");
	cdev_del(&c_dev);
	device_destroy(cl,devNum);
	class_destroy(cl);
	unregister_chrdev_region(devNum,1);
  // unregister_chrdev(Major,DEVICE_NAME);


}

static int device_open(struct inode *inode, struct file *file){

// Check if sem has been taken
	if(down_interruptible(&myDevice.sem)){
		printk(KERN_INFO " Device is in use\n");
		return 1;
	}else{
		printk(KERN_INFO " Device control taken\n");
	}
	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file){
	up(&myDevice.sem);
	printk(KERN_INFO " Device control Released\n");
	return 0;

}

static ssize_t device_read(struct file * f, char *buffer, size_t len, loff_t * offset){
 // printk(KERN_INFO "Reading: ");
// reads data from struct and copies it to the user
 unsigned long errorBits; // bits that could not be read
 printk(KERN_INFO "Read : %s", myDevice.data);
 errorBits = copy_to_user(buffer, myDevice.data, len);

 return errorBits;



}

static ssize_t device_write(struct file *f, const char  *buffer, size_t len, loff_t * offset){
	// printk(KERN_INFO "Writing");
	// copies input into the device
	unsigned long errorBits; // bits that could not be read
	printk(KERN_INFO "Write in : %s", buffer);
	errorBits = copy_from_user(myDevice.data, buffer, len);
  return errorBits;

}
