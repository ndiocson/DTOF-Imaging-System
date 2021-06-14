# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\ndioc\workspace\Platform_Final\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\ndioc\workspace\Platform_Final\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Platform_Final}\
-hw {D:\PERSONAL\Projects\DTOFLS\Subsystem_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -fsbl-target {psu_cortexa53_0} -out {C:/Users/ndioc/workspace}

platform write
platform generate -domains 
platform active {Platform_Final}
platform generate
