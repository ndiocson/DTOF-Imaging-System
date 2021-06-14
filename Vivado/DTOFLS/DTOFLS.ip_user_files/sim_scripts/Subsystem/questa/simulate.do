onbreak {quit -f}
onerror {quit -f}

vsim -lib xil_defaultlib Subsystem_opt

do {wave.do}

view wave
view structure
view signals

do {Subsystem.udo}

run -all

quit -force
