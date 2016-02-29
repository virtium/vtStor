
- Build vtStor on Raspbian Jessie:
   + Step 1: Need to expand sd card size because default about 4 GB. reference http://elinux.org/RPi_raspi-config
   + Step 2: install libusb
         o sudo apt-get install libusb-1.0-0-dev
         o sudo apt-get install libudev-dev
	 o export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/include/libudev.h
	 o export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/include/libusb-1.0/libusb.h
   + Step 3: Install GCC 4.9 and compile C++14 programs (default Raspbian Jessie) if not installing, reference https://solarianprogrammer.com/2015/01/13/raspberry-pi-raspbian-install-gcc-compile-cpp-14-programs/
   + Step 4: Get vtStor source code.
   + Step 5: Use TXTerminal to build solution:
               - move the current path into the vtStor-solution path.
	       - command "make all" (finish).
	       
- Run vtStor.ATest:
    + move the current path into the vtStor-solution/Debug path.
    + command "export LD_LIBRARY_PATH=."
    + command "./vtStor.ATest"
          
- Note: 
    + when attaching SSD disk by usb, use command "lsblk" to check number of SSD disk example 2.
    + At main.cpp (vtStor.ATest project): change "line 60: std::shared_ptr<vtStor::IDrive> selectedDrive = drives[0];                         //!!! Warning: be careful with value 0 in drives[1]" 
                   to "line 60: std::shared_ptr<vtStor::IDrive> selectedDrive = drives[2];                         //!!! Warning: be careful with value 0 in drives[1]" 
    + Build again.