package main

import (
    "fmt"
    "os"
    "syscall"
    "unsafe"
)

func main() {
    serial, err := os.OpenFile("/dev/ttyACM0", syscall.O_RDWR|syscall.O_NOCTTY|syscall.O_NONBLOCK, 0666)
    if err != nil {
        fmt.Println("error opening file")
    }
    
    var cflags uint32 = syscall.CREAD 
    cflags |= syscall.CLOCAL
    cflags |= syscall.B115200
    cflags |= syscall.CS8
    cflags |= syscall.CSTOPB
    cflags |= syscall.PARENB
    cflags |= syscall.PARODD
    
    fd := serial.Fd()
    term := syscall.Termios{
        Iflag:  syscall.IGNPAR,
        Cflag:  cflags,
        Ispeed: syscall.B115200,
        Ospeed: syscall.B115200,
    }
    
    _, _, errno := syscall.Syscall6(
        syscall.SYS_IOCTL,
        uintptr(fd),
        uintptr(syscall.TCSETS),
        uintptr(unsafe.Pointer(&term)),
        0,
        0,
        0,
    )
    if errno != 0 {
        fmt.Println("syscall failed")
    }
    
    err = syscall.SetNonblock(int(fd), false)
    if err != nil {
        fmt.Println("set nonblocking failed")
    }
    
    _, err2 := serial.Write([]byte("0"))
    if err2 != nil {
        fmt.Println("write failed")
    }
    
    //~ buf := make([]byte, 128)
    //~ n, err2 := serial.Read(buf)
    //~ if err2 != nil {
        //~ fmt.Println("read failed")
    //~ }
    //~ fmt.Printf("%q\n", buf[:n])
    
    err2 = serial.Close()
}
