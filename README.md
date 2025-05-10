<div align="center">
   <h1>C++_Keyboard_ALL_HOOK</h1>
</div>


### **Description**


This C++ code defines and installs a low-level keyboard hook on Windows to monitor and potentially block certain keyboard inputs—specifically Alt+Tab and Windows keys—commonly used to switch or minimize applications. 

This is often used in kiosk, gaming, or locked-down environments.

Hook works globally (entire OS) if injected into a GUI app with a message loop.

SetWindowsHookEx with NULL module handle will only hook local thread unless compiled into a DLL for system-wide use.

You need a message loop (e.g., GetMessage) to keep the hook running.



### **Contact Us**

For any inquiries or questions, please contact us.

telegram : @topdev1012

email :  skymorning523@gmail.com

Teams :  https://teams.live.com/l/invite/FEA2FDDFSy11sfuegI